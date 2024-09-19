/***************************************************************************************************
 *Name: 8b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program using signal system call to catch the following signals
                b. SIGINT
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_signal(int signum) {
  printf("\nCaught SIGINT (interrupt from keyboard) - Signal number %d\n",signum);
  exit(EXIT_SUCCESS);
}

int main()
{
  if (signal(SIGINT,handle_signal) == SIG_ERR) {
    perror("Error setting up handler!");
    exit(EXIT_FAILURE);
  }
  
  printf("Signal handler for SIGINT is set up\nProcess ID: %d\n",getpid());
  printf("Press Ctrl+C to trigger SIGINT\n");
  
  //wait for the signal
  while(1) {
    pause();
  }
  
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Signal handler for SIGINT is set up
Process ID: 13722
Press Ctrl+C to trigger SIGINT
^C
Caught SIGINT (interrupt from keyboard) - Signal number 2
*/

