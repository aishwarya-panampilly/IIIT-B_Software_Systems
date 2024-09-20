/***************************************************************************************************
 *Name: 8g.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program using signal system call to catch the following signals
                g. SIGPROF (use setitimer system call)
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_signal (int signum) {
  printf("Caught SIGPROF - Signal number %d\n",signum);
}

int main()
{
  struct itimerval timer;
  if (signal(SIGPROF,handle_signal) == SIG_ERR) {
    perror("Error in setting handler");
    exit(EXIT_FAILURE);
  } 
    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    
    if (setitimer(ITIMER_PROF,&timer,NULL) == -1) {
      perror("Couldn't set timer");
      exit(EXIT_FAILURE);
    }
    
    printf ("Timer set at 3 seconds initially with 1 second interval\n");
    
    while(1) {
      for (volatile int i = 0; i < 1000000000 ; ++i);
      sleep(1);
    }
    
    return 0;
}

/******************************************OUTPUT************************************************/\
/*
Timer set at 3 seconds initially with 1 second interval
Caught SIGPROF - Signal number 27
Caught SIGPROF - Signal number 27
Caught SIGPROF - Signal number 27
Caught SIGPROF - Signal number 27
*/
