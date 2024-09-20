/***************************************************************************************************
 *Name: 16.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to send and receive data from parent to child vice versa. Use two way
communication.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int parent_to_child[2];  // Pipe for parent to child communication
    int child_to_parent[2];  // Pipe for child to parent communication
    pid_t pid;
    char parent_msg[100];  // Buffer for parent's message
    char child_msg[100];   // Buffer for child's message

    // creating 2 pipes
    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // forking proces
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {  // Parent process
        // important to close unnecessary pipe ends
        close(parent_to_child[0]);  // Close read end of parent-to-child pipe
        close(child_to_parent[1]);  // Close write end of child-to-parent pipe

        // Parent sends data to child
        printf("Parent: Enter a message to send to the child: ");
        fgets(parent_msg, sizeof(parent_msg), stdin);

        // Write to the child through the pipe
        write(parent_to_child[1], parent_msg, strlen(parent_msg) + 1);
        close(parent_to_child[1]);  // Close the write end after sending

        // Wait for child's response
        read(child_to_parent[0], child_msg, sizeof(child_msg));
        printf("Parent received from child: %s\n", child_msg);
        close(child_to_parent[0]);  // Close the read end after reading

        // Wait for the child process to finish
        wait(NULL);
    } else {  // Child process
        // Close unnecessary pipe ends
        close(parent_to_child[1]);  // Close write end of parent-to-child pipe
        close(child_to_parent[0]);  // Close read end of child-to-parent pipe

        // Child reads the message from the parent
        read(parent_to_child[0], parent_msg, sizeof(parent_msg));
        printf("Child received from parent: %s\n", parent_msg);
        close(parent_to_child[0]);  // Close the read end after receiving

        // Child sends data back to the parent
        printf("Child: Enter a message to send to the parent: ");
        fgets(child_msg, sizeof(child_msg), stdin);

        // Write the message to the parent
        write(child_to_parent[1], child_msg, strlen(child_msg) + 1);
        close(child_to_parent[1]);  // Close the write end after sending
    }

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Parent: Enter a message to send to the child: hello!
Child received from parent: hello!

Child: Enter a message to send to the parent: goodbye!
Parent received from child: goodbye!
*/


