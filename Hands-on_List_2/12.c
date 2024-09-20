/***************************************************************************************************
 *Name: 12.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main()
{
  pid_t pid;
  pid = fork();
  
  if (pid < 0) {
    perror("Fork failed!");
    exit(1);
  }
  
  else if (pid == 0) {
    //child process
    printf("Child process (PID : %d) sending SIGKILL to Parent (PID : %d)\n",getpid(),getppid());
    //sending sigkill to parent
    kill(getppid(),SIGKILL);
    //child becomes an orphan
    printf("Child process becomes an orphan\n");
    sleep(10);
    printf("Child process exits\n");
    exit(0);
  }
  else {
    printf("Parent process (PID : %d) is waiting\n",getpid());
    sleep(20);
  }
  return 0;
}
/******************************************OUTPUT************************************************/
/*
Parent process (PID : 18555) is waiting
Child process (PID : 18556) sending SIGKILL to Parent (PID : 18555)
Child process becomes an orphan
Killed
aishjp@Aish-Linux:~/my-repo/Hands-on_List_2$ Child process exits
*/
