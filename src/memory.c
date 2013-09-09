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


