/***************************************************************************************************
 *Name: 21.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program, call fork and print the parent and child process id
 *Date: 28th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
  pid_t pid = fork();
  if (pid < 0)
  {
    printf("Fork failed!\n");
    exit(1);
  }
  else if ( pid == 0 ) {
    printf("Child process PID: %d\n",getpid());
    fflush(stdout);
  }
  else {
    printf("Parent process PID: %d\n",getpid());
    fflush(stdout);
  }
  return 0;
}
/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 21.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Parent process PID: 33779
  Child process PID: 33780
*/

  
