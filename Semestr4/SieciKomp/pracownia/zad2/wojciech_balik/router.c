// Wojciech Balik
// 280254
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <strings.h>
#include <errno.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <sys/select.h>
#include <limits.h>
#include "routing_table.h"

#define TURN 5
#define MSG_LEN 9
#define MAX_TURNS_UNREACHABLE 5
#define JUST_GOT_MSG UINT_MAX
#define MAX_TURN_NOT_RESPONDING 5




void set_time(float t, struct timeval* tv)
{
	tv->tv_sec = (int)t;
	tv->tv_usec = (int)(1000000*(t-((float)tv->tv_sec)));
}
float get_float_time(struct timeval tv)
{
	return ((float)tv.tv_sec) + ((float)tv.tv_usec)/1000000.0;
}

void parse_msg(uint8_t* buffer, int_ip* ip, uint8_t* mask, unsigned int* dist)
{
	ip->bytes.b0 = buffer[0];
	ip->bytes.b1 = buffer[1];
	ip->bytes.b2 = buffer[2];
	ip->bytes.b3 = buffer[3];
	*mask = buffer[4];
	uint8_t* tmp = (uint8_t*)dist;
	tmp[0] = buffer[8];
	tmp[1] = buffer[7];
	tmp[2] = buffer[6];
	tmp[3] = buffer[5];

}

