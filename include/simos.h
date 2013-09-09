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

/**
 * A node contains a void* pointer, user can insert a pointer to 
 * any data wanted
 */
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

/** Create a new simos_list_t* pointing to NULL. */
simos_list_t *simos_list_new();
/*============================================================================
 | All list parameters must be a valid pointer. Otherwise, bad pointer error. 
 +--------------------------------------------------------------------------*/
/** Create a new node, next and prev NULL and data pointing to the parameter. */
simos_list_node_t *simos_list_new_node(void *data);
/** Check whether list is empty, but list should be a valid parameter. */
int simos_list_empty(simos_list_t *list);
/** Add a new node at tail of the list. */
void simos_list_add(simos_list_t *list, simos_list_node_t *node);
/** Find the node and delete it. Return true or false. */
int simos_list_del(simos_list_t *list, simos_list_node_t *node);
/** Delete the very first node in the list. */
simos_list_node_t *simos_list_del_head(simos_list_t *list);
/** Delete the very last node in the list. */
simos_list_node_t *simos_list_del_tail(simos_list_t *list);
/** Delete all nodes in the list AND ALSO THE DATA. */
void simos_list_free(simos_list_t *list);

/** Simple macro meaning: for every `var' into the `list' */
#define SIMOS_LIST_FOREACH(var, list)					\
	for ((var) = ((list)->head);					\
			(var);						\
			(var) = ((var)->next))



/***********************************************************************
 * process declarations 
 **********************************************************************/

/** Process information. */
typedef struct {
	/** Process' identifier. */
	int pid; 
	/** Units of time required for executing the process. */
	size_t required_execution_time; 
	/** Turnaround time. */
	size_t turnaround_time;
	/** Amount of memory required for the process.  */
	size_t required_memory;
	/** Memory pointer where the process was allocated in the memory. */
	size_t memory_pointer;
	/** Time at process' creation. */
	size_t entry_time;
	/** Time at process' tear down. */
	size_t out_time;
} simos_process_t;

/** Create a new process. */
simos_process_t *simos_process_create(int pid, size_t required_execution_time, 
		size_t required_memory);
/** Just call free (malloc(3)) in proc. */
void simos_process_destroy(simos_process_t *proc);
/** Type cast in node->data to simos_process_t. */
simos_process_t *simos_node_to_process(simos_list_node_t *node);


/***********************************************************************
 * scheduler declararions
 **********************************************************************/

typedef struct {
	simos_list_t *ready;
} simos_scheduler_t;

/** Create a new ready process list. */
simos_scheduler_t *simos_scheduler_new();
/** Add a process in the list (FCFS policy). */
void simos_process_list_add(simos_list_t *proclist, simos_process_t *proc);
/** Delete the process with the refered pid. Return true or false. */
int simos_process_list_del(simos_list_t *proclist, int pid);
/** Get the process with the refered pid. Return simos_process_t*. */
simos_process_t *simos_process_list_get(simos_list_t *proclist, int pid);

    /*==========================================================*/
    /*-------- New policies must be implemented here... --------*/
    /*==========================================================*/



/***********************************************************************
 * Memory management functions
 **********************************************************************/

typedef struct {
	size_t size;
	unsigned char *cells;
} simos_memory_t;

/** Create a memory with the refered size. */
simos_memory_t *simos_memory_create(size_t size);
/** Call free (malloc(3)) in the allocated memory. */
void simos_memory_destroy(simos_memory_t *mem);
/**
 * Try to find a gap in the memory that fits the block size. 
 *
 * Return the pointer to the base of the allocated memory. Whether is not 
 *   possible to allocate, returns -1.
 */
size_t simos_memory_alloc(simos_memory_t *mem, size_t block);
/** Set memory pointed with refered length to free. */
void simos_memory_free(simos_memory_t *mem, size_t pointer, size_t length);



/***********************************************************************
 * simos declarations 
 **********************************************************************/

typedef struct {
	simos_scheduler_t *sched;
	simos_memory_t *mem;
} simos_t;

/** Create a new simulation of a system with the memory size as specified. */
simos_t *simos_new(size_t memory_size);
/** Add a process to the scheduler. */
int simos_add_process(simos_t *simos, simos_process_t *proc);
/** Execute the simulation... */
void simos_execute(simos_t *simos);
/** After execution, the memory must be freed. */
void simos_free(simos_t *simos);



#ifdef	__cplusplus
}
#endif

#endif


