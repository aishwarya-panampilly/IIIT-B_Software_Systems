/***************************************************************************************************
 *Name: 8f.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program using signal system call to catch the following signals
                f. SIGVTALRM (use setitimer system call)
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_signal (int signum) {
  printf("Caught SIGVTALRM - Signal number %d\n",signum);
}

int main()
{
  struct itimerval timer;
  
  if(signal(SIGVTALRM,handle_signal) == SIG_ERR) {
    perror("Error setting handler!");
    exit(EXIT_FAILURE);
  }
  
  //timer goes off after 3 seconds and then 1 second interval
  timer.it_value.tv_sec = 3;
  timer.it_value.tv_usec = 0;
  timer.it_interval.tv_sec = 1;
  timer.it_interval.tv_usec = 0;
  
  //start timer
  if (setitimer(ITIMER_VIRTUAL,&timer,NULL) == -1) {
    perror ("Couldn't set timer");
    exit(EXIT_FAILURE);
  }
  
  printf("Virtual timer set for 3 seconds initially with 1 second interval\n");
  
  //loop to keep program running
  while (1) {
    for (volatile int i = 0; i < 1000000000; ++i);
  }
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Virtual timer set for 3 seconds initially with 1 second interval
Caught SIGVTALRM - Signal number 26
Caught SIGVTALRM - Signal number 26
Caught SIGVTALRM - Signal number 26
Caught SIGVTALRM - Signal number 26
*/
