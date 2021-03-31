#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int copyMemory(int blockSize, int sourceSize, char* source, char* destination) {
  int numberOfCopies = sourceSize / blockSize + 1;
  for(int i = 0; i < numberOfCopies; i=i+1) {
    //memcpy(destination + (i * blockSize), source + (i * blockSize), blockSize);

  }
  //sleep(1);
  return numberOfCopies;
}

int main() {

   //char src[10000] = "this is a pretty short string";
   char dest[2000000] = "something irrelevant";
   char src[2000000];

   FILE *fp = fopen("./pi.txt", "r");
   char c;
   while((c=fgetc(fp))!=EOF){
      strncat(src, &c, 1);
    }

   int loops = 1000;
   struct timespec ts1, ts2;
   long tsTot, tsAvr;
   for(int i = 0; i < loops; i=i+1) {
     clock_gettime(CLOCK_REALTIME, &ts1);

     copyMemory(100,strlen(src), src, dest);

     clock_gettime(CLOCK_REALTIME, &ts2);
     printf("%ld.%09ld\n", (long)(ts2.tv_sec - ts1.tv_sec),
      ts2.tv_nsec - ts1.tv_nsec);
     tsTot += (int) ts2.tv_nsec - (int) ts1.tv_nsec;
   }

   tsAvr = tsTot / loops;
   printf("the averege time was: %ld\n", tsAvr);
   //printf("%s\n", dest);
   //printf("%ld.%09ld\n", (long)(ts2.tv_sec - ts1.tv_sec),
    //ts2.tv_nsec - ts1.tv_nsec);



}
