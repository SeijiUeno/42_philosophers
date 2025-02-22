The classic Dining Philosophers problem!

Overview of The Problem

You have a fixed number of philosophers sitting around a circular table.
Each philosopher needs two forks to eat from a shared bowl of spaghetti.
Each philosopher has a cycle of thinking, eating, and sleeping.
The challenge is to design a solution that prevents deadlocks (where everyone is waiting for a fork) 
and starvation (where a philosopher never gets to eat).

Key Concepts

- Threads: Each philosopher will be represented as a separate thread, allowing them to act concurrently.   
Mutexes: Mutexes (mutual exclusion) will be used to protect the forks. Only one philosopher can hold a given mutex (and therefore the fork) at a time.   
Synchronization: Carefully manage how philosophers acquire and release forks to avoid the classic dining philosophers' pitfalls.

Library

- <pthread.h>
This header file provides the necessary functions and data structures for working with threads in C. 
It includes functions like pthread_create(), pthread_join(), pthread_mutex_init(), and more.
- !Compiler Directive!: You'll typically need to include the "-lpthread" directive when compiling your code. 
This tells the linker to include the pthread library, which contains the actual implementations of the thread functions.

compile without Makefile:
- gcc -Wall -Wextra -Werror -lpthread *.c -o philo

You can use Valgrind’s Helgrind tool to check for threading issues:
- valgrind --tool=helgrind --log-file=helgrind.log ./philo

compile with Makefile:
- Make 
- ./philo 
