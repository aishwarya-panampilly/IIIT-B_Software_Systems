/***************************************************************************************************
 *Name: 14.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
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
    char write_msg[100];  // Buffer to store user input
    char read_msg[100];   // Buffer to store the message read from the pipe

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Fork a new process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent process: writes to the pipe
        close(fd[0]);  // Close the read end of the pipe

        
        printf("Enter a message: ");
        fgets(write_msg, sizeof(write_msg), stdin);

        // Write the user input to the pipe
        write(fd[1], write_msg, strlen(write_msg) + 1);  // Include the null terminator
        close(fd[1]);  // Close the write end after writing

        // Wait for the child process to finish
        wait(NULL);
    } else {
        // Child process: reads from the pipe
        close(fd[1]);  // Close the write end of the pipe

        // Read the message from the pipe
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child process read from pipe: %s\n", read_msg);

        close(fd[0]);  // Close the read end after reading
    }

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Enter a message: hello!
Child process read from pipe: hello!
*/

    

