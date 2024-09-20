/***************************************************************************************************
 *Name: 10.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program using sigaction system call to catch the following signals.
                a. SIGSEGV
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum) {
  printf("Caught SIGSEGV (Segmentation Fault) - Signal Number : %d\n", signum);
  exit(EXIT_FAILURE);
}

int main()
{
  struct sigaction sa;
  //setting up sigaction
  sa.sa_handler = signal_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  
  if (sigaction(SIGSEGV,&sa,NULL) == -1) {
    perror("sigaction not set");
    exit(EXIT_FAILURE);
  }
  
  printf("SIGSEGV handler is set up\nNow causing a segmentation fault by dereferencing NULL pointer\n");
  int *p = NULL;
  *p = 42;
  
  return 0;
}

/******************************************OUTPUT************************************************/
/*
SIGSEGV handler is set up
Now causing a segmentation fault by dereferencing NULL pointer
Caught SIGSEGV (Segmentation Fault) - Signal Number : 11
*/


  
