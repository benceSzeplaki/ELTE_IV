#ifndef header_guard_1
#define header_guard_1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bunny.h"

typedef struct ArrayBunny
{
    Bunny *array;
    size_t used;
    size_t size;
} ArrayBunny;

void initArray(ArrayBunny *b, size_t initialSize)
{
    b->array = malloc(initialSize * sizeof(Bunny));
    b->used = 0;
    b->size = initialSize;
}

void insertArray(ArrayBunny *b, Bunny xd)
{
    if (b->used == b->size)
    {
        b->size += 1;
        b->array = realloc(b->array, b->size * sizeof(Bunny));
    }
    b->array[b->used++] = xd;
}

Bunny getBunnyFromArray(ArrayBunny *b, int i)
{
    return b->array[i];
}

int getSize(ArrayBunny *b)
{
    return (int)b->size;
}

void printArray(ArrayBunny *b)
{
    for (int i = 0; i < getSize(b); i++)
    {
        printBunny(getBunnyFromArray(b, i));
    };
}

void freeArray(ArrayBunny *b)
{
    for (int i = 0; i < getSize(b); i++)
    {
        free(b->array[i].name);
    };
    free(b->array);
    b->array = NULL;
    b->used = b->size = 0;
}
#endif