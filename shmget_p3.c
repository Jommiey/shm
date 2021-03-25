#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>

#define SHMSIZE 128

int main()
{
    // Choose key for shared segment.
    key_t key = 4534;

    // Find existing or create new segment with chosen key.
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

    // Write a message and wait for a response. While-loop to continue sending
    // messages after receiving a response.
    while (true)
    {
        char input[20];
        printf("Input string to send to consumer: ");
        scanf("%s", input);
        
        char *s = shm;
        for (int i = 0; i < strlen(input); i++) 
        {
            printf("Wrote %c to segment.\n", input[i]);
            *s++ = input[i];
        }
        *s = NULL;

        while (*shm != '*')
        {
            printf("Waiting for response from client. *shm is currently: %s\n", shm);
            sleep(1);
        }
        printf("Got response from client.\n");
    }
}
