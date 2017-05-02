// Wojciech Balik
// 280254
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/select.h>
#include <time.h>


#define PACKET_SIZE 1000
#define DEFAULT_WINDOW_SIZE 100
#define TIMEOUT 0.01
#define MAX_HEADER_LEN 20

typedef struct 
{
	float time_left;
	size_t start; // must be divisible by PCKET_SIZE
	bool received_data;
} window_entry;


size_t init_msg(char* msg, size_t start, size_t len)
{
	sprintf(msg, "GET %lu %lu\n", start, len);
	return (size_t)(strchr(msg, '\n') - msg + 1);
}

// return headers lenghth
size_t parse_msg_header(char* msg, size_t* start, size_t* len)
{
	sscanf(msg, "DATA %lu %lu\n", start, len);
	return (size_t)(strchr(msg, '\n') - msg + 1);
}

size_t find_min(window_entry* window, size_t n)
{
	size_t min_idx = 0;
	float min_time = FLT_MAX;
	for(size_t i = 1; i < n; ++i)
	{
		if((window[i].time_left < min_time ) && (!window[i].received_data))
		{
			min_idx = i;
			min_time = window[i].time_left;
		}
	}

	return min_idx;
}

void set_time(float t, struct timeval* tv)
{
	tv->tv_sec = (int)t;
	tv->tv_usec = (int)(1000000*(t-((float)tv->tv_sec)));
}

