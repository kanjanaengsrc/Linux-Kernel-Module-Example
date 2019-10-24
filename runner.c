#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define dev "/proc/mydevice"
#define MAXSIZE 32
int main(void)
{
   char str[MAXSIZE];
   memset(str,0,MAXSIZE);
   int num=26;
   int fd=0;
   int result=0;
   fd = open(dev,O_RDWR, S_IWUSR | S_IRUSR);
   if(fd == -1){
      printf("Error: Could not open %s\n",dev);
      exit(1);
   }else{
      printf("%s is opened\n",dev);
      printf("Enter number of alphabet (<= 32) : ");
      scanf("%d",&num);
      result = read(fd,str,num);
      if(result){
         printf("%s are read from %s\n",str,dev);
      }else{
         printf("Error while reading from %s\n",dev);
      }
      getchar();
      printf("Enter string : ");
      fgets(str,MAXSIZE,stdin);
      result = write(fd,str,strlen(str)); 
      if(result){
         printf("%s are wrote into %s\n",str,dev);
      }else{
         printf("Error while writing into %s\n",dev);
      }
      printf("(Second round) Enter number of alphabet (<= 32) : ");
      scanf("%d",&num);
      result = read(fd,str,num);
      if(result){
         printf("%s are read from %s\n",str,dev);
      }else{
         printf("Error while reading from %s\n",dev);
      }
   }
   return 0;
}
