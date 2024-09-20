/***************************************************************************************************
 *Name: 9.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main()
{
  if (signal(SIGINT,SIG_IGN) == SIG_ERR) {
    perror("Cannot ignore signal!");
    exit(EXIT_FAILURE);
  } 
  
  printf("SIGINT signal is now being ignored\nPress Ctrl+C to test\n");
  
  //wait for 10 seconds
  
  sleep(10);
  
  //reset sigint
  if (signal(SIGINT,SIG_DFL) == SIG_ERR) {
    perror("Unable to set default!");
    exit(EXIT_FAILURE);
  }
  
  printf("\nSIGINT signal reset to default\nPress Ctrl+C to exit\n");
  
  //loop to keep program running
  while(1) {
    pause();
  }
  return 0;
}

/******************************************OUTPUT************************************************/
/*
SIGINT signal is now being ignored
Press Ctrl+C to test
^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C^C
SIGINT signal reset to default
Press Ctrl+C to exit
^C
*/

