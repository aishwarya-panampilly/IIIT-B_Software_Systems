/***************************************************************************************************
 *Name: 23.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to create a Zombie state of the running program.
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION**********************************************/  
// Child becomes Zombie as parent is sleeping when child process exits. 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process exiting...\n");
        exit(0);  // Child exits
    } else {
        // Parent process
        printf("Parent process is sleeping, child process with PID %d is now a zombie.\n", pid);
        sleep(10);  // Parent sleeps, keeping the child in zombie state

        // After sleep, parent reaps the child
        printf("Parent now reaping the zombie process.\n");
        wait(NULL);  // Reap the child
    }

    return 0;
}
/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 23.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Parent process is sleeping, child process with PID 31362 is now a zombie.
  Child process exiting...
  Parent now reaping the zombie process.
*/
