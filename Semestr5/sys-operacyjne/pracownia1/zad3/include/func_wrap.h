#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

pid_t fork_();
void close_(int fd);
void pipe_(int *fd);
int read_(int fd, void *buf, size_t count);
void write_(int fd, const void *buf, size_t count);
int read_word(int fd, char *buf, int buf_size);