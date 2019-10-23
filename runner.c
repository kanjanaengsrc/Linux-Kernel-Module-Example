#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
int main(void)
{
   char buffer[1];
   int fd;
   fd = open("/proc/mydevice",O_RDWR, S_IWUSR | S_IRUSR);
   if(fd == -1){
      fprintf(stderr,"Error opening file\n");
      exit(-1);
   }else{
      printf("/proc/mydeive is opened\n");
   }
   return 0;
}
