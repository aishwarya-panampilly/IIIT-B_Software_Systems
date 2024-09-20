/***************************************************************************************************
 *Name: 32d.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to implement semaphore to protect any critical section.
                d. remove the created semaphore
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

    // Create a semaphore
    semid = semget(sem_key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize the semaphore to 1 (binary semaphore)
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl (SETVAL)");
        exit(EXIT_FAILURE);
    }

    // Simulate multiple processes accessing the critical section
    for (int i = 0; i < 5; i++) {  // Create 5 processes
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {  // Child process
            // Enter critical section
            printf("Process %d is trying to enter the critical section...\n", getpid());
            sem_wait(semid);  // Wait for access

            // Critical section
            printf("Process %d has entered the critical section.\n", getpid());
            sleep(1);  // Simulate work in the critical section
            printf("Process %d is leaving the critical section.\n", getpid());

            // Exit critical section
            sem_signal(semid);

            // Detach and exit child process
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
/******************************************OUTPUT************************************************/
/*
Process 44683 is trying to enter the critical section...
Process 44683 has entered the critical section.
Process 44684 is trying to enter the critical section...
Process 44685 is trying to enter the critical section...
Process 44686 is trying to enter the critical section...
Process 44687 is trying to enter the critical section...
Process 44683 is leaving the critical section.
Process 44684 has entered the critical section.
Process 44684 is leaving the critical section.
Process 44686 has entered the critical section.
Process 44686 is leaving the critical section.
Process 44685 has entered the critical section.
Process 44685 is leaving the critical section.
Process 44687 has entered the critical section.
Process 44687 is leaving the critical section.
All processes finished. Semaphore removed.
*/
