/***************************************************************************************************
 *Name: 5f.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print the system limitation of
                f. total number of pages in the physical memory
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>

int main()
{
  long total_pages = sysconf(_SC_PHYS_PAGES);
  if (total_pages != -1) {
    printf("Total number of pages in physical memory : %ld\n",total_pages);
  } else {
    perror("System call failed!");
  }
  return 0;
}

/******************************************OUTPUT************************************************/
/*
Total number of pages in physical memory : 990252
*/

