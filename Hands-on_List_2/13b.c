/***************************************************************************************************
 *Name: 13b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//second program to send signal using kill
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() 
{
  pid_t pid;
  
  printf("Enter the PID of the first program : ");
  scanf("%d",&pid);
  
  printf("Sending SIGSTOP signal to process %d\n",pid);
  kill(pid,SIGSTOP);
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Enter the PID of the first program : 20036
Sending SIGSTOP signal to process 20036
*/
