/***************************************************************************************************
 *Name: 18.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to find out total number of directories on the pwd. execute ls -l | grep ^d | wc ? Use only dup2.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe1[2], pipe2[2];
    
    // Create first pipe for ls -l -> grep
    if (pipe(pipe1) == -1) {
        perror("pipe1 failed");
        exit(EXIT_FAILURE);
    }

    // Fork first child to execute "ls -l"
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Child process 1 (ls -l)
        // Redirect stdout to pipe1's write end
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[0]);  // Close read end
        close(pipe1[1]);  // Close write end

        // Execute ls -l
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls failed");
        exit(EXIT_FAILURE);
    }

    // Create second pipe for grep -> wc
    if (pipe(pipe2) == -1) {
        perror("pipe2 failed");
        exit(EXIT_FAILURE);
    }

    // Fork second child to execute "grep ^d"
    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Child process 2 (grep ^d)
        // Redirect stdin to pipe1's read end and stdout to pipe2's write end
        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe1[1]);  // Close write end of pipe1
        close(pipe1[0]);  // Close read end of pipe1
        close(pipe2[0]);  // Close read end of pipe2
        close(pipe2[1]);  // Close write end of pipe2

        // Execute grep ^d
        execlp("grep", "grep", "^d", NULL);
        perror("execlp grep failed");
        exit(EXIT_FAILURE);
    }

    // Close pipe1 in the parent process as it's no longer needed
    close(pipe1[0]);
    close(pipe1[1]);

    // Fork third child to execute "wc"
    pid_t pid3 = fork();
    if (pid3 == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid3 == 0) {
        // Child process 3 (wc)
        // Redirect stdin to pipe2's read end
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[1]);  // Close write end of pipe2
        close(pipe2[0]);  // Close read end of pipe2

        // Execute wc
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc failed");
        exit(EXIT_FAILURE);
    }

    // Close pipe2 in the parent process
    close(pipe2[0]);
    close(pipe2[1]);

    // Wait for all child processes to finish
    wait(NULL);  // Wait for pid1
    wait(NULL);  // Wait for pid2
    wait(NULL);  // Wait for pid3

    return 0;
}

/******************************************OUTPUT************************************************/
/*
1
*/

