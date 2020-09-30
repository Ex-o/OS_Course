#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cstring>

void *new_realloc(void *ptr, size_t sz_old, size_t sz_new){
	if (ptr == NULL) {
		return malloc(sz_new);
	}

	if (!sz_new){
		free(ptr);
		return NULL;
	}

	int sz_min = sz_new < sz_old ? sz_new : sz_old;

	void *new_arr = malloc(sz_min);
	memcpy(new_arr, ptr, sz_min);
	free(ptr);
	return new_arr;
}