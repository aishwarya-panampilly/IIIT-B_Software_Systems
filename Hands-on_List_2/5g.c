/***************************************************************************************************
 *Name: 5g.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print the system limitation of
                g. number of currently available pages in the physical memory.
 *Date: 19th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>

int main()
{
  long available_pages = sysconf(_SC_AVPHYS_PAGES);
  if (available_pages != -1) {
    printf("Number of currently available pages in physical memory : %ld\n",available_pages);
  } else {
    perror("System call failed!");
  }
  return 0;
}
/******************************************OUTPUT************************************************/
/*
Number of currently available pages in physical memory : 101753
*/
