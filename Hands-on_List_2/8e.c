/***************************************************************************************************
 *Name: 8e.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program using signal system call to catch the following signals
                e. SIGALRM (use setitimer system call)
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void handle_signal (int signum) {
  printf("Caught SIGALRM - Signal number %d\n",signum);
}

int main()
{
  struct itimerval timer;
  if (signal(SIGALRM,handle_signal) == SIG_ERR) {
    perror("Error in setting handler!");
    exit(EXIT_FAILURE);
  }
  
  //configure timer to go off after 5 seconds and then after every two seconds
  
  timer.it_value.tv_sec = 5;
  timer.it_value.tv_usec = 0;
  timer.it_interval.tv_sec = 2;
  timer.it_interval.tv_usec = 0;
  
  //start timer
  if (setitimer(ITIMER_REAL,&timer,NULL) == -1) {
    perror("Could not set timer");
    exit(EXIT_FAILURE);
  }
  
  printf("Timer is set with 5 seconds initially and an interval of 2 seconds\n");
  
  while(1) {
    pause();
  }
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Timer is set with 5 seconds initially and an interval of 2 seconds
Caught SIGALRM - Signal number 14
Caught SIGALRM - Signal number 14
Caught SIGALRM - Signal number 14
Caught SIGALRM - Signal number 14
*/
  

