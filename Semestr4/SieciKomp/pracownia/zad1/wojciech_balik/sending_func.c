// Wojciech Balik
// 280254
#include "sending_func.h"

uint16_t compute_icmp_checksum (const void *buff, int length)
{
	uint32_t sum;
	const uint16_t* ptr = buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (uint16_t)(~(sum + (sum >> 16)));
}

void compute_checksum(icmp_sender* sender)
{
	sender->icmp_header.checksum = 0;
	sender->icmp_header.checksum = compute_icmp_checksum((uint16_t*)&sender->icmp_header, sizeof(sender->icmp_header));
}

int send_init(icmp_sender* sender, int sockfd, int type, int code, int id, int seq, char* ip)
{
	sender->sockfd = sockfd;

	sender->icmp_header.type = type;
	sender->icmp_header.code = code;
	sender->icmp_header.un.echo.id = id;
	sender->icmp_header.un.echo.sequence = seq;
	compute_checksum(sender);

	sender->recipient.sin_family = AF_INET;
	sender->recipient.sin_port = 0;
	int err = inet_pton(AF_INET, ip, &sender->recipient.sin_addr);
	if(err == 0)
		return 1;

	return 0;
}

int icmp_send(icmp_sender* sender, int n)
{
	for(int i = 0; i < n; ++i)
	{
		int bytes_sent = sendto(
			sender->sockfd,
			&sender->icmp_header,
			sizeof(sender->icmp_header),
			0,
			(struct sockaddr*)&sender->recipient,
			sizeof(sender->recipient)
		);
		if(bytes_sent < 0)
			return 1;
	}
	return 0;
}
