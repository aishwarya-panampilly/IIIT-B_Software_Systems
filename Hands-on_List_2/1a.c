/***************************************************************************************************
 *Name: 1a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
                a. ITIMER_REAL
 *Date: 21th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

// Signal handler for SIGALRM
void timer_handler(int signum) {
    printf("ITIMER_REAL expired! (SIGALRM)\n");
}

int main() {
    struct itimerval timer;

    // Set up the signal handler for SIGALRM using signal()
    signal(SIGALRM, timer_handler);

    // Configure the timer to expire after 10 seconds and 10 microseconds
    timer.it_value.tv_sec = 10;   // Initial expiration (seconds)
    timer.it_value.tv_usec = 10;  // Initial expiration (microseconds)
    timer.it_interval.tv_sec = 0; // No repeating interval
    timer.it_interval.tv_usec = 0;

    // Set the ITIMER_REAL timer
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    printf("ITIMER_REAL timer set for 10 seconds and 10 microseconds.\n");

    // Infinite loop to keep the program running and waiting for the signal
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}
/******************************************OUTPUT************************************************/
/*
ITIMER_REAL timer set for 10 seconds and 10 microseconds.
ITIMER_REAL expired! (SIGALRM)
*/
