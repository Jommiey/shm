/* 
 * mmap program to act as a producer of messages using shared memory. 
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SHMSIZE 4096

int main()
{
    // Name of the shared memory object.
    const char* shm_name = "shmtest";

    // Message to send to the shared memory.
    const char* message = "nice";

    // Create shared memory object and truncate it.
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHMSIZE);

    // Pointer to the shared memory.
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED;
    void* ptr = mmap(0, SHMSIZE, protection, visibility, shm_fd, 0);

    // Write to the shared memory.
    sprintf(ptr, "%s", message);

    // Wait until we get a response from the client.
    while(strcmp(ptr, "*") != 0)
    {
        printf("Waiting for a response...\n", ptr);
        sleep(1);
    }
    printf("Got a response. Shutting down...\n");
    return 0;
}
