/***************************************************************************************************
 *Name: 13a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//Program waiting to catch SIGSTOP signal - in linux SIGSTOP signal cannot be caught , blocked or ignored by a process
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main()
{
  printf("Process waiting for SIGSTOP signal (PID %d)\n",getpid());
  while (1) {
    pause();
  }
  return 0;
}
//first run 13a.c and then run 13b.c in different terminals to get output
/******************************************OUTPUT************************************************/
/*
Process waiting for SIGSTOP signal (PID 20036)

[1]+  Stopped                 ./a.out
*/
