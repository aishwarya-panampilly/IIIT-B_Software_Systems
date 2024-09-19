/***************************************************************************************************
 *Name: 4.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
 *Date: 18th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

unsigned long long rdtsc() 
{
  unsigned long long dst;
  __asm__ __volatile__("rdtsc":"=A"(dst));
  return dst;
}

int main()
{
  long long start,end;

  
  start = rdtsc();
  
  for (int i = 0; i < 100 ; i++){
    getpid();
  }
  
  end = rdtsc();
  
  printf("Time taken to execute 100 getpid() calls: %llu CPU cycles\n",end - start);
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Time taken to execute 100 getpid() calls: 190050 CPU cycles
*/


