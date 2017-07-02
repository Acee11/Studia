// Wojciech Balik
// 280254

#ifndef DOWNLOADER__H
#define DOWNLOADER__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include "window.h"

#define PACKET_SIZE 1000
#define MAX_HEADER_LEN 25
#define DEFAULT_WINDOW_SIZE 2000
#define TIMEOUT 0.1
#define WAIT_TIME (0.002)
#define MSG_SENDING_COUNT 2



struct downloader
{
	size_t bytes_to_dl;
	FILE* dst_file;
	int sockfd;
	struct sockaddr_in recipient;
};

size_t encode_msg(char* msg, size_t start, size_t len);
size_t decode_msg(char* msg, size_t* start, size_t* len);
void float_to_tv(struct timeval* tv, float t);
float tv_to_float(struct timeval* tv);

void send_msg_n_times(
	uint8_t* msg, 
	size_t msg_len, 
	unsigned int n,
	int sockfd,
	struct sockaddr_in* recipient);

void downloader_init(struct downloader* dler, char* ip, unsigned int port, char* fname);
void close_dler(struct downloader* dler);
unsigned int handle_new_packet(
	struct window* window, 
	struct downloader* dler, 
	size_t recv_frame_number,
	uint8_t* recv_data
);

void download(struct downloader* dler);

#endif