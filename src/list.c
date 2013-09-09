#include <malloc.h>
#include "simos.h"

/**
 * Is the list empty?
 */
int simos_list_empty(simos_list_t *list)
{
	return list->head == NULL;
}

/**
 * Allocate room for a list.
 */
simos_list_t * simos_list_new()
{
	simos_list_t *l = malloc(sizeof(simos_list_t));
	l->head = NULL;
	l->tail = NULL;
	return l;
}

/**
 * Add a node at tail of the queue.
 */
void simos_list_add(simos_list_t *list, simos_list_node_t *node)
{
	/* whether the list is empty */
	if (simos_list_empty(list)) {
		list->head = node;
		list->tail = node;
		return;	
	}

	node->prev = list->tail;
	list->tail->next = node;
	list->tail = node;
}

/**
 * Delete an especific node in the list.
 */
int simos_list_del(simos_list_t *list, simos_list_node_t *node)
{
	simos_list_node_t *n;

	if (simos_list_empty(list)) {
		return 0;
	}

	if (list->head == list->tail) {
		list->head = list->tail = NULL;
		return 1;
	}

	SIMOS_LIST_FOREACH(n, list) {
		if (n->next == node->next && n->prev == node->prev) {
			if (n == list->tail) {
				n->prev->next = NULL;
				list->tail = n->prev;
			} else if (n == list->head) {
				n->next->prev = NULL;
				list->head = n->next;
			} else {
				n->prev->next = n->next;
				n->next->prev = n->prev;
			}

			return 1;
		}
	}
	
	// node not found.
	return 0;
}

/**
 * Delete the first node in the list.
 */
simos_list_node_t *simos_list_del_head(simos_list_t *list)
{
	simos_list_node_t *n = list->head;

	if (simos_list_empty(list)) {
		return NULL;
	}

	if (list->head == list->tail) {
		list->head = NULL;
		list->tail = NULL;
	} else {
		list->head->next->prev = NULL;
		list->head = list->head->next;
	}

	return n;
}

/**
 * Delete the last node in the list.
 */
simos_list_node_t *simos_list_del_tail(simos_list_t *list)
{
	simos_list_node_t *n = list->tail;

	if (simos_list_empty(list)) {
		return NULL;
	}

	if (list->head == list->tail) {
		list->head = NULL;
		list->tail = NULL;
	} else {
		list->tail->prev->next = NULL;
		list->tail = list->tail->prev;
	}

	return n;
}

/**
 * Free all pointers in the list.
 */
void simos_list_free(simos_list_t *list)
{
	simos_list_node_t *n;
	SIMOS_LIST_FOREACH(n, list) {
		free(n->data);
		free(n);
	}
}


