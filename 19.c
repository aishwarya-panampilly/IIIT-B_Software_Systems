/***************************************************************************************************
 *Name: 19.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to find out time taken to execute getpid system call. Use time stamp counter
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>   // For getpid()

// Inline assembly function to read the Time Stamp Counter (TSC)
unsigned long long rdtsc() {
    unsigned int lo, hi;
    // Read the lower and higher 32 bits of the TSC into lo and hi
    asm volatile("rdtsc" : "=a"(lo), "=d"(hi));
    // Combine lo and hi into a 64-bit integer and return
    return ((unsigned long long)hi << 32) | lo;
}

int main() {
    unsigned long long start, end;
    pid_t pid;

    // Get the start TSC value
    start = rdtsc();
    pid = getpid();
    // Get the end TSC value
    end = rdtsc();

    // Calculate the number of CPU cycles taken
    unsigned long long cycles = end - start;

    // Print the result
    printf("PID: %d\n", pid);
    printf("CPU cycles taken by getpid(): %llu\n", cycles);

    return 0;
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 19.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  PID: 34565
  CPU cycles taken by getpid(): 21041
*/

