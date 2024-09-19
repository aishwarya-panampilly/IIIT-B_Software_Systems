/***************************************************************************************************
 *Name: 5c.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print the system limitation of
                c. number of clock ticks (jiffy) per second.
 *Date: 17th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>

int main()
{
  long ticks_per_sec = sysconf(_SC_CLK_TCK);
  if (ticks_per_sec != -1) {
    printf("Number of clock ticks per second : %ld\n",ticks_per_sec);
  } else {
    perror("System call error!");
  }
  return 0;
}
/******************************************OUTPUT************************************************/
/*
Number of clock ticks per second : 100
*/



