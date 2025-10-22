# OS-HW1
Topic: Producer-Consumer Problem

This code runs a producer and consumer program simultaneously, like the Producer-Consumer Problem we have studied in class.
The expected result is for the Producer is to produce an "item" and then the Consumer to consume the item, having them run together using semaphores, shared memory, and mutual exclusion to run nicely 
without interrupting each other, without getting caught in an infinite loop.

USAGE GUIDE:

I used Windows Visual Studio Code, and I downloaded WSL (Windows Subsystem for Linux) and used Ubuntu to run my code.

1. Download all files
2. Make sure all files are there by typing "ls"
3. Type ./producer & ./consumer & to run the program

Extras:

1. If the producer and consumer run files aren't in the "ls", then typing "make".
2. There might be a time when the code messes up and starts going crazy. I would type into the terminal "make clean" then "make"

Key Components:

Semaphores

Semaphores make sure that the producer waits when the table (buffer) is full and the consumer waits when the table is empty.

Mutual Exclusion

Mutex Locks make sure that the producer and consumer never try to modify the buffer at the same time.

Shared Memory

The producer and consumer are both able to use the SharedTable to access and modify the buffer.

EXAMPLE OUTPUT SCREENSHOT:

<img width="187" height="221" alt="image" src="https://github.com/user-attachments/assets/e8e106e3-fadf-41eb-b860-2503daaa6594" />
