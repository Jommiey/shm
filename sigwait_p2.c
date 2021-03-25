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
    while (true)
    {
        printf("Waiting to be killed.");
        sleep(1);
    }
}
