/***************************************************************************************************
 *Name: 5e.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print the system limitation of
                e. size of a page
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>

int main()
{
  long page_size = sysconf(_SC_PAGESIZE);
  if (page_size != -1) {
    printf("Size of a memory page: %ld bytes\n",page_size);
  } else {
    perror("System call failed!");
  }
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Size of a memory page: 4096 bytes
*/
