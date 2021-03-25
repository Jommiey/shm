#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

int main()
{
    // Write pid to file so another process can kill us.
    FILE *fp;
    fp = fopen("./pid.txt", "w+");
    fprintf(fp, "%d", getpid());
    fclose(fp);

    // Wait until we are killed.
    printf("Before\n");
    sigset_t signal_set;
    int sig = 0;
    sigemptyset(&signal_set);
    sigaddset(&signal_set, SIGINT);
    sigwait(&signal_set, &sig);
    printf("After\n");
}
