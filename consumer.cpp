#include <iostream>
#include <thread>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "shared_memory.hpp"

using namespace std;

void consumer(SharedTable* table) 
{
    int next_consumed;
    int out = 0;

    while (true) 
    {
        /* Wait if buffer empty */
        sem_wait(&table->full);
        sem_wait(&table->mutex);

        /* Remove item from buffer */
        next_consumed = table->buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        table->counter--;

        /* Print confirm with number*/
        cout << "Consumer: consumed item " << next_consumed << endl;

        /* Release sem */
        sem_post(&table->mutex);
        sem_post(&table->empty);

        this_thread::sleep_for(chrono::seconds(2)); // Slows down for readabilitiy 
    }
}

int main() 
{
    /* Opens shared memory */
    int fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (fd == -1) 
    {
        cerr << "Shared memory not found." << endl;
        exit(1);
    }

    /* Uses map memory */
    auto* table = static_cast<SharedTable*>(mmap(nullptr, sizeof(SharedTable), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    /* Run consumer */
    thread consumerThread(consumer, table);
    consumerThread.join();

    munmap(table, sizeof(SharedTable));
    close(fd);
    return 0;
}
