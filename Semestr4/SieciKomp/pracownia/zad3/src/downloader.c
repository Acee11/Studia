// Wojciech Balik
// 280254

#include "downloader.h"



size_t encode_msg(char* msg, size_t start, size_t len)
{
	sprintf(msg, "GET %lu %lu\n", start, len);
	return (size_t)(strchr(msg, '\n') - msg + 1); // returns header length
}

size_t decode_msg(char* msg, size_t* start, size_t* len)
{
	sscanf(msg, "DATA %lu %lu\n", start, len);
	*start /= PACKET_SIZE;
	return (size_t)(strchr(msg, '\n') - msg + 1); // returns header length
}

void float_to_tv(struct timeval* tv, float t)
{
	tv->tv_sec = (int)t;
	tv->tv_usec = (int)(1000000*(t-((float)tv->tv_sec)));
}

float tv_to_float(struct timeval* tv)
{
	return ((float)tv->tv_sec) + ((float)tv->tv_usec)/1000000.0;
}

void send_msg_n_times(
	uint8_t* msg, 
	size_t msg_len, 
	unsigned int n,
	int sockfd,
	struct sockaddr_in* recipient)
{
	for(unsigned int i = 0; i < n; ++i)
	{
		size_t bytes_sent = sendto(
			sockfd, 
			msg, 
			msg_len, 
			0, 
			(struct sockaddr*)recipient, 
			sizeof(struct sockaddr_in)
		);
		if(bytes_sent != msg_len)
		{
			fprintf(stderr, "Error while sending packets:\n\t%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}	
}

void downloader_init(struct downloader* dler, char* ip, unsigned int port, char* fname)
{
	dler->dst_file = fopen(fname, "ab");
	if(dler->dst_file == NULL)
	{
		fprintf(stderr, "Error while opening a file\n");
		exit(EXIT_FAILURE);
	}

	dler->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(dler->sockfd < 0)
	{
		fprintf(stderr, "Error while creating a socket:\n\t%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}



	struct sockaddr_in if_address;

	bzero(&if_address, sizeof(if_address));
	if_address.sin_family = AF_INET;
	if_address.sin_port = htons(port);
	if_address.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(dler->sockfd, (struct sockaddr*)&if_address, sizeof(if_address)) < 0)
	{
		fprintf(stderr, "Error while binding a socket:\n\t%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	bzero(&dler->recipient, sizeof(dler->recipient));
	dler->recipient.sin_family = AF_INET;
	dler->recipient.sin_port = htons(port);
	inet_pton(AF_INET, ip, &dler->recipient.sin_addr);

}

unsigned int handle_new_packet(
	struct window* window, 
	struct downloader* dler, 
	size_t recv_frame_number,
	uint8_t* recv_data
)
{
	size_t last_frame = (dler->bytes_to_dl / PACKET_SIZE) - (dler->bytes_to_dl % PACKET_SIZE == 0);

	if(recv_frame_number < window->beginning || 
	   recv_frame_number >= window->beginning + window->size)
		return 0;
	size_t frame_idx = recv_frame_number - window->beginning;
	size_t frame_idx_offset = (frame_idx + window->offset) % window->size;
	if(window->frames[frame_idx_offset].received_data)
		return 0;
	window->frames[frame_idx_offset].received_data = true;
	if(frame_idx == 0)
	{
		char msg[MAX_HEADER_LEN];
		memcpy(
			window->frames[frame_idx_offset].data, 
			recv_data, 
			PACKET_SIZE
		);
		while(frame_idx < window->size && 
			  window->frames[frame_idx_offset].received_data && 
			  window->beginning <= last_frame)
		{
			
			if((window->beginning == last_frame) && (dler->bytes_to_dl % PACKET_SIZE != 0))
			{
				fwrite(
					window->frames[frame_idx_offset].data, 
					sizeof(uint8_t), 
					dler->bytes_to_dl % PACKET_SIZE, 
					dler->dst_file
				);
			}
			else
			{
				fwrite(
					window->frames[frame_idx_offset].data, 
					sizeof(uint8_t), 
					PACKET_SIZE, 
					dler->dst_file
				);
			} 

			if(window->beginning + window->size <= last_frame)
			{
				size_t header_len = encode_msg(
					msg, 
					(window->beginning + window->size) * PACKET_SIZE, 
					PACKET_SIZE
				);

				send_msg_n_times(
					(uint8_t*)msg,
					header_len,
					MSG_SENDING_COUNT,
					dler->sockfd,
					&dler->recipient
				);
				window->frames[frame_idx_offset].time_left = TIMEOUT;
				window->frames[frame_idx_offset].received_data = false;
				window->frames[frame_idx_offset].frame_number = (window->beginning + window->size);
			}
			++window->beginning;
			++frame_idx;
			++window->offset;
			frame_idx_offset = (frame_idx_offset + 1) % window->size;
		}
	}
	else
	{
		memcpy(
			window->frames[frame_idx_offset].data, 
			recv_data, 
			PACKET_SIZE
		);
	}
	return 1;
}

void close_dler(struct downloader* dler)
{
	fclose(dler->dst_file);
	close(dler->sockfd);
}

void download(struct downloader* dler)
{
	unsigned int packets_downloaded = 0;
	unsigned int packets_to_dl = (dler->bytes_to_dl / PACKET_SIZE);
	if(dler->bytes_to_dl % PACKET_SIZE != 0)
		++packets_to_dl;

	struct window window;
	size_t window_size = packets_to_dl < DEFAULT_WINDOW_SIZE ? packets_to_dl : DEFAULT_WINDOW_SIZE;
	init_window(&window, window_size, PACKET_SIZE);

	for(size_t i = 0; i < window.size; ++i)
	{
		window.frames[i].time_left = TIMEOUT;
		window.frames[i].frame_number = i;
		window.frames[i].received_data = false;
	}

	char msg[MAX_HEADER_LEN];

	struct sockaddr_in unused_sender;
	socklen_t unused_sender_len = sizeof(unused_sender);

	for(size_t i = 0; i < window.size; ++i)
	{
		window.frames[i].time_left = TIMEOUT;
		window.frames[i].frame_number = i;
		window.frames[i].received_data = false;

		size_t sent_msg_len = encode_msg(
			msg, 
			window.frames[i].frame_number * PACKET_SIZE, 
			PACKET_SIZE
		);
		send_msg_n_times(
			(uint8_t*)msg,
			sent_msg_len,
			MSG_SENDING_COUNT,
			dler->sockfd,
			&dler->recipient
		);
	}

	uint8_t buffer[PACKET_SIZE + MAX_HEADER_LEN];
	fd_set descriptors;
	FD_ZERO(&descriptors);
	FD_SET(dler->sockfd, &descriptors);
	while(window.beginning < packets_to_dl)
	{
		struct timeval tv, tv1, tv2;
		float_to_tv(&tv, WAIT_TIME);
		gettimeofday(&tv1, NULL);
		int ready = select(dler->sockfd+1, &descriptors, NULL, NULL, &tv);
		gettimeofday(&tv2, NULL);
		tv2.tv_sec -= tv1.tv_sec;
		tv2.tv_usec -= tv1.tv_usec;
		float select_time_waited = tv_to_float(&tv2);
		float overall_time_waited = select_time_waited;
		if(ready < 0)
		{
			fprintf(stderr, "Error while waiting for packets:\n\t%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		while(ready-- > 0)
		{
			ssize_t received_bytes = recvfrom(
				dler->sockfd, 
				buffer, 
				PACKET_SIZE+MAX_HEADER_LEN, 
				0, 
				(struct sockaddr*)&unused_sender, 
				&unused_sender_len
			);
			if(received_bytes < 0)
			{
				fprintf(stderr, "Error: while revieving packets \n\t%s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}

			size_t recv_frame_number, recv_frame_len;
			size_t recv_header_len = decode_msg(
				(char*)buffer, 
				&recv_frame_number,
				&recv_frame_len
			);
			uint8_t* recv_data = &buffer[recv_header_len];
			
			packets_downloaded += handle_new_packet(
				&window,
				dler,
				recv_frame_number,
				recv_data
			);
		}
		for(size_t i = 0; i < window.size; ++i)
		{
			if(!window.frames[i].received_data)
			{
				window.frames[i].time_left -= overall_time_waited;
				if(window.frames[i].time_left <= 0.0)
				{
					window.frames[i].time_left = TIMEOUT;
					size_t sent_msg_len = encode_msg(msg, 
						window.frames[i].frame_number * PACKET_SIZE, 
						PACKET_SIZE
					);
					send_msg_n_times(
						(uint8_t*)msg,
						sent_msg_len,
						MSG_SENDING_COUNT,
						dler->sockfd,
						&dler->recipient
					);
				}
			}
		}
		FD_SET(dler->sockfd, &descriptors);
		printf("\rProgress: %u%%", (100*packets_downloaded)/packets_to_dl);
	}
	printf("\n");
	close_window(&window);
}