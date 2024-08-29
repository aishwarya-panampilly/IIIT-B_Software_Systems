/***************************************************************************************************
 *Name: 25.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to create three child processes. The parent should wait for a particular child (use waitpid system call)
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
    pid_t pid1, pid2, pid3;
    int cid;
    
    // Create the first child process
    pid1 = fork();
    
    if (pid1 < 0) {
        printf("Error: Failed to fork child 1.\n");
        return 1;
    }
    
    if (pid1 == 0) {
        // Child 1 process
        printf("Child 1: PID = %d\n", getpid());
        sleep(2);  // Simulate some work with sleep
        return 0;
    }
    
    // Create the second child process
    pid2 = fork();
    
    if (pid2 < 0) {
        printf("Error: Failed to fork child 2.\n");
        return 1;
    }
    
    if (pid2 == 0) {
        // Child 2 process
        printf("Child 2: PID = %d\n", getpid());
        sleep(4);  // Simulate some work with sleep
        return 0;
    }
    
    // Create the third child process
    pid3 = fork();
    
    if (pid3 < 0) {
        printf("Error: Failed to fork child 3.\n");
        return 1;
    }
    
    if (pid3 == 0) {
        // Child 3 process
        printf("Child 3: PID = %d\n", getpid());
        sleep(6);  // Simulate some work with sleep
        return 0;
    }
    
    // Parent process to ask user which child to wait for 
    printf("Enter which child to wait for  (1, 2, or 3): ");
    scanf("%d", &cid);
    
    pid_t cpid;
    
    switch (cid) {
        case 1:
            cpid = pid1;
            break;
        case 2:
            cpid = pid2;
            break;
        case 3:
            cpid = pid3;
            break;
        default:
            printf("Invalid child number. Exiting.\n");
            return 1;
    }
    
    printf("Parent: Waiting for child %d with PID = %d to finish\n", cid, cpid);
    
    int status;
    pid_t wtpid = waitpid(cpid, &status, 0);  // Wait for the selected child
    
    if (wtpid == -1) {
        printf("Error: waitpid failed.\n");
        return 1;
    }
    
    if (WIFEXITED(status)) {
        printf("Parent: Child %d exited with status = %d\n", cid, WEXITSTATUS(status));
    }   
    return 0;
    
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 25.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Child 1: PID = 30710
  Child 2: PID = 30711
  Child 3: PID = 30712
  Enter which child to wait for  (1, 2, or 3): 2
  Parent: Waiting for child 2 with PID = 30711 to finish
  Parent: Child 2 exited with status = 0
*/

