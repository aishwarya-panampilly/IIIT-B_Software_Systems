/***************************************************************************************************
 *Name: 15.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a simple program to send some data from parent to the child process
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];  // File descriptors for the pipe
    pid_t pid;
    char write_msg[100];  // Buffer for user input
    char read_msg[100];   // Buffer for reading from the pipe
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent process: write user input to the pipe
        close(fd[0]); 
        printf("Parent: Enter a message for the child: ");
        fgets(write_msg, sizeof(write_msg), stdin);
        write(fd[1], write_msg, strlen(write_msg) + 1);  // Include the null terminator
        close(fd[1]);  // Close the write end after writing
        // Parent can wait for child to finish if necessary
        wait(NULL);
    } else {
        // Child process: read from the pipe
        close(fd[1]);  // Close the write end of the pipe
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child process received: %s\n", read_msg);
        close(fd[0]);  // Close the read end after reading
    }
    return 0;
}
/******************************************OUTPUT***********************************************/
/*
Parent: Enter a message for the child: hello!
Child process received: hello!
*/
