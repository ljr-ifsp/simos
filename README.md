simos
=====

SIMulation of Operating System.


Code organization
=================

To compile use

	make

`simos' is a static library code. After compiling it, check

	lib/libsimos.a

for the binary.

Directories in the project are:
-------------------------------


- include/

	The directory include has `simos.h' which has the declaration and 
	prototype of every resource available with simos.

- src/

	Directory containing the codes:
	
		* simos.c : basic functions to create simulations. Call these 
			functions to write a simulator. It has a provisory
			'time' variable to take care about the simulation time.
			If you need to export this variable, try remove
			'static' and declare it as 'extern' in the simulator.

		* memory.c: create an array of unsigned char representing cells
			just like in real computer systems. In memory.c must be 
			implemented memory management issues.

		* scheduler.c: has a 'ready' process list and functions to add 
			and remove process to the simulated system. Scheduling 
			policies must be implemented in this file. As a good 
			practice is suggested to put the next process in the 
			head of the list. To implement preemptive issues, 
			the processor exiting process must be inserted again,
			so the insert algorithm should tackle with position 
			where the process will be placed in the list. For
			example, for the Round-robin policy, just insert a
			process in the very last position.

		* process.c: process' structure. Information of the process. 
			Add metrics here. For example, insert arrival_time in
			the system.

		* list.c: a generic approach for the list of process. Sometimes
			it will be hard to distinguish if a code should be 
			inserted in scheduler.c or list.c. A simple guideline 
			is: whether code is not dependent of the policy, put it
			in list.c, otherwise in scheduler.c. 

- examples/

	Directory containing examples of use. Check `simulation.c' for a simple
	FCFS non-preemptive simulation.



Author
=====

The code was spawned in Sep 7, 2013 by 

	Lourenco Alves 
	São Paulo's Federal Institute of Technology
	Araraquara, SP - Brazil
	(ljr[dot]ifsp gmail)
	http://ljr.sdf.org

This project is intented to help Operating System classes by enabling a
simple but sufficient start up for labs like Scheduling policies and 
Memory management implementations.

You are strongly encouraged to report bugs and contribute to 
this project.


Long live and prosper.

\\\\//


