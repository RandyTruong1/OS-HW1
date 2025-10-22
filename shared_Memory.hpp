#ifndef SHARED_MEMORY_HPP
#define SHARED_MEMORY_HPP

#include <semaphore.h>

// Shared memory name
#define SHM_NAME "/table_shm"

// Buffer can hold up to 2 items
#define BUFFER_SIZE 2

// Struct stored in shared memory
struct SharedTable 
{
    int buffer[BUFFER_SIZE]; // Buffer
    int counter;             // Number of items in buffer
    int item_id;             // global item counter
    sem_t empty;             // Counts empty slots
    sem_t full;              // Counts filled slots
    sem_t mutex;             // Make sure only one thing changes the buffer at a time.
};

#endif