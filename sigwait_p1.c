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
    kill(read_pid(), 9);
}
