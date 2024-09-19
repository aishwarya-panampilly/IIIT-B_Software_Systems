/***************************************************************************************************
 *Name: 5d.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print the system limitation of
                d. maximum number of open files
 *Date: 17th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>

int main()
{
  long max_files = sysconf(_SC_OPEN_MAX);
  if (max_files != -1) {
    printf("Maximum number of open files : %ld\n",max_files);
  } else {
    perror("System call failed!");
  }
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Maximum number of open files : 1024
*/

