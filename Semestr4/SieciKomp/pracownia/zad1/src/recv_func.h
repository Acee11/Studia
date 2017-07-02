// Wojciech Balik
// 280254
#ifndef RECV_FUNC
#define RECV_FUNC
#include <sys/select.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

typedef struct 
{
	int sockfd;
	size_t packets_rdy;
	uint32_t avg_time;
	char* sender_ip_str;
	size_t ip_len; // ip_len * 20 =  sizeof(sender_ip_str) 
	size_t ip_cnt;
	uint8_t type;
	uint8_t* packet_buffer;
	size_t buffer_len;
} icmp_receiver;

void recv_init(icmp_receiver* receiver,int sockfd, uint8_t* packet_buffer, size_t buffer_len, char* sender_ip_str, size_t ip_len);

//receives n packets(or less) after waiting max sec seconds and usec microseconds
int recv_icmp(icmp_receiver* receiver, int pid, int seq, uint32_t n, uint32_t usec);

#endif