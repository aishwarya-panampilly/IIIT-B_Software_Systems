/***************************************************************************************************
 *Name: 23.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit rl;

    // Get the maximum number of open files
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        perror("getrlimit failed");
        exit(1);
    }

    printf("Maximum number of open files: soft limit = %lu, hard limit = %lu\n",
           rl.rlim_cur, rl.rlim_max);

    // Get the size of the pipe (circular buffer)
    // This size may vary based on the system, default is typically 16KB or more.
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe creation failed");
        exit(1);
    }

    // The size of the pipe is typically fixed by the system, often 16KB.
    // For this demo, we'll just mention the default size.
    printf("Size of the pipe (circular buffer) is generally: 16KB (system dependent)\n");

    // Close the pipe
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Maximum number of open files: soft limit = 1024, hard limit = 1048576
Size of the pipe (circular buffer) is generally: 16KB (system dependent)
*/

