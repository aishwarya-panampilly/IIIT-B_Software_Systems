/***************************************************************************************************
 *Name: 22.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file.
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    // Open a file for writing
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Failed to open file");
        exit(1);
    }

    // Fork the process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        const char *child_msg = "Child Process writing\n";
        for (int i = 0; i < 5; i++) {
            write(fd, child_msg, sizeof(child_msg) - 1);
            sleep(1); // Add some delay
        }
        close(fd);
        exit(0);
    } else {
        // Parent process
        const char *parent_msg = "Parent Process writing\n";
        for (int i = 0; i < 5; i++) {
            write(fd, parent_msg, sizeof(parent_msg) - 1);
            sleep(1); // Add some delay
        }

        // Wait for the child to finish
        wait(NULL);
        close(fd);
    }

    printf("File writing complete. Check output.txt for the result.\n");
    return 0;
}
/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 22.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  File writing complete. Check output.txt for the result.
  
  output.txt************************************************************
  Parent Child PParent Child PParent Child PParent Child PParent Child P
*/

//the output comes as so because both parent and child processes are writing to the file concurrently, and file I/O operations are not synchronized
//tried changing sleep durations however the output didn't change 
