// Wojciech Balik
// 280254

#ifndef WINDOW__H
#define WINDOW__H
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct 
{
	float time_left;
	size_t frame_number;
	bool received_data;
	uint8_t* data;
} window_entry;

struct window
{
	window_entry* frames;
	uint8_t *data_begin;
	size_t size;
	size_t offset;
	size_t beginning;
};

void init_window(struct window* window, size_t size, size_t packet_size);
void close_window(struct window* window);

#endif