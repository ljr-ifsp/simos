#include <stdio.h>
#include <simos.h>

int main(int argc, char *argv[])
{
	int i;
	simos_t *s = simos_new(100);

	for (i = 0; i < 10; i++) {
		simos_add_process(s, simos_process_create(i, 8, 8));
	}
	simos_execute(s);

	simos_free(s);
	return 0;
}

