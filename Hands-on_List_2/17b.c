/***************************************************************************************************
 *Name: 17b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to execute ls -l | wc.
                b. use dup2
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
    // Fork the first child to run 'ls -l'
    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid1 == 0) {
        // First child process: Executes 'ls -l'
        // Close the read end of the pipe
        close(pipefd[0]);
        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
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
        // Close the write end of the pipe
        close(pipefd[1]);
        // Redirect stdin to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);
        // Close the read end of the pipe (it's now duplicated to stdin)
        close(pipefd[0]);
        // Execute 'wc'
        execlp("wc", "wc", NULL);
        //only executed when failed
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
     36     317    1798
*/
