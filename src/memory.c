/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 ljr-ifsp
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <stdio.h>
#include <malloc.h>
#include "simos.h" 

simos_memory_t *simos_memory_create(size_t size)
{
    
    simos_memory_t *mem = (simos_memory_t *) malloc(sizeof(simos_memory_t));
    mem->size = size;
    mem->cells = calloc(size, sizeof(int));
    return mem;
}

void simos_memory_destroy(simos_memory_t *mem)
{
    free(mem->cells);
    free(mem);
}

size_t simos_memory_alloc(simos_memory_t *mem, size_t block)
{
    int i = 0, available = 0, pointer;

    /* try to find how many gaps existing in the memory */
    while (1) {
        /* find a gap in the memory */
        while (i < mem->size && mem->cells[i] != 0) {
            i++;
        }
        //printf("[MEM] Gap found at %d\n", i);

        /* measure gap's size */
        while (i < mem->size && available < block && mem->cells[i] == 0) {
            i++;
            available++;
        }

        if (available == block) {
            pointer = i - block;
            for (i = pointer; i < (pointer + block); i++) {
                mem->cells[i] = 1;
            }
            return pointer;
        } else if (i > mem->size) {
            //printf("Not enough space... No memory allocated.");
            return -1;
        }
    }
    
}

void simos_memory_free(simos_memory_t *mem, size_t pointer, size_t length)
{
    int i;
    for (i = pointer; i < (pointer + length); i++) {
        mem->cells[i] = 0;
    }
}


