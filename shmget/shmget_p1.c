#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define SHMSIZE 128

int main()
{
    // Create shared memory segment and check if successful.
    key_t key = 4534;
    int shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("Error using shmget.");
        exit(1);
    }

    // Attach segment.
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char*) -1)
    {
        perror("Error using shmat.");
        exit(1);
    }

    // Insert data into segment.
    char c;
    char *s = shm;
    for (c = 'a'; c <= 'z'; c++)
    {
        printf("Wrote %c to segment.\n", c);
        *s++ = c;
    }

    *s = NULL;
    // Wait until client has read what we wrote and responded.
    while (*shm != '*')
    {
        printf("Waiting for response from client.\n");
        sleep(1);
    }
    printf("Got response from client.\n");
}
