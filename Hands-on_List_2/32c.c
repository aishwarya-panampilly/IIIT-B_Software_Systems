/***************************************************************************************************
 *Name: 32c.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to implement semaphore to protect any critical section.
                c. protect multiple pseudo resources ( may be two) using counting semaphore
 *Date: 21th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define SEM_KEY 1234  // Semaphore key
#define NUM_RESOURCES 2  // Number of pseudo resources

// Define semaphore operations: wait (P) and signal (V)
void sem_wait(int semid) {
    struct sembuf sb;
    sb.sem_num = 0;    // Use the first (and only) semaphore in the set
    sb.sem_op = -1;    // Decrement semaphore (wait/lock)
    sb.sem_flg = 0;    // No special flags
    if (semop(semid, &sb, 1) == -1) {
        perror("semop (wait)");
        exit(EXIT_FAILURE);
    }
}

void sem_signal(int semid) {
    struct sembuf sb;
    sb.sem_num = 0;    // Use the first (and only) semaphore in the set
    sb.sem_op = 1;     // Increment semaphore (signal/unlock)
    sb.sem_flg = 0;    // No special flags
    if (semop(semid, &sb, 1) == -1) {
        perror("semop (signal)");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int semid;
    key_t sem_key = SEM_KEY;  // Semaphore key
    int pid;

    // Create a counting semaphore for two resources
    semid = semget(sem_key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize the semaphore to the number of available resources
    if (semctl(semid, 0, SETVAL, NUM_RESOURCES) == -1) {
        perror("semctl (SETVAL)");
        exit(EXIT_FAILURE);
    }

    // Simulate multiple processes accessing the resources
    for (int i = 0; i < 5; i++) {  // Create 5 processes
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {  // Child process
            // Attempt to access a resource
            printf("Process %d is trying to access a resource...\n", getpid());
            sem_wait(semid);  // Wait for an available resource

            // Critical section: access the resource
            printf("Process %d has accessed a resource.\n", getpid());
            sleep(1);  // Simulate some work with the resource

            // Release the resource
            printf("Process %d is releasing the resource.\n", getpid());
            sem_signal(semid);

            // Exit child process
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process: wait for all child processes to finish
    for (int i = 0; i < 5; i++) {
        wait(NULL);  // Wait for all child processes
    }

    // Cleanup: Remove the semaphore after use
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl (IPC_RMID)");
        exit(EXIT_FAILURE);
    }

    printf("All processes finished. Semaphore removed.\n");

    return 0;
}
/*****************************************OUTPUT************************************************/
/*
Process 44538 is trying to access a resource...
Process 44538 has accessed a resource.
Process 44541 is trying to access a resource...
Process 44541 has accessed a resource.
Process 44539 is trying to access a resource...
Process 44540 is trying to access a resource...
Process 44542 is trying to access a resource...
Process 44538 is releasing the resource.
Process 44541 is releasing the resource.
Process 44539 has accessed a resource.
Process 44540 has accessed a resource.
Process 44540 is releasing the resource.
Process 44542 has accessed a resource.
Process 44539 is releasing the resource.
Process 44542 is releasing the resource.
All processes finished. Semaphore removed.
*/
