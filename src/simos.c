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
#include <stdlib.h>

#include "simos.h"

static size_t time = 0;
static FILE *global_fp = NULL;

/** Create a new simulation of a system with the memory size as specified. */
simos_t *simos_new(size_t memory_size)
{
	simos_t *s = malloc(sizeof(simos_t));

	s->sched = simos_scheduler_new();
	s->mem = simos_memory_create(memory_size);

	return s; 
}

simos_t *simos_new_with_priority(size_t memory_size, size_t priority_queue, char *queue_name)
{
	simos_t *s = simos_new(memory_size);
	s->sched->priority_queue = priority_queue;
	s->sched->queue_name = queue_name;

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
void simos_execute(void (*f)(simos_t *simos), simos_t *simos)
{
	(*f)(simos);
}

void simos_execute_MQ(simos_mq_t *simos_mq, size_t number_queues)
{
	simos_mq_t temp;
	int i, j;

	for (i = 0; i < number_queues; i++)
	{
		for (j = 0; j < number_queues; j++)
		{
			if (simos_mq[i].simos->sched->priority_queue >
				simos_mq[j].simos->sched->priority_queue)
			{
				temp = simos_mq[i];
				simos_mq[i] = simos_mq[j];
				simos_mq[j] = temp;

			}
		}
	}

	// Globals variable
	global_fp = fopen("../metrics/multiple_queue.txt", "w");

	for (i = 0; i < number_queues; i++)
	{
		// fprintf for writing in file of metrics
		time = 0;
		
		printf("\n//////////////////////////////////////////////////////////\n");
		fprintf(global_fp, "\n//////////////////////////////////////////////////////////\n");

		printf("%s, starts ... ", simos_mq[i].simos->sched->queue_name);
		fprintf(global_fp, "%s, starts ... ", simos_mq[i].simos->sched->queue_name);
		
		printf("\n//////////////////////////////////////////////////////////\n\n");
		fprintf(global_fp, "\n//////////////////////////////////////////////////////////\n\n");
		
		simos_execute(simos_mq[i].f, simos_mq[i].simos);
		
		global_fp = fopen("../metrics/multiple_queue.txt", "a");
	}

	fclose(global_fp);
}

/** After execution, the memory must be freed. */
void simos_free(simos_t *simos)
{
	simos_memory_destroy(simos->mem);
	simos_list_free(simos->sched->ready);
}

void simos_execute_FCFS(simos_t *simos)
{
	simos_list_node_t *n;
	simos_process_t *p;
	FILE *fp;

	if (global_fp == NULL)
		fp = fopen("../metrics/first_come_first_served.txt", "w");
	else
		fp = global_fp;

	// for each node in scheduler's ready list do:
	SIMOS_LIST_FOREACH(n, simos->sched->ready) { 
		printf("Current time is: %ld\n", time);
		fprintf(fp, "Current time is: %ld\n", time);

		/* time accounting */
		p = simos_node_to_process(n);
		p->entry_time = time;
		time += p->required_execution_time; // NOTE: there is no preemption
		p->out_time = time;

		simos_memory_free(simos->mem, p->memory_pointer, 
				p->required_memory);

		printf("Process %d leaving at %ld.\n", p->pid, time);
		fprintf(fp, "Process %d leaving at %ld.\n", p->pid, time);
	}

	fclose(fp);
}

void simos_execute_SJF(simos_t *simos)
{
	simos_list_node_t *n;
	simos_process_t *p;
	FILE *fp;
	
	time = 0;

	simos_process_list_sort(simos->sched->ready, "sjf");

	if (global_fp == NULL)
		fp = fopen("../metrics/shortest_job_first.txt", "w");
	else
		fp = global_fp;

	// for each node in scheduler's ready list do:
	SIMOS_LIST_FOREACH(n, simos->sched->ready) { 
		printf("Current time is: %ld\n", time);
		fprintf(fp, "Current time is: %ld\n", time);

		/* time accounting */
		p = simos_node_to_process(n);
		p->entry_time = time;
		time += p->required_execution_time; // NOTE: there is no preemption
		p->out_time = time;

		simos_memory_free(simos->mem, p->memory_pointer, 
				p->required_memory);

		printf("Process %d leaving at %ld.\n", p->pid, time);
		fprintf(fp, "Process %d leaving at %ld.\n", p->pid, time);
	}

	fclose(fp);
}

void simos_execute_RR(simos_t *simos)
{
	simos_list_node_t *n;
	simos_process_t *p;
	simos_list_t *proclist;
	FILE *fp;

	time = 0;

	if (global_fp == NULL)
		fp = fopen("../metrics/round_robin.txt", "w");
	else
		fp = global_fp;

	do
	{
		proclist = simos->sched->ready;

		SIMOS_LIST_FOREACH(n, proclist) {
			printf("Current time is: %ld\n", time);
			fprintf(fp, "Current time is: %ld\n", time);

			p = simos_node_to_process(n);
			time += p->quantum;
			p->required_execution_time -= p->quantum;

			printf("Process %d leaving at %ld.\n", p->pid, time);
			fprintf(fp, "Process %d leaving at %ld.\n", p->pid, time);

			if (((int)p->required_execution_time) < 1)
			{
				printf("*** Process %d termined. ***\n", p->pid);
				fprintf(fp, "*** Process %d termined. ***\n", p->pid);
				simos_list_del(proclist, n);
			}
		}

	} while (!simos_list_empty(proclist));

	fclose(fp);
}

void simos_execute_RRWP(simos_t *simos)
{
	simos_list_node_t *n;
	simos_process_t *p;
	FILE *fp;

	time = 0;

	if (global_fp == NULL)
		fp = fopen("../metrics/round_robin_with_priority.txt", "w");
	else
		fp = global_fp;
	
	simos_process_list_sort(simos->sched->ready, "rrwp");


	// for each node in scheduler's ready list do:
	SIMOS_LIST_FOREACH(n, simos->sched->ready) { 
		printf("Current time is: %ld\n", time);
		fprintf(fp, "Current time is: %ld\n", time);

		/* time accounting */
		p = simos_node_to_process(n);
		p->entry_time = time;
		time += p->required_execution_time; // NOTE: there is no preemption
		p->out_time = time;

		simos_memory_free(simos->mem, p->memory_pointer, 
				p->required_memory);

		printf("Process %d leaving at %ld. Process priority equals %ld.\n", p->pid, time, p->priority);
		fprintf(fp, "Process %d leaving at %ld. Process priority equals %ld.\n", p->pid, time, p->priority);
	}

	fclose(fp);
}

void simos_execute_SRT(simos_t *simos)
{
	simos_list_node_t *n;
	simos_process_t *p;
	simos_list_t *proclist;
	FILE *fp;

	time = 0;

	if (global_fp == NULL)
		fp = fopen("../metrics/shortest_remaining_time.txt", "w");
	else
		fp = global_fp;

	simos_process_list_sort(simos->sched->ready, "srt");

	do
	{
		proclist = simos->sched->ready;

		SIMOS_LIST_FOREACH(n, proclist) {
			printf("Current time is: %ld\n", time);
			fprintf(fp, "Current time is: %ld\n", time);

			p = simos_node_to_process(n);
			time += p->quantum;
			p->required_execution_time -= p->quantum;

			printf("Process %d leaving at %ld.\n", p->pid, time);
			fprintf(fp, "Process %d leaving at %ld.\n", p->pid, time);

			if (((int)p->required_execution_time) < 1)
			{
				printf("*** Process %d termined. ***\n", p->pid);
				fprintf(fp, "*** Process %d termined. ***\n", p->pid);
				simos_list_del(proclist, n);
			}
		}

	} while (!simos_list_empty(proclist));

	fclose(fp);
}
