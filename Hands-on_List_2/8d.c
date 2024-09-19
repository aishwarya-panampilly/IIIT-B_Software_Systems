/***************************************************************************************************
 *Name: 8d.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program using signal system call to catch the following signals
                d. SIGALRM (use alarm system call)
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int signum) {
  printf("Caught SIGALRM - Signal number %d\n",signum);
  exit(EXIT_SUCCESS);
}

int main()
{
  if (signal(SIGALRM, handle_signal) == SIG_ERR) {
    perror("Error in setting handler!");
    exit(EXIT_FAILURE);
  } 
  
  //scheduling alarm to be delivered after 5 secs
  printf("Setting alarm for 5 seconds\n");
  alarm(5);
  
  //waiting for signal
  printf("Waiting for alarm\n");
  pause(); //sleeping until signal is caught
  
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Setting alarm for 5 seconds
Waiting for alarm
Caught SIGALRM - Signal number 14
*/
