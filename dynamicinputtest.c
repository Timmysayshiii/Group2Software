#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "TExaS.h"
#include "dynamicinputtest.h"

struct vector {
	char *data;
	size_t size, capacity;
};

typedef struct vector vector;

vector *init_vector() {
	vector *vec = (vector *)malloc(sizeof(vector));
	vec->size = 0;
	vec->capacity = 4;
	vec->data = (char *)malloc(vec->capacity);
	
	return vec;
}

void add_char(vector *vec, char c) {
	if (vec->size == vec->capacity) {
		vec->capacity *= 2;
		vec->data = (char *)realloc(vec->data, vec->capacity);
	}
	vec->data[vec->size++] = c;
}

char *get_str(vector *vec) {
	return vec->data;
}

void free_vector(vector *vec) {
	free(vec->data);
	free(vec);
}