int main()
{
	size_t n;
	scanf("%lu\n", &n);
	int* sockfd = malloc(n * sizeof(int));
	int maxfd = 0;
	fd_set descriptors;
	FD_ZERO(&descriptors);

	routing_table rtable;
	routing_table_init(&rtable, n);

	for(unsigned int i = 0; i < n; ++i)
	{
		

		routing_table_entry entry;
		char if_ip[20];
		scanf("%[1234567890.]/%hhu %*s %u\n",
		       if_ip, &entry.mask, &entry.dist);

		sscanf(if_ip, "%hhu.%hhu.%hhu.%hhu",
		       &entry.ip.bytes.b0, &entry.ip.bytes.b1,
		       &entry.ip.bytes.b2, &entry.ip.bytes.b3
		);
		
		entry.conn_through = DIRECT_CONN;
		entry.reachable = true;
		entry.state = 0;

		push_back(&rtable, entry);


		sockfd[i] = socket(AF_INET, SOCK_DGRAM, 0);
		if(sockfd[i] < 0)
		{
			fprintf(stderr, "Error while creating a socket:\n\t%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		struct sockaddr_in if_address;
		bzero(&if_address, sizeof(if_address));
		if_address.sin_family = AF_INET;
		if_address.sin_port = htons(54321);
		init_ip(if_ip, entry);
		if_address.sin_addr.s_addr = inet_addr(if_ip);
		int broadcastPermission = 1;
		setsockopt(sockfd[i], SOL_SOCKET, SO_BROADCAST,
			       (void*)&broadcastPermission, 
			       sizeof(broadcastPermission));
		if(bind(sockfd[i], (struct sockaddr*)&if_address, sizeof(if_address)) < 0)
		{
			fprintf(stderr, "Error while binding a socket:\n\t%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}


		FD_SET(sockfd[i], &descriptors);
		if(sockfd[i] > maxfd)
			maxfd = sockfd[i];
	}
	
	printf("direct_len = %lu     len = %lu\n", rtable.direct_len, rtable.len);


	for(;;)
	{
		uint8_t buffer[IP_MAXPACKET+1];

		float time_left = (float)TURN;

		struct timeval tv, tv1, tv2;


		// recieving packets
		while(time_left > 0)
		{
			set_time(time_left, &tv);
			gettimeofday(&tv1, NULL);
			int ready = select(maxfd+1, &descriptors, NULL, NULL, &tv);
			gettimeofday(&tv2, NULL);
			tv2.tv_sec -= tv1.tv_sec;
			tv2.tv_usec -= tv1.tv_usec;
			time_left -= get_float_time(tv2);
			if(ready < 0)
			{
				fprintf(stderr, "Error while waiting for packets:\n\t%s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			else if(ready > 0)
			{
				struct sockaddr_in sender;	
				socklen_t sender_len = sizeof(sender);
				for(unsigned int i = 0; i < n; ++i)
				{
					while(FD_ISSET(sockfd[i], &descriptors))
					{

						ssize_t datagram_len = recvfrom(sockfd[i], buffer, MSG_LEN, MSG_DONTWAIT, (struct sockaddr*)&sender, &sender_len);
						if (datagram_len < 0)
						{
							if(errno == EWOULDBLOCK) //no more packets
								break;
							fprintf(stderr, "Error: while revieving packets \n\t%s\n", strerror(errno));
							exit(EXIT_FAILURE);
						}

						else if(datagram_len != MSG_LEN) //something is wrong with the message
							continue;

						char sender_ip_str[20]; 
						inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));

						int_ip sender_ip_int;
						str_to_int_ip(sender_ip_str, &sender_ip_int);
						if(sender_ip_int.ip32 == rtable.table[i].ip.ip32) //packet from ourselves
							continue;
						int sender_idx = find_ip_by_str(&rtable, sender_ip_str, true);
						if(sender_idx == -1) //got packet from unknown sender
						{
							continue;
						}
						if(!rtable.table[sender_idx].reachable)
							rtable.table[sender_idx].reachable = true;
						rtable.table[sender_idx].state = JUST_GOT_MSG;
						int_ip recv_ip;
						uint8_t recv_mask;
						unsigned int recv_dist;
						parse_msg(buffer, &recv_ip, &recv_mask, &recv_dist);
						int idx = find_shortest(&rtable, recv_ip);
						if(sender_idx == idx)
							continue;
						if(idx == -1) // unknown network
						{
							if(recv_dist != INF)
							{
								routing_table_entry entry;
								entry.ip = recv_ip;
								entry.mask = recv_mask;
								entry.dist = recv_dist + rtable.table[sender_idx].dist;
								entry.reachable = true;
								entry.conn_through = sender_idx;
								entry.conn_through_ip = sender_ip_int;
								entry.state = 0;
								push_back(&rtable, entry);
							}

						}
						else // known netowork
						{
							routing_table_entry entry = rtable.table[idx];
							if(recv_dist == INF || rtable.table[sender_idx].dist == INF)
								recv_dist = INF;
							else
								recv_dist += rtable.table[sender_idx].dist;
							if(recv_dist > entry.dist)
							{
								// we've got information that distance has grown
								if(sender_idx == rtable.table[idx].conn_through)
								{
									rtable.table[idx].dist = recv_dist;
									if(recv_dist >= MAX_DIST)
									{
										mark_unreachable(&rtable, idx);
									}
								}
							}
							else if(recv_dist < entry.dist) // got shorter path
							{
								if(!rtable.table[idx].reachable && recv_dist < MAX_DIST)
									rtable.table[idx].reachable = true;
								rtable.table[idx].conn_through = sender_idx;
								rtable.table[idx].conn_through_ip = sender_ip_int;
								rtable.table[idx].dist = recv_dist;
							}
						}

						--ready;
					}
				}
				
			}
			for(unsigned int i = 0; i < n; ++i)
				FD_SET(sockfd[i], &descriptors);
		}

		// sending packets
		struct sockaddr_in recipient;
		bzero(&recipient, sizeof(recipient));
		recipient.sin_family = AF_INET;
		recipient.sin_port = htons(54321);

		// sending only to directly connected targets

		for(unsigned int i = 0; i < rtable.direct_len; ++i)
		{
			for(unsigned int j = 0; j < rtable.len; ++j)
			{
				// not sending information about targets unreachable for
				// long enough time

				if(!rtable.table[j].reachable && rtable.table[j].state > MAX_TURNS_UNREACHABLE)
					continue;
				uint8_t buffer[MSG_LEN];
				init_msg(buffer, rtable.table[j]);

				recipient.sin_family = AF_INET;
				recipient.sin_port = htons(54321);
				char dst_ip[20];
				init_ip(dst_ip, rtable.table[i]);
				inet_pton(AF_INET, dst_ip, &recipient.sin_addr);

				if(sendto(sockfd[i], buffer, MSG_LEN, 0, (struct sockaddr*)&recipient, sizeof(recipient)) != MSG_LEN)
				{
					// handle unreachable
					if(rtable.table[i].reachable)
						mark_unreachable(&rtable, i);
					break;

				}
			}
		}

		// end the turn
		for(unsigned int i = 0; i < rtable.len; ++i)
		{
			if(rtable.table[i].reachable)
			{
				if(rtable.table[i].state == JUST_GOT_MSG)
					rtable.table[i].state = 0;
				else if(rtable.table[i].conn_through == DIRECT_CONN)
				{
					++rtable.table[i].state;
					if(rtable.table[i].state == MAX_TURN_NOT_RESPONDING)
					{
						mark_unreachable(&rtable, i);
					}
				}
			}
			else if(rtable.table[i].state != MAX_TURNS_UNREACHABLE)
			{
				++rtable.table[i].state;
				if(rtable.table[i].state == MAX_TURNS_UNREACHABLE && rtable.table[i].conn_through != DIRECT_CONN)
					rtable_remove(&rtable, i);
			}
		}
		// print route table
		rtable_print(&rtable);
	}



}