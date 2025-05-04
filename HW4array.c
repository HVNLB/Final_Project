#include "array.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct array* array_create()
{
	struct array* a = (struct array*)malloc(sizeof(struct array));
        assert(0 != a);
        memset(a, 0, sizeof(struct array));
	a->size = 0;
	a->capacity = 2;
	a->start = (element_type*)malloc(a->capacity * sizeof(element_type));
	return a;
}

void array_push_back(struct array* a, element_type e)
{
	 // check if array is full
	if(a->size==a->capacity)
	{    // make new capacity double the old one
		size_type newCap = a->capacity * 2;
		// reallocate more memory for the array
		element_type* newStart = (element_type*) realloc(a->start, newCap * sizeof(element_type));
		if(newStart == NULL)
		{ 	 // failed to get memory
			printf("realloc failed\n");
			exit(1);
		}
		a->start = newStart;// set new memory
		a->capacity = newCap; // update cap
	}

	// put element at the end
	a->start[ a->size ] = e;
	// increase size because we added something
	a->size = a->size + 1;
}

void array_pop_back(struct array* a)
{   // check if pointer is not NULL
	if(a!=NULL)
	{
		        // only pop if there's something in the array
		if(a->size!=0)
		{

			// just reduce size,no need to clear data
			a->size = a->size - 1;
		}
	}
}

void array_insert(struct array* a, size_type index, element_type e)
{
	 // index too big
	if(index > a->size){
		printf("invalid index\n");
		return;// can't insert
	}
    // if no space, make more room
	if(a->size==a->capacity){
		size_type bigger = a->capacity + a->capacity;// double it
		 // try to reallocate
		a->start = (element_type*) realloc(a->start, bigger * sizeof(element_type));
		if(!a->start){
			printf("alloc fail\n"); exit(1);
		}
		a->capacity = bigger;
	}
	 // move all elements to the right
	size_type i = a->size;// start from the end
	while(i > index){
		a->start[i] = a->start[i-1];// shift things
		i=i-1;// go back
	}

	// put new element at the spot
	a->start[index] = e;

	 // we added one
	a->size = a->size+1;
}

size_type array_size(struct array* a)
{
	assert(0 != a);
	return a->size;
}

size_type array_capacity(struct array* a)
{
	assert(0 != a);
	return a->capacity;
}

void array_print(struct array* a)
{
	assert(0 != a);
	for (size_type i = 0; i < a->size; ++i) {
		printf("%d ", a->start[i]);
	}
	printf("\nsize = %d", a->size);
	printf("\ncapacity = %d\n\n", a->capacity);
}

int array_empty(struct array* a)
{
	assert(0 != a);
	return a->size == 0;
}
