// Wojciech Balik
// 280254
#include "recv_func.h"


void recv_init(icmp_receiver* receiver,int sockfd, uint8_t* packet_buffer, size_t buffer_len, char* sender_ip_str, size_t ip_len)
{
	receiver->sockfd = sockfd;
	receiver->packet_buffer = packet_buffer;
	receiver->buffer_len = buffer_len; 
	receiver->sender_ip_str = sender_ip_str;
	receiver->ip_len = ip_len;
}

int recv_icmp(icmp_receiver* receiver, int pid, int seq, uint32_t n, uint32_t usec)
{
	if(receiver->ip_len < n)
		return 1;

	struct sockaddr_in sender;
	socklen_t sender_len = sizeof(sender);
	fd_set descriptors;
	FD_ZERO(&descriptors);
	FD_SET(receiver->sockfd, &descriptors);
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = usec;

	char ip_str[20];
	receiver->ip_cnt = 0;

	receiver->packets_rdy = 0;
	receiver->avg_time = 0;

	while(receiver->packets_rdy < n)
	{
		int ready = select(receiver->sockfd+1, &descriptors, NULL, NULL, &tv);

		if(ready < 0)
			return 2;
		else if(ready > 0) //number of packets waiting is > 0
		{
			int packet_len = recvfrom(
				receiver->sockfd,
				receiver->packet_buffer,
				IP_MAXPACKET,
				MSG_DONTWAIT,
				(struct sockaddr*)&sender,
				&sender_len
			);
			if(packet_len < 0)
				return 3;
			
			//reading data
			struct iphdr* ip_header = (struct iphdr*) receiver->packet_buffer;
			uint8_t* icmp_packet = receiver->packet_buffer + 4*ip_header->ihl;
			struct icmphdr* icmp_hder = (struct icmphdr*) icmp_packet;

			if(icmp_hder->type == ICMP_TIME_EXCEEDED) //time exceeded
			{
				icmp_hder = (struct icmphdr*) (icmp_packet + sizeof(struct icmphdr) + sizeof(struct iphdr));
			}
			else if(icmp_hder->type != ICMP_ECHOREPLY) //not echo reply nor time exceeded
			{
				continue;
			}

			if(icmp_hder->un.echo.id == pid && icmp_hder->un.echo.sequence == seq) // recieved packet comes from expected sender
			{
				receiver->type = icmp_hder->type;
				++receiver->packets_rdy;
				if(receiver->sender_ip_str != NULL)
				{
					inet_ntop(
						AF_INET,
						&(sender.sin_addr),
						ip_str,
						sizeof(ip_str)
					);

					int new_ip_flag = 1;
					for(size_t i = 0; i < receiver->ip_cnt; ++i) //checking if response came from not known router
					{
						if(strcmp(ip_str, &receiver->sender_ip_str[20*i]) == 0)
						{
							new_ip_flag = 0;
							break;
						}
					}
					if(new_ip_flag)
					{
						memcpy(&receiver->sender_ip_str[20*receiver->ip_cnt], ip_str, 20);
						++receiver->ip_cnt;
						if(receiver->ip_cnt != receiver->ip_len)
							receiver->sender_ip_str[20*receiver->ip_cnt] = '\0';
					}
				}
			}
		}
		else break; //timeout after waiting (max) n sec u microseconds
	}
	receiver->avg_time = (1000000 - tv.tv_usec)/3000;
	return 0;
}