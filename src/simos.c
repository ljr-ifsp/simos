#include <malloc.h>
#include "simos.h"

static size_t time = 0;


simos_t *simos_new(size_t memory_size)
{
	simos_t *s = malloc(sizeof(simos_t));

	s->sched = simos_scheduler_new();
	s->mem = simos_memory_create(memory_size);

	return s; 
}

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

void simos_execute(simos_t *simos)
{
	simos_list_node_t *n;
	simos_process_t *p;

	SIMOS_LIST_FOREACH(n, simos->sched->ready) {
		printf("Current time is: %ld\n", time);

		/* time accounting */
		p = simos_node_to_process(n);
		p->entry_time = time;
		time += p->required_execution_time;
		p->out_time = time;

		simos_memory_free(simos->mem, p->memory_pointer, p->required_memory);

		printf("Process %d leaving at %ld.\n", p->pid, time);
	}
}

void simos_free(simos_t *simos)
{
	free(simos->mem);
	simos_list_free(simos->sched->ready);
}



