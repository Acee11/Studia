// Wojciech Balik
// 280254

#include "window.h"

void init_window(struct window* window, size_t size, size_t packet_size)
{
	window->frames = malloc(size * sizeof(window_entry));
	window->size = size;
	window->offset = 0;
	window->beginning = 0;
	uint8_t* data = malloc(window->size * packet_size * sizeof(uint8_t));
	window->data_begin = data;

	for(unsigned int i = 0; i < window->size; ++i)
		window->frames[i].data = &data[packet_size * i];

}

void close_window(struct window* window)
{
	free(window->data_begin);
	free(window->frames);
}