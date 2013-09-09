CC = gcc
INCLUDES = -I../include
SIMOS = ../lib/libsimos.a

all: list_manipulation proc_test simulation

list_manipulation: list_manipulation.c $(SIMOS)
	$(CC) $(INCLUDES)  list_manipulation.c $(SIMOS) -o list_manipulation

proc_test: proc_test.c $(SIMOS)
	$(CC) $(INCLUDES)  proc_test.c $(SIMOS) -o proc_test

simulation: simulation.c $(SIMOS)
	$(CC) $(INCLUDES)  simulation.c $(SIMOS) -o simulation


clean:
	rm -f list_manipulation proc_test simulation


