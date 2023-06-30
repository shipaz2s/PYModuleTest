#pragma once
#include <stdint.h>

typedef struct {
	size_t begin;
	size_t end;
} Signal;

typedef struct {
	Signal* data;
	size_t capacity;
	size_t size;
} Signals;

void appendSignal(Signals* signals, size_t begin, size_t end);


