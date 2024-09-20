/***************************************************************************************************
 *Name: 10b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program using sigaction system call to catch the following signals.
                b. SIGINT
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum) {
  printf("\nCaught SIGINT - Signal number : %d\n",signum);
}

int main()
{
  struct sigaction sa;
  
  sa.sa_handler = signal_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  
  if (sigaction(SIGINT,&sa,NULL) == -1) {
    perror("Error installing handler");
    exit(EXIT_FAILURE);
  }
  
  printf("SIGINT handler is set up\nPress Ctrl+C to test\n");
  
  while(1) {
    pause();
  }

  return 0;
}

/******************************************OUTPUT************************************************/
/*
SIGINT handler is set up
Press Ctrl+C to test
^C
Caught SIGINT - Signal number : 2
^C
Caught SIGINT - Signal number : 2
^C
Caught SIGINT - Signal number : 2
*/
