/***************************************************************************************************
 *Name: 11.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - use sigaction system call.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main()
{
  struct sigaction sa_ignore,sa_default;
  sa_ignore.sa_handler = SIG_IGN;
  sigemptyset(&sa_ignore.sa_mask);
  sa_ignore.sa_flags = 0;
  
  if (sigaction(SIGINT,&sa_ignore,NULL) == -1)
  {
    perror ("Error setting handler");
    exit(EXIT_FAILURE);
  }
  printf("SIGINT is being ignored\nPress CTRL+C to test\n");
  
  sleep(10);
  
  sa_default.sa_handler = SIG_DFL;
  sigemptyset(&sa_default.sa_mask);
  sa_default.sa_flags = 0;
  
  if (sigaction(SIGINT,&sa_default,NULL) == -1) {
    perror("Error setting default");
    exit(EXIT_FAILURE);
  }
  
  printf("\nSIGINT signal is now reset to default\nPress Ctrl+C to terminate the program\n");
  
  while(1) {
    pause();
  }
  return 0;
}

/******************************************OUTPUT************************************************/
/*
SIGINT is being ignored
Press CTRL+C to test
^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C
SIGINT signal is now reset to default
Press Ctrl+C to terminate the program
^C
*/

