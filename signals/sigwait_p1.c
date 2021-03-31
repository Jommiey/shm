#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int read_pid()
{
    FILE *fp = fopen("./pid.txt", "r");
    fprintf(fp, "%d", getpid());
    int pid;
    fscanf(fp, "%d", &pid);
    fclose(fp);
    return pid;
}

int main()
{
    int pid = read_pid();
    /* kill(pid, SIGINT); */
    kill(pid, SIGRTMIN+1);
    /* kill(pid, SIGRTMIN+2); */

    while(1)
    {
        printf("What signal do you want to send?\n");
        printf("1. SIGRTMIN+1\n");
        printf("2. SIGRTMIN+2\n");
        int signal = 0;
        scanf("%i", &signal);

        if (signal == 1)
        {
            printf("Sending SIGRTMIN+1 to process %d\n\n", pid);
            kill(pid, SIGRTMIN+1);
        }

        if (signal == 2)
        {
            printf("Sending SIGRTMIN+2 to process %d\n\n", pid);
            kill(pid, SIGRTMIN+2);
        }
    }
}
