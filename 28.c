/***************************************************************************************************
 *Name: 28.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to get maximum and minimum real time priority
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
// you can use the sched_get_priority_max() and sched_get_priority_min() functions to retrieve maximum and minimum real time priorities
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#include <string.h>

int main() 
{
    int min_priority, max_priority;

    // Get the minimum and maximum priority for SCHED_FIFO
    min_priority = sched_get_priority_min(SCHED_FIFO);
    max_priority = sched_get_priority_max(SCHED_FIFO);

    if (min_priority == -1 || max_priority == -1) {
        fprintf(stderr, "Error getting priorities for SCHED_FIFO: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("SCHED_FIFO:\n");
    printf("  Minimum Priority: %d\n", min_priority);
    printf("  Maximum Priority: %d\n", max_priority);

    // Get the minimum and maximum priority for SCHED_RR
    min_priority = sched_get_priority_min(SCHED_RR);
    max_priority = sched_get_priority_max(SCHED_RR);

    if (min_priority == -1 || max_priority == -1) {
        fprintf(stderr, "Error getting priorities for SCHED_RR: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("SCHED_RR:\n");
    printf("  Minimum Priority: %d\n", min_priority);
    printf("  Maximum Priority: %d\n", max_priority);

    return 0;
}

//This shows range of priority values in my system but it can be different based on confirgurations
/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 28.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  SCHED_FIFO:
    Minimum Priority: 1
    Maximum Priority: 99
  SCHED_RR:
    Minimum Priority: 1
    Maximum Priority: 99
*/

