// Wojciech Balik
// 280254

#include <stdio.h>

#include "downloader.h"

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));

	if(argc != 4)
	{
		fprintf(stderr, "Usage: ./transport <port> <output file name> <bytes to download>\n");
		exit(EXIT_FAILURE);
	}
	unsigned int port;
	size_t len;
	if(sscanf(argv[1], "%u", &port) != 1)
	{
		fprintf(stderr, "Wrong input(port)\n");
		exit(EXIT_FAILURE);
	}

	char* fname = argv[2]; 

	if(sscanf(argv[3], "%lu", &len) != 1)
	{
		fprintf(stderr, "Wrong input(bytes to download)\n");
		exit(EXIT_FAILURE);
	}

	struct downloader dler;
	dler.bytes_to_dl = len;
	downloader_init(&dler, "156.17.4.30", port, fname);

	download(&dler);
	return 0;
}