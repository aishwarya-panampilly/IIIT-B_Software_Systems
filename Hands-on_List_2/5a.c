/***************************************************************************************************
 *Name: 5a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print the system limitation of
                a. maximum length of the arguments to the exec family of functions.
 *Date: 17th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>
int main()
{
  long arg_max = sysconf(_SC_ARG_MAX);
  if (arg_max != -1) {
    printf("Maximum length of the arguments to the exec family of functions is %ld\n",arg_max);
  } else {
    perror("System call failed!");
  }
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Maximum length of the arguments to the exec family of functions is 2097152
*/

