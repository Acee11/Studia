#include "routing_table.h"

// /16 -> 0b11111111111111110000000000000000
uint32_t number_to_mask(uint8_t n)
{
	if(n == 0)
		return 0;
	int mask = 0x80000000;
	mask >>= (n-1);
	return (uint32_t)mask;
}

void routing_table_init(routing_table *rtable, size_t n)
{
	rtable->table = malloc(n * sizeof(routing_table_entry));
	rtable->max_len = n;
	rtable->len = 0;
	rtable->direct_len = 0;
}

void push_back(routing_table* rtable, routing_table_entry rtable_entry)
{

	if(rtable->len == rtable->max_len)
	{
		rtable->max_len *= 2;
		if(rtable->max_len == 0)
			rtable->max_len = 1;
		routing_table_entry* new_table = malloc(rtable->max_len * sizeof(routing_table_entry));
		memcpy(new_table, rtable->table, rtable->len * sizeof(routing_table_entry));
		free(rtable->table);
		rtable->table = new_table;
	}
	if(rtable_entry.conn_through == DIRECT_CONN)
	{
		memmove(&rtable->table[rtable->direct_len+1], 
			    &rtable->table[rtable->direct_len], 
			    (rtable->len - rtable->direct_len) * sizeof(routing_table_entry));
		rtable->table[rtable->direct_len++] = rtable_entry;
		++rtable->len;
	}
	else
		rtable->table[rtable->len++] = rtable_entry;
}

int find_ip_by_str(routing_table* rtable, char* str_ip, bool direct)
{
	int_ip ip;
	sscanf(str_ip, "%hhu.%hhu.%hhu.%hhu",
		       &ip.bytes.b0, &ip.bytes.b1,
		       &ip.bytes.b2, &ip.bytes.b3
		);
	int end = direct ? rtable->direct_len : rtable->len;
	for(int i = 0; i < end; ++i)
	{
		int mask = number_to_mask(rtable->table[i].mask);
		if((rtable->table[i].ip.ip32 & mask) == (ip.ip32 & mask))
			return i;
	}
	return -1;
}

int find_shortest(routing_table* rtable, int_ip ip)
{
	unsigned int min_dist = INF;
	int min_idx = -1;
	for(unsigned int i = 0; i < rtable->len; ++i)
	{
		int mask = number_to_mask(rtable->table[i].mask);
		if((ip.ip32 & mask) == (rtable->table[i].ip.ip32 & mask))
		{
			if(rtable->table[i].dist < min_dist)
			{
				min_dist = rtable->table[i].dist;
				min_idx = i;
			}
		}
	}

	return min_idx;
}

void init_msg(uint8_t* buffer, routing_table_entry entry)
{
	buffer[0] = entry.ip.bytes.b0;
	buffer[1] = entry.ip.bytes.b1;
	buffer[2] = entry.ip.bytes.b2;
	buffer[3] = entry.ip.bytes.b3;
	buffer[4] = entry.mask;

	unsigned int dist = entry.reachable ? entry.dist : INF;
	uint8_t* ptr = (uint8_t*) &dist;
	buffer[5] = ptr[3];
	buffer[6] = ptr[2];
	buffer[7] = ptr[1];
	buffer[8] = ptr[0];
}

void init_ip(char* dst_ip, routing_table_entry entry)
{
	entry.ip.ip32 |= (~number_to_mask(entry.mask));
	sprintf(dst_ip, "%hhu.%hhu.%hhu.%hhu\0", entry.ip.bytes.b0, entry.ip.bytes.b1,
		    entry.ip.bytes.b2, entry.ip.bytes.b3);
}

void rtable_remove(routing_table* rtable, unsigned int i)
{
	if(i >= rtable->len)
		return;
	for(unsigned int j = 0; j < rtable->len; ++j)
	{
		if(rtable->table[j].conn_through > i && rtable->table[j].conn_through != DIRECT_CONN)
			--rtable->table[j].conn_through;
	}
	memmove(&rtable->table[i], &rtable->table[i+1], (rtable->len - i - 1)*sizeof(routing_table_entry));
	if(i < rtable->direct_len)
		--rtable->direct_len;
	--rtable->len;
}

void rtable_print(routing_table* rtable)
{
	for(unsigned int i = 0; i < rtable->len; ++i)
	{
		int_ip ip = rtable->table[i].ip;
		ip.ip32 &= number_to_mask(rtable->table[i].mask);
		printf("%hhu.%hhu.%hhu.%hhu/%hhu ",
			ip.bytes.b0, ip.bytes.b1,
			ip.bytes.b2, ip.bytes.b3,
			rtable->table[i].mask);
		if(rtable->table[i].reachable)
		{
			printf("distance %d ", rtable->table[i].dist);
			if(rtable->table[i].conn_through == DIRECT_CONN)
				printf("connected directly\n");
			else
			{
				ip = rtable->table[i].conn_through_ip;
				printf("via %hhu.%hhu.%hhu.%hhu\n",
					ip.bytes.b0, ip.bytes.b1,
					ip.bytes.b2, ip.bytes.b3);
			}
		}
		else
		{
			printf("unreachable ");
			if(rtable->table[i].conn_through == DIRECT_CONN)
				printf("connected directly\n");
			else printf("\n");
		}
	}
	printf("-----------------------------------------------\n");
}

void mark_unreachable(routing_table* rtable, unsigned int idx)
{
	if(rtable->table[idx].reachable)
	{
		rtable->table[idx].reachable = false;
		rtable->table[idx].state = 0;
	}
	for(unsigned int i = rtable->direct_len; i < rtable->len; ++i)
	{
		if(rtable->table[i].conn_through == idx)
			mark_unreachable(rtable, i);
	}
}

void str_to_int_ip(char* str_ip, int_ip* ip)
{
	sscanf(str_ip, "%hhu.%hhu.%hhu.%hhu",
		       &ip->bytes.b0, &ip->bytes.b1,
		       &ip->bytes.b2, &ip->bytes.b3
		);
}