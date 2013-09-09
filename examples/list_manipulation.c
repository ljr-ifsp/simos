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
#include <malloc.h>
#include <simos.h>




simos_list_node_t *new_node(int i)
{
	int *v = malloc(sizeof(int));
	simos_list_node_t *n = malloc(sizeof(simos_list_node_t));
	n->next = NULL;
	n->prev = NULL;
	*v = i;
	n->data = v;
	return n;
}

simos_list_node_t *get_elem(simos_list_t *l, int d)
{
	simos_list_node_t *n;
	SIMOS_LIST_FOREACH(n, l) {
		if (d == *((int *) (n->data))) {
			return n;
		}
	}
	return NULL;
}

int get_data(simos_list_node_t *n)
{
	return *((int *) n->data);
}

void print_list(simos_list_t *list)
{
	simos_list_node_t *n;
	printf("[LIST]: ");
	SIMOS_LIST_FOREACH(n, list) {
		printf("%d ", *((int *) n->data));
	}
	printf("\n");
}


int main(int argc, char *argv[])
{
	simos_list_t *l;
	simos_list_node_t *n;

	l = simos_list_new();

	simos_list_add(l, new_node(1));
	simos_list_add(l, new_node(2));
	simos_list_add(l, new_node(3));
	simos_list_add(l, new_node(4));

	n = get_elem(l, 2);
	printf("%d\n", get_data(n));
	print_list(l);

	n = get_elem(l, 2);
	if (simos_list_del(l, n)) {
		printf("%d deleted.\n", get_data(n));
	} else {
		printf("error deleting %d.\n", get_data(n));
	}
	print_list(l);

	if ((n = simos_list_del_head(l)) != NULL) {
		printf("head %d deleted.\n", get_data(n));
	} else {
		printf("error deleting head %d.\n", get_data(n));
	}
	print_list(l);

	if ((n = simos_list_del_tail(l)) != NULL) {
		printf("tail %d deleted.\n", get_data(n));
	} else {
		printf("error deleting tail %d.\n", get_data(n));
	}
	print_list(l);

	if (simos_list_del(l, n)) {
		printf("%d deleted.\n", get_data(n));
	} else {
		printf("error deleting %d.\n", get_data(n));
	}
	print_list(l);
	if (simos_list_del(l, n)) {
		printf("%d deleted.\n", get_data(n));
	} else {
		printf("error deleting %d.\n", get_data(n));
	}
	print_list(l);

	return 0;
}


