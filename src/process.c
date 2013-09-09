
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




