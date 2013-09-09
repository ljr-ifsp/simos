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
