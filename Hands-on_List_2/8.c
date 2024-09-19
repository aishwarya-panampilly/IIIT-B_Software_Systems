/***************************************************************************************************
 *Name: 8.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program using signal system call to catch the following signals
                a. SIGSEGV
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum) {
  printf("Caught SIGSEGV (Segmentation Fault) - Signal number %d\n",signum);
  exit(EXIT_FAILURE);
}

int main() 
{
  if (signal(SIGSEGV,signal_handler) == SIG_ERR) {
    perror("Error setting up handler!");
    exit(EXIT_FAILURE);
  }

  printf("Signal handler for SIGSEGV is set up\nProcess ID: %d\n",getpid());
  
  int *ptr = NULL;
  *ptr = 42; //accessing invalid memory to trigger segment fault
  
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Signal handler for SIGSEGV is set up
Process ID: 9408
Caught SIGSEGV (Segmentation Fault) - Signal number 11
*/
