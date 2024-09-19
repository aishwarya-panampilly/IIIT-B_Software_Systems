/***************************************************************************************************
 *Name: 1b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program (for each time domain) to set a interval timer in 10 sec and 10 micro second
                b. ITIMER_VIRTUAL
 *Date: 12th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

//signal handler is a function which is called by the target environment when the corresponding signal occurs. The environment suspends execution of the program till the signal handler returns.

void signal_handler(int sig) {
  //
  char *buffer = "ITIMER_VIRTUAL signal received\n";
  write (STDOUT_FILENO,buffer,strlen(buffer));
}

int main() 
{
   // initialising a timer 
   struct itimerval timer;
   
   //according to the ISO/ANSI standard, we need to call the signal function to identify the handler for the signal in the beginning of the program or at some point before the signal may occur
   signal(SIGVTALRM,signal_handler);
   
   //it_interval sets the repeating interval after the first expiration 
   //if it is set to 0, timer only expires once
   timer.it_interval.tv_sec = 10;
   timer.it_interval.tv_usec = 10; //microseconds
   
   //it_value sets the initial time before the timer expires for the FIRST TIME.
   //if you set it to 10 secs, the timer will expire after 10 seconds and send signal
   //if it is set to 0, timer is disarmed
   timer.it_value.tv_sec = 10;
   timer.it_value.tv_usec = 10;
   
   //now setting timer with setitimer, specify which timer, new timer and previous timer settings 
   //we pass the address of timer as it requires a pointer
   //ITIMER_VIRTUAL counts down against the user mode CPU time consumed by a process (including all the threads in that process)
   // at each expiration a SIGVTALRM is generated
   
   if (setitimer(ITIMER_VIRTUAL,&timer,NULL) == -1) {
      perror("Error in setting timer!");
      exit(1);
   }
   
   // to ensure that the program remains active to respond to signals, infinite loop is used
   while (1) {
   }
   
   return 0;
}

/******************************************SOLUTION************************************************/
   
   
   
