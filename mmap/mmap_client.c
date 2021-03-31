/* 
 * mmap program to act as a consumer of messages using shared memory. 
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define SHMSIZE 4096

static volatile int run = 1;
void* ptr;

// SIGINT handler used to tell server we don't want any more messages.
void intHandler(int sig)
{
    printf("Caught SIGINT signal, exiting program.\n");
    sprintf(ptr, "%s", "*");
    //run = 0;
}

int main()
{
    // Set up interrupt signal
    signal(SIGINT, intHandler);

    // Name of the shared memory object.
    const char* name = "shmtest";

    // Create shared memory object.
    int shm_fd = shm_open(name, O_RDWR, 0666);

    // Pointer to the shared memory.
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED;
    ptr = mmap(0, SHMSIZE, protection, visibility, shm_fd, 0);

    // Read from shared memory.
    /* while(run) */
    /* { */
    /*     printf("%s", (char*) ptr); */
    /*     sleep(1); */
    /* } */
    int sig;
    sigset_t signal_set;
    sigemptyset(&signal_set);
    sigaddset(&signal_set, SIGINT);
    sigwait(&signal_set, &sig);
    printf("After");
    
    return 0;
}