int main(int argc, char** argv)
{

	if(argc != 4)
	{
		fprintf(stderr, "Usage: ./transport <port> <output file name> <bytes to download>\n");
		exit(EXIT_FAILURE);
	}
	unsigned int port;
	size_t len;
	if(sscanf(argv[1], "%u", &port) != 1)
	{
		fprintf(stderr, "Wrong input(port)\n");
		exit(EXIT_FAILURE);
	}

	char* fname = argv[2]; 

	if(sscanf(argv[3], "%lu", &len) != 1)
	{
		fprintf(stderr, "Wrong input(bytes to download)\n");
		exit(EXIT_FAILURE);
	}

	FILE* f = fopen(fname, "ab");
	if(f == NULL)
	{
		fprintf(stderr, "Error while opening a file\n");
		exit(EXIT_FAILURE);
	}

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		fprintf(stderr, "Error while creating a socket:\n\t%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in if_address;

	bzero(&if_address, sizeof(if_address));
	if_address.sin_family = AF_INET;
	if_address.sin_port = htons(port);
	if_address.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd, (struct sockaddr*)&if_address, sizeof(if_address)) < 0)
	{
		fprintf(stderr, "Error while binding a socket:\n\t%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	fd_set descriptors;
	FD_ZERO(&descriptors);
	FD_SET(sockfd, &descriptors);

	// len == 10 000  =>  last_frame = 9
	// len == 999     =>  last_frame = 0 
	size_t last_frame = (len / PACKET_SIZE) - (len % PACKET_SIZE == 0);
	size_t WINDOW_SIZE = DEFAULT_WINDOW_SIZE;
	if(last_frame < WINDOW_SIZE)
		WINDOW_SIZE = last_frame + 1;


	uint8_t* data = malloc(WINDOW_SIZE * PACKET_SIZE * sizeof(uint8_t));
	window_entry window[WINDOW_SIZE];

	struct sockaddr_in recipient;
	bzero(&recipient, sizeof(recipient));
	recipient.sin_family = AF_INET;
	recipient.sin_port = htons(port);
	inet_pton(AF_INET, "156.17.4.30", &recipient.sin_addr);

	struct sockaddr_in sender;	
	socklen_t sender_len = sizeof(sender);

	for(size_t i = 0; i < WINDOW_SIZE; ++i)
	{
		window[i].start = PACKET_SIZE * i;
		window[i].time_left = TIMEOUT;
		window[i].received_data = false;
		char buffer[MAX_HEADER_LEN];
		size_t header_len = init_msg(buffer, window[i].start, PACKET_SIZE);
		size_t bytes_sent = sendto(
			sockfd, 
			buffer, 
			header_len, 
			0, 
			(struct sockaddr*)&recipient, 
			sizeof(recipient)
		);
		
		if(bytes_sent != header_len)
		{
			fprintf(stderr, "Error while sending packets:\n\t%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

	size_t LFR = 0;
	size_t offset = 0; 
	// window is implemented as cyclic list, so n-th element index is
	// (n + offset) mod WINDOW_SIZE

	
	while(LFR <= last_frame)
	{
		printf("%lu\n", LFR);
		char msg[MAX_HEADER_LEN+1];
		uint8_t buffer[2*PACKET_SIZE];

		size_t idx = find_min(window, WINDOW_SIZE);
		struct timeval tv;
		if(window[idx].time_left < 0.0)
			window[idx].time_left = 0.0;
		set_time(window[idx].time_left, &tv);
		int ready = select(sockfd+1, &descriptors, NULL, NULL, &tv);

		if(ready < 0)
		{
			fprintf(stderr, "Error while waiting for packets:\n\t%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		else if(ready == 0)
		{
			for(size_t i = 0; i < WINDOW_SIZE; ++i)
				if(!window[i].received_data)
					window[i].time_left -= window[idx].time_left;
			window[idx].time_left = TIMEOUT;
			size_t header_len = init_msg(msg, window[idx].start, PACKET_SIZE);
			size_t bytes_sent = sendto(
				sockfd, 
				msg, 
				header_len, 
				0, 
				(struct sockaddr*)&recipient, 
				sizeof(recipient)
			);
			if(bytes_sent != header_len)
			{
				fprintf(stderr, "Error while sending packets:\n\t%s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
		else // ready > 0
		{
			ssize_t datagram_len = recvfrom(
				sockfd, 
				buffer, 
				2*PACKET_SIZE, 
				0, 
				(struct sockaddr*)&sender, 
				&sender_len
			);
			if (datagram_len < 0)
			{
				fprintf(stderr, "Error: while revieving packets \n\t%s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			
			size_t start, msg_len;
			size_t header_len = parse_msg_header((char*)buffer, &start, &msg_len);
			uint8_t* recv_data = &buffer[header_len];

			size_t frame = start / PACKET_SIZE;
			//size_t first_frame = window[(0 + offset) % WINDOW_SIZE].start / PACKET_SIZE;
			if(frame < LFR || frame >= LFR + WINDOW_SIZE)
				continue;
			size_t packet_idx = (frame - LFR);
			size_t packet_idx_offset = (packet_idx + offset) % WINDOW_SIZE;
			if(window[packet_idx_offset].received_data)
				continue;
			window[packet_idx_offset].received_data = true;
			if(packet_idx == 0)
			{
				memcpy(&data[PACKET_SIZE * packet_idx_offset], recv_data, PACKET_SIZE);
				while(packet_idx < WINDOW_SIZE && window[packet_idx_offset].received_data && LFR <= last_frame)
				{
					if((LFR == last_frame) && (len % PACKET_SIZE != 0))
						fwrite(
							&data[PACKET_SIZE * packet_idx_offset], 
							sizeof(uint8_t), 
							len % PACKET_SIZE, 
							f
						);
					else fwrite(
							&data[PACKET_SIZE * packet_idx_offset], 
							sizeof(uint8_t), 
							PACKET_SIZE, 
							f
						);

					if(LFR + WINDOW_SIZE < last_frame)
					{
						size_t header_len = init_msg(msg, (LFR + WINDOW_SIZE) * PACKET_SIZE, PACKET_SIZE);
						size_t bytes_sent = sendto(
							sockfd, 
							msg, 
							header_len, 
							0, 
							(struct sockaddr*)&recipient, 
							sizeof(recipient)
						);
						if(bytes_sent != header_len)
						{
							fprintf(stderr, "Error while sending packets:\n\t%s\n", strerror(errno));
							exit(EXIT_FAILURE);
						}
						window[packet_idx_offset].time_left = TIMEOUT;
						window[packet_idx_offset].received_data = false;
						window[packet_idx_offset].start = (LFR + WINDOW_SIZE) * PACKET_SIZE;
					}

					++LFR;
					++packet_idx;
					++offset;
					packet_idx_offset = (packet_idx_offset + 1) % WINDOW_SIZE;
				}
			}
			else
			{
				window[packet_idx_offset].received_data = true;
				memcpy(&data[PACKET_SIZE * packet_idx_offset], recv_data, PACKET_SIZE);
			}
			
		}

		FD_SET(sockfd, &descriptors);
	}




	free(data);
	fclose(f);
	return 0;
}