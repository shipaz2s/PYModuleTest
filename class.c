#include "class.h"
#include <stdlib.h>
#include <memory.h>

#include <stdio.h>

void appendSignal(Signals* signals, size_t begin, size_t end) {
	
	printf("size = %d, capacity = %d\n", signals->size);
	if (signals->size + 1 > signals->capacity) {
		Signal* new_data = malloc(sizeof(Signal) * signals->capacity * 2);
		memcpy(new_data, signals->data, sizeof(Signal) * signals->capacity);
		if (signals->data != NULL) {
			free(signals->data);
		}
		signals->data = new_data;
		signals->capacity = signals->capacity * 2;
	}
	
	printf("NEW size = %d, capacity = %d\n", signals->size);
	Signal new_signal;
	new_signal.begin = begin;
	new_signal.end = end;
	signals->data[signals->size] = new_signal;
	signals->size += 1;
	printf("appended\n");
}