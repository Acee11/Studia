// Wojciech Balik
// 280254
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "sending_func.h"
#include "recv_func.h"

#define USEC_WAIT_TIME 1000000


struct icmphdr_buffer
{

	size_t packets_rdy;
	float avg_time;
	char* sender_ip_str;
	size_t ip_len; // ip_len * 20 =  sizeof(sender_ip_str) 
	size_t ip_cnt;
	uint8_t type; 
};


int main(int argc, char** argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage:\n\ttraceroute <ip>\n");
		exit(1);
	}

	int err;
	int pid = getpid();
	int seq = 1;
	int ttl = 1;
	uint8_t buffer[IP_MAXPACKET];
	
	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if(sockfd < 0)
	{
		fprintf(stderr, "Error: While creating a socket:\n\t%s\n", strerror(errno));
		exit(2);
	}


	icmp_sender sender;
	err = send_init(&sender, sockfd, ICMP_ECHO, 0, pid, seq, argv[1]);
	if(err == 1)
	{
		fprintf(stderr, "Error: Wrong ip format\n");
		exit(3);
	}

	int ip_len = 4;
	char sender_ip_str[ip_len*20];

	icmp_receiver receiver;
	recv_init(&receiver, sockfd, buffer, IP_MAXPACKET, sender_ip_str, ip_len);

	for(;;)
	{
		
		setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));


		sender.icmp_header.un.echo.sequence = seq;
		compute_checksum(&sender);

		err = icmp_send(&sender, 3);
		if(err == 1)
		{
			fprintf(stderr, "Error: While sending packets\n");
			exit(4);
		}

		err = recv_icmp(&receiver, pid, seq, 3, USEC_WAIT_TIME);

		if(err == 1)
		{
			fprintf(stderr, "Error: Wrong ip buffer size\n");
			exit(5);
		}
		else if(err == 2)
		{
			fprintf(stderr, "Error: While waiting for packets\n\t%s\n", strerror(errno));
			exit(6);
		}
		else if(err == 3)
		{
			fprintf(stderr, "Error: While recieving packets\n\t%s\n", strerror(errno));
			exit(7);
		}
		else if(err == 4)
		{
			fprintf(stderr, "Error: While waiting for packets\n\t%s\n", strerror(errno));
			exit(8);
		}

		//printing output
		printf("%-3d    ", seq);
		if(receiver.ip_cnt == 0)
			printf("*\n");
		else
		{
			for(size_t i = 0; i < receiver.ip_cnt; ++i)
			{
				if(receiver.sender_ip_str[20*i] == '\0')
					break;
				printf("%-20s", &receiver.sender_ip_str[20*i]);
			}
			if(receiver.packets_rdy == 3)
				printf("%u ms\n", receiver.avg_time);
			else
			{
				printf("???\n");
			}
		}
		++seq;
		++ttl;

		if(receiver.type == ICMP_ECHOREPLY && receiver.ip_cnt != 0)
			break;
		if(ttl > 64)
			break;
	}

	close(sockfd);
	return 0;
}