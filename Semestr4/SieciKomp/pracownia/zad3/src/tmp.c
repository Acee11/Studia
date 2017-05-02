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


#define PACKET_SIZE 1000
#define DEFAULT_WINDOW_SIZE 10
#define TIMEOUT 1.0
#define MAX_HEADER_LEN 20

int main(int argc, char** argv)
{
	FILE* f = fopen("input", "ab");
	fwrite("GET 0 700\n", sizeof(char), 10, f);
	return 0;
}