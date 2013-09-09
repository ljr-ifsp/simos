simos
=====

Simulation of Operating System.


Code organization
=================

To compile use

	make

`simos' is static library code. After compiling it, check

	lib/libsimos.a

for the binary.

Directories in the project are:


- include/

	The directory include has `simos.h' which is the declaration and 
	prototype of every resource available with simos.

- src/

	Directory containing the codes:
		* simos.c : basic functions of the simulator. Call these 
			functions to write a simulator. It has a provisory
			time variable to take care about the simulation time.
			It may necessary export time variable, to do so, remove
			'static' and declare time as `extern' in the simulator.

		* memory.c: create a array of unsigned char representing cells
			just like in real systems. In it must be implemented
			memory management issues.

		* scheduler.c: has a ready process list and functions to add 
			and remove process. Scheduling policies must be 
			implemented there. A good practice is put the next 
			process in the head of the list. For preemptive issues, 
			the processor exiting process must be inserted again,
			so the inser algorithm should tackle with the its 
			position in the list. For round-robin, just insert in
			the very last position.

		* process.c: process' structure. Information of the process. 
			Add metrics here. For example, insert arrival_time in
			the system.

		* list.c: a generic approach for the list of process. Sometimes
			it may be hard distinguish a code should be inserted in
			scheduler.c or list.c. A guideline is: whether code is
			not dependent of the policy, put it in list.c, otherwise
			in scheduler.c. 

- examples/

	Directory containing examples of use. Check `simulation.c' for a simple
	FCFS non-preemptive simulation.



Author
=====

The code was forked in Sep 7, 2013 by 

	Lourenco Alves 
	Federal Institute of Technology at São Paulo
	Araraqara, SP - Brazil
	(ljr[dot]ifsp gmail)
	http://ljr.sdf.org

This project is intented to help Operating System class, by enabling a
simple but sufficient start up for labs like Scheduling policies and 
Memory management implementations.

You are strongly encouraged to report bugs and contribute to 
this project.


Long live and prosper.

\\\\//


