#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h> // Exit
#include <unistd.h> // Fork, Sleep
#include <string.h>
#include <stdbool.h>

void shared_memory(int pid)
{
    key_t key = 9876;
    int shmid = shmget(key, 128, IPC_CREAT | 0666);
    if (!shmid)
    {
        perror("Error creating shmid.");
        exit(1);
    }

    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char*) -1)
    {
        perror("Error attaching to shared memory.");
        exit(1);
    }

    if (pid == 0)
    {
        char* s = shm;
        for (char c = 'a'; c <= 'z'; c++)
        {
            *s++ = c;
            printf("Inserted %c.\n", c);
        }
    }
    else
    {
        sleep(3);
        char *s;
        for (s = shm; *s != NULL; s++)
        {
            printf("Client read %c from segment\n", *s);
        }
        printf("Client finished reading from segment\n");
    }
}

int main()
{
    int pid = fork();
    shared_memory(pid);
}
