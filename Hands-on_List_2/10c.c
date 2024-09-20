/***************************************************************************************************
 *Name: 10c.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program using sigaction system call to catch the following signals.
                c. SIGFPE
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum)
{
  printf("Caught SIGFPE - Signal number : %d\n",signum);
  exit(EXIT_FAILURE);
}

int main()
{
  struct sigaction sa;
  sa.sa_handler = signal_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  
  if (sigaction(SIGFPE,&sa,NULL) == -1) {
    perror("Error setting handler");
    exit(EXIT_FAILURE);
  }

  printf("SIGFPE handler is set up\nNow causing floating point exception\n");
  int x = 1;
  int y = 0;
  int result =  x/y;
  return 0;
}

/******************************************OUTPUT************************************************/
/*
SIGFPE handler is set up
Now causing floating point exception
Caught SIGFPE - Signal number : 8
*/


