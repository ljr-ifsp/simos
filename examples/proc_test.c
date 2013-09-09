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

void print_list(simos_list_t *list)
{
	simos_list_node_t *n; 
	printf("[LIST]: ");
	SIMOS_LIST_FOREACH(n, list) {
		printf("%d ", ((simos_process_t *) n->data)->pid);
	}
	printf("\n");
}


int main(int argc, char *argv[])
{
	simos_list_t *pl;
	simos_process_t *p;


	pl = simos_list_new();

	simos_process_list_add(pl, simos_process_create(1, 10, 10));
	simos_process_list_add(pl, simos_process_create(2, 20, 20));
	simos_process_list_add(pl, simos_process_create(3, 30, 30));
	simos_process_list_add(pl, simos_process_create(4, 40, 40));
	simos_process_list_add(pl, simos_process_create(5, 50, 50));
	print_list(pl);

	simos_process_list_del(pl, 1);
	simos_process_list_del(pl, 3);
	print_list(pl);

	if ((p = simos_process_list_get(pl, 2)) != NULL) {
		printf("%d\n", p->pid);
	}

	if ((p = simos_process_list_get(pl, 3)) != NULL) {
		printf("%d\n", p->pid);
	} else {
		printf("oops no process...\n");
	}


	return 0;
}
