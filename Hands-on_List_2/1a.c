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

void timer_handler(int signum) {
    printf("Timer expired!\n");
}

int main() {
    struct sigaction sa;
    struct itimerval timer;

    // Set up the signal handler for SIGALRM
    sa.sa_handler = timer_handler;
    sa.sa_flags = 0; // No flags
    sigaction(SIGALRM, &sa, NULL);

    // Configure the timer to expire after 10 seconds and 10 microseconds
    timer.it_value.tv_sec = 10; // Initial expiration
    timer.it_value.tv_usec = 10; // Initial expiration (10 microseconds)
    timer.it_interval.tv_sec = 0; // No repeating interval
    timer.it_interval.tv_usec = 0; // No repeating interval

    // Set the timer
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    printf("Timer set for 10 seconds and 10 microseconds.\n");

    // Wait for the timer to expire
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Timer set for 10 seconds and 10 microseconds.
Timer expired!
*/
