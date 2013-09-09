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
#ifndef SIMOS_H
#define SIMOS_H

#ifdef	__cplusplus
extern "C" {
#endif


/***********************************************************************
 * list declarations 
 **********************************************************************/

struct simos_list_node {
	void *data;
	struct simos_list_node *next;
	struct simos_list_node *prev;
};
typedef struct simos_list_node simos_list_node_t;

typedef struct simos_list {
	simos_list_node_t *head;
	simos_list_node_t *tail;
} simos_list_t;

simos_list_t *simos_list_new();
simos_list_node_t *simos_list_new_node(void *data);
int simos_list_empty(simos_list_t *list);
void simos_list_add(simos_list_t *list, simos_list_node_t *node);
int simos_list_del(simos_list_t *list, simos_list_node_t *node);
simos_list_node_t *simos_list_del_head(simos_list_t *list);
simos_list_node_t *simos_list_del_tail(simos_list_t *list);
void simos_list_free(simos_list_t *list);

#define SIMOS_LIST_FOREACH(var, list)					\
	for ((var) = ((list)->head);					\
			(var);						\
			(var) = ((var)->next))



/***********************************************************************
 * process declarations 
 **********************************************************************/

typedef struct {
	/** Process' identifier */
	int pid; 
	/** Units of time required for executing the process. */
	size_t required_execution_time; 
	/** Turnaround time. */
	size_t turnaround_time;
	/** Amount of memory required for the process.  */
	size_t required_memory;
	/** Memory pointer where the process was allocated in the memory */
	size_t memory_pointer;
	/** Time at process' creation */
	size_t entry_time;
	/** Time at process' tear down */
	size_t out_time;
} simos_process_t;

simos_process_t *simos_process_create(int pid, 
        size_t required_execution_time, size_t required_memory);
void simos_process_destroy(simos_process_t *proc);
simos_process_t *simos_node_to_process(simos_list_node_t *node);


/***********************************************************************
 * scheduler declararions
 **********************************************************************/

typedef struct {
	simos_list_t *ready;
} simos_scheduler_t;

simos_scheduler_t *simos_scheduler_new();
void simos_process_list_add(simos_list_t *proclist, simos_process_t *proc);
int simos_process_list_del(simos_list_t *proclist, int pid);
simos_process_t *simos_process_list_get(simos_list_t *proclist, int pid);



/***********************************************************************
 * Memory management functions
 **********************************************************************/

typedef struct {
	size_t size;
	unsigned int *cells;
} simos_memory_t;


simos_memory_t *simos_memory_create(size_t size);
void simos_memory_destroy(simos_memory_t *mem);
size_t simos_memory_alloc(simos_memory_t *mem, size_t block);
void simos_memory_free(simos_memory_t *mem, size_t pointer, size_t length);



/***********************************************************************
 * simos declarations 
 **********************************************************************/

typedef struct {
	simos_scheduler_t *sched;
	simos_memory_t *mem;
} simos_t;

simos_t *simos_new(size_t memory_size);
int simos_add_process(simos_t *simos, simos_process_t *proc);
void simos_execute(simos_t *simos);
void simos_free(simos_t *simos);



#ifdef	__cplusplus
}
#endif

#endif


