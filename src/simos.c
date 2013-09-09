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

static size_t time = 0;


/** Create a new simulation of a system with the memory size as specified. */
simos_t *simos_new(size_t memory_size)
{
	simos_t *s = malloc(sizeof(simos_t));

	s->sched = simos_scheduler_new();
	s->mem = simos_memory_create(memory_size);

	return s; 
}

/** Add a process to the scheduler. */
int simos_add_process(simos_t *simos, simos_process_t *proc)
{
	size_t pointer = simos_memory_alloc(simos->mem, proc->required_memory);

	if (pointer == -1) {
		return 0;
	}

	proc->memory_pointer = pointer;
	simos_process_list_add(simos->sched->ready, proc);

	return 1;
}

/** Execute the simulation... */
void simos_execute(simos_t *simos)
{
	simos_list_node_t *n;
	simos_process_t *p;

	// for each node in scheduler's ready list do:
	SIMOS_LIST_FOREACH(n, simos->sched->ready) { 
		printf("Current time is: %ld\n", time);

		/* time accounting */
		p = simos_node_to_process(n);
		p->entry_time = time;
		time += p->required_execution_time; // NOTE: there is no preemption
		p->out_time = time;

		simos_memory_free(simos->mem, p->memory_pointer, 
				p->required_memory);

		printf("Process %d leaving at %ld.\n", p->pid, time);
	}
}

/** After execution, the memory must be freed. */
void simos_free(simos_t *simos)
{
	simos_memory_destroy(simos->mem);
	simos_list_free(simos->sched->ready);
}



