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
#include <stdio.h>
#include <simos.h>

void execute_FCFS();
void execute_SJF();
void execute_SRT();
void execute_RR();
void execute_RRWP();
void execute_MQ();

int main(int argc, char *argv[])
{
    execute_FCFS();
    execute_SJF();
    execute_SRT();
    execute_RR();
    execute_RRWP();
    execute_MQ();
    
    return 0;
}

void execute_FCFS()
{
    int i;

    simos_t *s = simos_new(100);

    printf("\n================================\n");
    printf("First Come First Served. [FCSF]");
    printf("\n================================\n");

    for (i = 0; i < 3; i++) {
        simos_add_process(s, simos_process_create(i, 8, 8));
    }
    simos_execute(simos_execute_FCFS, s);
    simos_free(s);
}

void execute_SJF()
{
    simos_t *s = simos_new(100);
    
    printf("\n================================\n");
    printf("Shortest Job First. [SJF]");
    printf("\n================================\n");

    simos_add_process(s, simos_process_create(1, 10, 10));
    simos_add_process(s, simos_process_create(3, 4, 4));
    simos_add_process(s, simos_process_create(2, 1, 1));

    simos_execute(simos_execute_SJF, s);
    simos_free(s);
}

void execute_SRT()
{
    simos_t *s = simos_new(100);

    const size_t QUANTUM = 5;
    
    printf("\n================================\n");
    printf("Shortest Remaning Time. [SRT]");
    printf("\n================================\n");

    // simos_process_create_with_quantum(int pid, size_t required_execution_time, size_t required_memory, size_t quantum)
    simos_add_process(s, simos_process_create_with_quantum(1, 10, 10, QUANTUM));
    simos_add_process(s, simos_process_create_with_quantum(2, 1, 1, QUANTUM));
    simos_add_process(s, simos_process_create_with_quantum(3, 6, 6, QUANTUM));

    simos_execute(simos_execute_SRT, s);
    simos_free(s);
}

void execute_RR()
{
    simos_t *s = simos_new(100);
    
    const size_t QUANTUM = 5;

    printf("\n================================\n");
    printf("Round Robin. [RR]");
    printf("\n================================\n");

    // simos_process_create_with_quantum(int pid, size_t required_execution_time, size_t required_memory, size_t quantum)
    simos_add_process(s, simos_process_create_with_quantum(1, 18, 18, QUANTUM));
    simos_add_process(s, simos_process_create_with_quantum(2, 7, 7, QUANTUM));
    simos_add_process(s, simos_process_create_with_quantum(3, 35, 35, QUANTUM));

    simos_execute(simos_execute_RR, s);
    simos_free(s);
}

void execute_RRWP()
{
    simos_t *s = simos_new(100);
    
    const size_t QUANTUM = 5;

    printf("\n================================\n");
    printf("Round Robin With Priority. [RRWP]");
    printf("\n================================\n");

    // simos_process_create_with_priority(int pid, size_t required_execution_time, size_t required_memory, size_t quantum, size_t priority)
    simos_add_process(s, simos_process_create_with_priority(1, 18, 18, QUANTUM, 8));
    simos_add_process(s, simos_process_create_with_priority(2, 7, 7, QUANTUM, 14));
    simos_add_process(s, simos_process_create_with_priority(3, 35, 35, QUANTUM, 2));

    simos_execute(simos_execute_RRWP, s);
    simos_free(s);
}

void execute_MQ()
{
    const int NUMBER_QUEUES = 3;
    simos_mq_t s[NUMBER_QUEUES];
    
    const size_t QUANTUM = 5;

    const void *POLICYS[] = {
        simos_execute_FCFS,
        simos_execute_RRWP,
        simos_execute_RR
    };

    printf("\n================================\n");
    printf("Multiple Queue. [MQ]");
    printf("\n================================\n");

    s[0].simos = simos_new_with_priority(100, 5, "Queue One");
    s[0].f = POLICYS[0];
    simos_add_process(s[0].simos, simos_process_create_with_priority(1, 24, 24, QUANTUM, 8));
    simos_add_process(s[0].simos, simos_process_create_with_priority(2, 6, 6, QUANTUM, 8));
    simos_add_process(s[0].simos, simos_process_create_with_priority(3, 19, 19, QUANTUM, 8));

    s[1].simos = simos_new_with_priority(100, 1, "Queue Two");
    s[1].f = POLICYS[1];
    simos_add_process(s[1].simos, simos_process_create_with_priority(1, 24, 24, QUANTUM, 8));
    simos_add_process(s[1].simos, simos_process_create_with_priority(2, 6, 6, QUANTUM, 1));
    simos_add_process(s[1].simos, simos_process_create_with_priority(3, 19, 19, QUANTUM, 10));

    s[2].simos = simos_new_with_priority(100, 20, "Queue Three");
    s[2].f = POLICYS[2];
    simos_add_process(s[2].simos, simos_process_create_with_priority(1, 24, 24, QUANTUM, 8));
    simos_add_process(s[2].simos, simos_process_create_with_priority(2, 6, 6, QUANTUM, 8));
    simos_add_process(s[2].simos, simos_process_create_with_priority(3, 19, 19, QUANTUM, 8));

    simos_execute_MQ(s, NUMBER_QUEUES);
}
