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

#define NUM_PAGES 20

/** Create a memory with the refered size. */
simos_memory_t *simos_memory_create(size_t size)
{
    simos_memory_t *mem = malloc(sizeof(simos_memory_t));

    mem->size = size;
    mem->cells = calloc(size, sizeof(unsigned char)); // set memory to zero...
    mem->num_pages = NUM_PAGES;
    mem->pages = malloc(sizeof(simos_page_t)*NUM_PAGES);

    int i;
    for (i = 0; i < NUM_PAGES; i++)
        mem->pages[i].busy = 0;

    return mem;
}

/** Call free (malloc(3)) in the allocated memory. */
void simos_memory_destroy(simos_memory_t *mem)
{
    free(mem->cells);
    free(mem);
}

size_t simos_first_fit(simos_memory_t *mem, size_t block)
{
    if (mem == NULL)
        return -1;

    int space, begin_page, i, j;

    for (i=0; i < NUM_PAGES; i++)
    {
        if (mem->pages[i].busy == 0)
        {
            begin_page = begin_page - 1 == i ? begin_page : i;
         
            space += mem->pages[i].length_page;
            
            if (space >= block)
            {
                for (j = begin_page; j < i; j++)
                    mem->pages[j].busy = 1;

                return begin_page; 
            }
        }
    }
    return -1;
}

size_t simos_next_fit(simos_memory_t *mem, size_t block)
{
    if (mem == NULL)
        return -1;

    int space, begin_page, i, j;

    for (i=mem->last_page_alloc; i < NUM_PAGES; i++)
    {
        if (mem->pages[i].busy == 0)
        {
            begin_page = begin_page - 1 == i ? begin_page : i;

            space += mem->pages[i].length_page;
            
            if (space >= block)
            {
                for (j = begin_page; j < i; j++)
                    mem->pages[j].busy = 1;

                mem->last_page_alloc = begin_page;

                return begin_page; 
            }
        }
    }
    return -1;
}

size_t simos_worst_fit(simos_memory_t *mem, size_t block)
{
    if (mem == NULL)
        return -1;

    int space, begin_page, i, j, greater = -1, greater_pos = -1;

    for (i=0; i < NUM_PAGES; i++)
    {
        if (mem->pages[i].busy == 0)
        {
            begin_page = begin_page - 1 == i ? begin_page : i;

            if ( (begin_page-1) == i )
            {
                greater_pos = begin_page;
                begin_page = i;
            }

            
            if (begin_page == i && space > greater)
            {
                greater = space;
            }

            space += mem->pages[i].length_page;
        }
    }

    if (greater_pos != -1)
    {
        for (j = begin_page; j < i; j++)
            mem->pages[j].busy = 1;

        mem->last_page_alloc = begin_page;

        return greater_pos; 
    }

    return -1;
}

size_t simos_best_fit(simos_memory_t *mem, size_t block)
{
    if (mem == NULL)
        return -1;

    int space, begin_page, i, j;

    for (i=0; i < NUM_PAGES; i++)
    {
        if (mem->pages[i].busy == 0)
        {
            begin_page = begin_page - 1 == i ? begin_page : i;
            space += mem->pages[i].length_page;
            
            if (space == block)
            {
                for (j = begin_page; j < i; j++)
                    mem->pages[j].busy = 1;

                mem->last_page_alloc = begin_page;

                return begin_page; 
            }
        }
    }

    // if not find the best space, then call first fit
    simos_first_fit(mem, block);

    return -1;
}


/**
 * Try to find a gap in the memory that fits the block size. 
 *
 * Return the pointer to the base of the allocated memory. Whether is not 
 *   possible to allocate, returns -1.
 */
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



/** Set memory pointed with refered length to free. */
void simos_memory_free(simos_memory_t *mem, size_t pointer, size_t length)
{
    int i;
    for (i = pointer; i < (pointer + length); i++) {
        mem->cells[i] = 0;
    }
}

