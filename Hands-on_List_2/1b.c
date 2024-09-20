/***************************************************************************************************
 *Name: 1b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a separate program (for each time domain) to set a interval timer in 10 sec and 10 micro second
                b. ITIMER_VIRTUAL
 *Date: 12th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

// Signal handler for SIGVTALRM (ITIMER_VIRTUAL)
void timer_handler(int signum) {
    printf("ITIMER_VIRTUAL expired! (SIGVTALRM)\n");
}

void consume_cpu_time() {
    // Perform CPU-bound work to simulate real usage
    volatile int i;
    for (i = 0; i < 1000000000000000; i++) {
        // A busy loop to keep CPU busy
    }
}

int main() {
    struct itimerval timer;

    // Set up the signal handler for SIGVTALRM using signal()
    signal(SIGVTALRM, timer_handler);

    // Configure the timer to expire after 10 seconds and 10 microseconds
    timer.it_value.tv_sec = 10;   // Initial expiration (seconds)
    timer.it_value.tv_usec = 10;  // Initial expiration (microseconds)
    timer.it_interval.tv_sec = 0; // No repeating interval
    timer.it_interval.tv_usec = 0;

    // Set the ITIMER_VIRTUAL timer
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("setitimer ITIMER_VIRTUAL");
        exit(EXIT_FAILURE);
    }

    printf("ITIMER_VIRTUAL timer set for 10 seconds and 10 microseconds.\n");

    // Consume CPU time to trigger the ITIMER_VIRTUAL timer
    while (1) {
        consume_cpu_time(); // Keep CPU busy to simulate load
        pause();            // Wait for signals (SIGVTALRM)
    }

    return 0;
}
/******************************************OUTPUT************************************************/
/*
ITIMER_VIRTUAL timer set for 10 seconds and 10 microseconds.
ITIMER_VIRTUAL expired! (SIGVTALRM)
*/
   
   
