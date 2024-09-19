/***************************************************************************************************
 *Name: 5b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print the system limitation of
                b. maximum number of simultaneous process per user id
 *Date: 17th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>

int main()
{
  long max_procs = sysconf(_SC_CHILD_MAX);
  if (max_procs != -1) {
    printf("Maximum number of simultaneous processes per user ID : %ld\n", max_procs);
  } else {
    perror("System call failed!");
  }
  return 0;
}

/******************************************OUTPUT*********************************************/
/*
Maximum number of simultaneous processes per user ID : 15194
*/

