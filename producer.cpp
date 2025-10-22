#include <iostream>
#include <thread>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "shared_memory.hpp"

using namespace std;

void producer(SharedTable* table)
{
    int next_produced;
    int in = 0;

    std::cout << "\n";

    while (true) 
    {
        /* Wait if buffer full */
        sem_wait(&table->empty);
        sem_wait(&table->mutex);

        // increment item counter
        table->item_id++;
        next_produced = table->item_id;

        /* Puts item in buffer */
        table->buffer[in] = next_produced;
        in = (in + 1) % BUFFER_SIZE;
        table->counter++;

        /* Print confirm with number*/
        cout << "Producer: produced item " << next_produced << endl;

        /* Release sem */
        sem_post(&table->mutex);
        sem_post(&table->full);


        this_thread::sleep_for(chrono::seconds(1)); // Slows down the code for 1 second to read easier
    }
}

int main() 
{
    /* Creates shared memory */
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) 
    {
        perror("shm_open");
        exit(1);
    }

    /* Sets size */
    ftruncate(fd, sizeof(SharedTable));

    /* Shared map */
    auto* table = static_cast<SharedTable*>(mmap(nullptr, sizeof(SharedTable), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    /* Variables */
    table->counter = 0;
    table->item_id = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) 
    {
        table->buffer[i] = 0;
    }

    sem_init(&table->empty, 1, BUFFER_SIZE);
    sem_init(&table->full, 1, 0);
    sem_init(&table->mutex, 1, 1);

    /* Run producer */
    thread producerThread(producer, table);
    producerThread.join();

    munmap(table, sizeof(SharedTable));
    close(fd);
    return 0;
}
