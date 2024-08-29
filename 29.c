/***************************************************************************************************
 *Name: 29.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO, SCHED_RR)
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//scheduling policy of a process can be retrieved and modified using the sched_setscheduler() and sched_getscheduler()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>
#include <errno.h>

// display the current scheduling policy
void display_policy(int policy) {
    switch(policy) {
        case SCHED_OTHER:
            printf("Current Scheduling Policy: SCHED_OTHER (Default)\n");
            break;
        case SCHED_FIFO:
            printf("Current Scheduling Policy: SCHED_FIFO (Real-time FIFO)\n");
            break;
        case SCHED_RR:
            printf("Current Scheduling Policy: SCHED_RR (Real-time Round Robin)\n");
            break;
        default:
            printf("Unknown Scheduling Policy\n");
            break;
    }
}

// Function to modify the scheduling policy of the process
int scheduling_policy(int policy) {
    struct sched_param pr;

    // Set the priority to the maximum for the chosen policy
    //sched_param structure is used to specify the scheduling parameters
    
    pr.sched_priority = sched_get_priority_max(policy); 
    //this function returns the maximum scheduling priority for the given policy and it sets the priority of pr as the max allowed priority

    // Attempt to set the scheduler
    if (sched_setscheduler(0, policy, &pr) == -1) {
        printf("Failed to set scheduling policy: %s\n", strerror(errno));
        return -1;
    }

    printf("Scheduling policy successfully changed.\n");
    return 0;
}

int main() {
    int cur_pol;
    int n_pol;
    char input[10];
    /*int pid = getpid();
    printf("The process ID is %d\n",pid);
    // we can use this to check if the scheduling policy has changed */

    // Get the current scheduling policy
    cur_pol = sched_getscheduler(0); //this gets scheduling policy of calling process
    if (cur_pol == -1) {
        perror("Failed to get current scheduling policy");
        exit(EXIT_FAILURE);
    }

    display_policy(cur_pol);

    // Prompt the user for the new scheduling policy
    printf("Enter new scheduling policy (FIFO/RR/DEFAULT): ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character from input to prevent error
    input[strcspn(input, "\n")] = '\0';

    // Determine the new policy based on user input
    if (strcmp(input, "FIFO") == 0) {
        n_pol = SCHED_FIFO;
    } else if (strcmp(input, "RR") == 0) {
        n_pol = SCHED_RR;
    } else if (strcmp (input, "DEFAULT") == 0) {
        n_pol = SCHED_OTHER;
    } else {
        printf("Invalid policy. Use 'FIFO' or 'RR'.\n");
        exit(EXIT_FAILURE);
    }

    // Set the new scheduling policy
    if (scheduling_policy(n_pol) == 0) {
        cur_pol = sched_getscheduler(0);
        display_policy(cur_pol);
    }

    return 0;
}

//we must run this program with root privileges to allow execution
/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 29.c
  aishjp@Aish-Linux:~/my-repo$ sudo ./a.out
  Current Scheduling Policy: SCHED_OTHER (Default)
  Enter new scheduling policy (FIFO/RR/DEFAULT): RR
  Scheduling policy successfully changed.
  Current Scheduling Policy: SCHED_RR (Real-time Round Robin)

*/  
