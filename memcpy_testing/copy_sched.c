#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>

int copyMemory(int blockSize, int sourceSize, char* source, char* destination) {
  int numberOfCopies = sourceSize / blockSize + 1;
  for(int i = 0; i < numberOfCopies; i=i+1) {
    memcpy(destination + (i * blockSize), source + (i * blockSize), blockSize);
  }
  return numberOfCopies;
}

int main() {
   printf("PID is %d\n", getpid());
   printf("Scheduler: %d\n", SCHED_OTHER);
   printf("Scheduler is %d.\n", sched_getscheduler(getpid()));
   printf("minprio is %d.\n", sched_get_priority_min(SCHED_FIFO));
   printf("maxprio is %d.\n", sched_get_priority_max(SCHED_FIFO));

   struct sched_param sp;
   sp.sched_priority = 99;
   int ret = sched_setscheduler(getpid(), SCHED_FIFO, &sp);

   printf("Return value: %d\n", ret);
   printf("New scheduler is %d.\n", sched_getscheduler(getpid()));

   char dest[2000000] = "something irrelevant";
   char src[2000000];

   FILE *fp = fopen("./pi.txt", "r");
   char c;
   while((c=fgetc(fp))!=EOF){
      strncat(src, &c, 1);
    }

   int loops = 100;
   int blockSize = 64;

   struct timespec ts1, ts2;
   long tsTot = 0;
   long tsAvr;

   clock_gettime(CLOCK_REALTIME, &ts1);
   for(int i = 0; i < loops; i=i+1) {
     copyMemory(blockSize, strlen(src), src, dest);
   }
   clock_gettime(CLOCK_REALTIME, &ts2);

   tsTot = (int) ts2.tv_nsec - (int) ts1.tv_nsec;

   tsAvr = tsTot / loops;
   printf("the average time was: %ld\n", tsAvr);


}
