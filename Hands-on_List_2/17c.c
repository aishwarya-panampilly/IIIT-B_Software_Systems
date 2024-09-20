/***************************************************************************************************
 *Name: 17c.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to execute ls -l | wc.
                c. use fcntl
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/wait.h>

int main() {
    int pipefd[2];  
    pid_t pid1, pid2;
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid1 == 0) {
        close(pipefd[0]);

        // Use fcntl to duplicate pipefd[1] to stdout (STDOUT_FILENO)
        close(STDOUT_FILENO);  // Close stdout to make the lowest FD available
        fcntl(pipefd[1], F_DUPFD, STDOUT_FILENO);  // Duplicate pipefd[1] to stdout
        // Close the write end of the pipe (it's now duplicated to stdout)
        close(pipefd[1]);
        // Execute 'ls -l'
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls failed");
        exit(1);
    }
    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid2 == 0) {
        close(pipefd[1]);
        // Use fcntl to duplicate pipefd[0] to stdin (STDIN_FILENO)
        close(STDIN_FILENO);  // Close stdin to make the lowest FD available
        fcntl(pipefd[0], F_DUPFD, STDIN_FILENO);  // Duplicate pipefd[0] to stdin
        // Close the read end of the pipe (it's now duplicated to stdin)
        close(pipefd[0]);
        // Execute 'wc'
        execlp("wc", "wc", NULL);
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
    37     326    1850
*/

