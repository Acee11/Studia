// Wojciech Balik
// 280254
#ifndef SENDING_FUNC
#define SENDING_FUNC
#include <netinet/ip_icmp.h>
#include <assert.h>
#include <arpa/inet.h>

typedef struct
{
	int sockfd;
	struct icmphdr icmp_header;
	struct sockaddr_in recipient;
} icmp_sender;

uint16_t compute_icmp_checksum (const void *buff, int length);
void compute_checksum(icmp_sender* sender);
int send_init(icmp_sender* sender, int sockfd, int type, int code, int id, int seq, char* ip);
int icmp_send(icmp_sender* sender, int n);

#endif