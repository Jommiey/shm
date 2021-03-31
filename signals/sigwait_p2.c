#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

// To avoid using printf inside signal handlers.
static int INTFIRED = 0;
static int MIN1FIRED = 0;
static int MIN2FIRED = 0;

void handlerInt(int sig)
{
    INTFIRED++;
    exit(0);
}

void handlerOne(int sig)
{
    MIN1FIRED++;
}

void handlerTwo(int sig)
{
    MIN2FIRED++;
}

int main()
{
    signal(SIGINT, handlerInt);
    signal(SIGRTMIN+1, handlerOne);
    signal(SIGRTMIN+2, handlerTwo);

    // Write pid to file so another process can kill us.
    FILE *fp;
    fp = fopen("./pid.txt", "w+");
    fprintf(fp, "%d", getpid());
    fclose(fp);

    // Wait until we are killed.
    sigset_t signal_set;
    int sig;
    sigemptyset(&signal_set);
    sigaddset(&signal_set, SIGINT);
    sigaddset(&signal_set, SIGRTMIN+1);
    sigaddset(&signal_set, SIGRTMIN+2);
    sigwait(&signal_set, &sig);
    printf("Wakeup-signal: %d\n", sig);
    while(1)
    {
        printf("Waiting for signals...\n");
        printf("SIGINT fired: %d\n", INTFIRED);
        printf("SIGRTMIN+1 fired: %d\n", MIN1FIRED);
        printf("SIGRTMIN+2 fired: %d\n\n", MIN2FIRED);
        sleep(1);
    }
}
