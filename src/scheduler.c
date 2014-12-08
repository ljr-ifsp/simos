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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "simos.h"


/** Create a new ready process list. */
simos_scheduler_t *simos_scheduler_new()
{
	simos_scheduler_t *s = malloc(sizeof(simos_scheduler_t));

	s->ready = simos_list_new();

	return s;
}

/** Add a process in the list (FCFS policy). */
void simos_process_list_add(simos_list_t *proclist, simos_process_t *proc)
{
	simos_list_add(proclist, simos_list_new_node(proc));
}

/** private function the search a process... */
static simos_list_node_t *simos_process_list_search(simos_list_t *proclist, 
		int pid)
{
	simos_list_node_t *n;
	// for each node n in the process list do:
	SIMOS_LIST_FOREACH(n, proclist) {
		if (pid == ((simos_process_t *) n->data)->pid) {
			return n;
		}
	}

	return NULL;
}

/** Delete the process with the refered pid.  Return true or false. */
int simos_process_list_del(simos_list_t *proclist, int pid)
{
	simos_list_node_t *n = simos_process_list_search(proclist, pid);

	if (n != NULL) {
		return simos_list_del(proclist, n);
	} 

	return 0;
}

/** Get the process with the refered pid. Return simos_process_t*. */
simos_process_t *simos_process_list_get(simos_list_t *proclist, int pid)
{
	simos_list_node_t *p = simos_process_list_search(proclist, pid);

	if (p != NULL) {
		return ((simos_process_t *) p->data);
	}

	return NULL;
}

/** Sort process */
void simos_process_list_sort(simos_list_t *proclist, char *policy)
{
    int swapped;
    
    simos_list_node_t *ptr1;
    simos_list_node_t *lptr = NULL;

 	simos_process_t *value_1;
 	simos_process_t *value_2;

    do
    {
        swapped = 0;
        ptr1 = proclist->head;
 
        while (ptr1->next != lptr)
        {
        	value_1 = simos_node_to_process(ptr1);
        	value_2 = simos_node_to_process(ptr1->next);

        	if (strcasecmp("sjf", policy) == 0 || strcasecmp("srt", policy) == 0)
        	{
        		if (value_1->required_execution_time > value_2->required_execution_time)
	            {
	                swap(ptr1, ptr1->next);
	                swapped = 1;
	            }

	            ptr1 = ptr1->next;

        	} else if (strcasecmp("rrwp", policy) == 0)
        	{
        		if (value_1->priority < value_2->priority)
	            {
	                swap(ptr1, ptr1->next);
	                swapped = 1;
	            }
	            
	            ptr1 = ptr1->next;

        	} else {
        		fprintf(stderr, "[ERROR]: Policy not found!\n");
        		exit(EXIT_FAILURE);
        	}
        }
    }
    while (swapped);
}
 
/* Function to swap data of two nodes a and b*/
void swap(simos_list_node_t *a, simos_list_node_t *b)
{
    void *temp = a->data;
    a->data = b->data;
    b->data = temp;
}
