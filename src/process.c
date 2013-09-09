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
#include <malloc.h>
#include "simos.h"

simos_process_t *simos_process_create(int pid, size_t required_execution_time, 
        size_t required_memory)
{
	simos_process_t *proc = (simos_process_t *) malloc(sizeof(simos_process_t));

	proc->pid = pid;
	proc->required_execution_time = required_execution_time;
	proc->required_memory = required_memory;
	proc->turnaround_time = required_execution_time;
	proc->memory_pointer = -1;

	return proc;
}

void simos_process_destroy(simos_process_t *proc)
{
	free(proc);
}

simos_process_t *simos_node_to_process(simos_list_node_t *node)
{
	return ((simos_process_t *) node->data);
}




