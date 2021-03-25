#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMSIZE 128

void write_pid_to_file()
{
    FILE *fp;
    fp = fopen("./pid.txt", "w+");
    fprintf(fp, "%d", getpid());
    fclose(fp);
}

int main()
{
    write_pid_to_file();

    // Get segment.
    key_t key = 4534;
    int shmid = shmget(key, SHMSIZE, 0666);
    if (shmid == -1)
    {
        perror("Error using shmget.");
        exit(1);
    }

    // Attach to segment.
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char*) -1)
    {
        perror("Error using shmat.");
        exit(1);
    }

    // Read from shared segment.
    char *s;
    for (s = shm; *s != NULL; s++)
    {
        printf("Client read %c from segment\n", *s);
    }
    printf("Client finished reading from segment\n");
    *shm = '*';
    exit(0);
}
