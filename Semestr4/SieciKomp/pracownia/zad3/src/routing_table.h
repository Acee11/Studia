#ifndef ROUTING_TABLE
#define ROUTING_TABLE

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define DIRECT_CONN UINT_MAX
#define INF UINT_MAX
#define MAX_DIST 40

typedef union
{
	uint32_t ip32;

	struct
	{
		uint8_t b3;
		uint8_t b2;
		uint8_t b1;
		uint8_t b0;
	} bytes;

} int_ip;

// in routing table directly connected networks are always at the begining(prefix)
typedef struct 
{
	int_ip ip;
	unsigned int dist;
	unsigned int conn_through; //index in routing table
	int_ip conn_through_ip;
	unsigned int state; //how long(in turns) is target not responding
	uint8_t mask;
	bool reachable;
} routing_table_entry;

typedef struct
{
	routing_table_entry* table;
	size_t max_len;
	size_t len;
	size_t direct_len;
} routing_table;

uint32_t number_to_mask(uint8_t n);
void routing_table_init(routing_table* rtable, size_t n);
void push_back(routing_table* rtable, routing_table_entry rtable_entry);
int find_ip_by_str(routing_table* rtable, char* str_ip, bool direct);
int find_shortest(routing_table* rtable, int_ip ip);
void init_msg(uint8_t* buffer, routing_table_entry entry);
void init_ip(char* dst_ip, routing_table_entry entry);
void rtable_remove(routing_table* rtable, unsigned int i);
void rtable_print(routing_table* rtable);
void mark_unreachable(routing_table* rtable, unsigned int idx);
void str_to_int_ip(char* str_ip, int_ip* ip);


#endif