/***************************************************************************************************
 *Name: 8c.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program using signal system call to catch the following signals
                c. SIGFPE
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handle_signal(int signum) {
  printf("Caught SIGFPE (Floating-Point Exception) - signal number %d\n",signum);
  exit(EXIT_SUCCESS);
}

int main()
{
  if (signal(SIGFPE,handle_signal) == SIG_ERR) {
    perror("Error setting handler!");
    exit(EXIT_FAILURE);
  }
  printf("Signal handler for SIGFPE is set up\nProcess ID: %d\n",getpid());
  
  //causing floating point exception
  int a = 1;
  int b = 0;
  int c = a / b;
  
  //this line will not be executed due to the exception
  printf("Result of division : %d\n",c);
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Signal handler for SIGFPE is set up
Process ID: 14212
Caught SIGFPE (Floating-Point Exception) - signal number 8
*/


