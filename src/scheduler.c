#include <malloc.h>
#include "simos.h"


simos_scheduler_t *simos_scheduler_new()
{
	simos_scheduler_t *s = malloc(sizeof(simos_scheduler_t));

	s->ready = simos_list_new();

	return s;
}

void simos_process_list_add(simos_list_t *proclist, simos_process_t *proc)
{
	simos_list_node_t *n = malloc(sizeof(simos_list_node_t));

	n->next = NULL;
	n->prev = NULL;
	n->data = proc;

	simos_list_add(proclist, n);
}

static simos_list_node_t *simos_process_list_search(simos_list_t *proclist, int pid)
{
	simos_list_node_t *n;
	SIMOS_LIST_FOREACH(n, proclist) {
		if (pid == ((simos_process_t *) n->data)->pid) {
			return n;
		}
	}

	return NULL;
}

int simos_process_list_del(simos_list_t *proclist, int pid)
{
	simos_list_node_t *n = simos_process_list_search(proclist, pid);

	if (n != NULL) {
		return simos_list_del(proclist, n);
	} 

	return 0;
}

simos_process_t *simos_process_list_get(simos_list_t *proclist, int pid)
{
	simos_list_node_t *p = simos_process_list_search(proclist, pid);

	if (p != NULL) {
		return ((simos_process_t *) p->data);
	}

	return NULL;
}



