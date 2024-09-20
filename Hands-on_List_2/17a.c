/***************************************************************************************************
 *Name: 17a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to execute ls -l | wc.
                a. use dup
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];  
    pid_t pid1, pid2;
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(1);
    }
    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid1 == 0) {
        // First child process: Executes 'ls -l'
        close(pipefd[0]);
        // Redirect stdout to the write end of the pipe using dup
        close(STDOUT_FILENO);  // Close stdout to make the lowest FD available
        dup(pipefd[1]);        // Now pipefd[1] is duplicated to stdout
        // Close the write end of the pipe (it's now duplicated to stdout)
        close(pipefd[1]);
        // Execute 'ls -l'
        execlp("ls", "ls", "-l", NULL);
        // If exec fails
        perror("execlp ls failed");
        exit(1);
    }
    // Fork the second child to run 'wc'
    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid2 == 0) {
        // Second child process: Executes 'wc'
        close(pipefd[1]);
        // Redirect stdin to the read end of the pipe using dup
        close(STDIN_FILENO);  // Close stdin to make the lowest FD available
        dup(pipefd[0]);       // Now pipefd[0] is duplicated to stdin
        // Close the read end of the pipe (it's now duplicated to stdin)
        close(pipefd[0]);
        // Execute 'wc'
        execlp("wc", "wc", NULL);
        // If exec fails
        perror("execlp wc failed");
        exit(1);
    }
    // Parent process: Close both ends of the pipe
    close(pipefd[0]);
    close(pipefd[1]);
    // Wait for both child processes to finish
    wait(NULL);
    wait(NULL);
    return 0;
}
/******************************************OUTPUT************************************************/
/*
35     308    1746
*/


