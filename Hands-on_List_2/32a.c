/***************************************************************************************************
 *Name: 32a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to implement semaphore to protect any critical section.
                a. rewrite the ticket number creation program using semaphore
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define SEM_KEY 1234  // Semaphore key
#define SHM_KEY 5678  // Shared memory key
#define INITIAL_TICKET_NUMBER 1  // Starting value for ticket numbers

// Define semaphore operations: wait (P) and signal (V)
void sem_wait(int semid) {
    struct sembuf sb;
    sb.sem_num = 0;   
    sb.sem_op = -1;    // Decrement semaphore (wait/lock)
    sb.sem_flg = 0;    // No special flags
    if (semop(semid, &sb, 1) == -1) {
        perror("semop (wait)");
        exit(EXIT_FAILURE);
    }
}

void sem_signal(int semid) {
    struct sembuf sb;
    sb.sem_num = 0;   
    sb.sem_op = 1;     // Increment semaphore (signal/unlock)
    sb.sem_flg = 0;    // No special flags
    if (semop(semid, &sb, 1) == -1) {
        perror("semop (signal)");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int semid, shmid;
    int *ticket_number;  // Pointer to the shared ticket number
    key_t sem_key = SEM_KEY;  // Semaphore key
    key_t shm_key = SHM_KEY;  // Shared memory key
    int pid;

    // Create a semaphore with 1 semaphore (binary semaphore)
    semid = semget(sem_key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize the semaphore to 1 (unlocked)
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl (SETVAL)");
        exit(EXIT_FAILURE);
    }

    // Create shared memory for the ticket number
    shmid = shmget(shm_key, sizeof(int), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment
    ticket_number = (int *)shmat(shmid, NULL, 0);
    if (ticket_number == (int *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Initialize the ticket number
    *ticket_number = INITIAL_TICKET_NUMBER;

    // Simulate multiple processes creating tickets
    for (int i = 0; i < 5; i++) {  // Create 5 processes
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {  // Child process
            // Enter critical section
            sem_wait(semid);

            // Critical section: generate the ticket number
            printf("Process %d is generating ticket number: %d\n", getpid(), *ticket_number);
            (*ticket_number)++;  // Increment ticket number

            // Exit critical section
            sem_signal(semid);

            // Exit child process
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process: wait for all child processes to finish
    for (int i = 0; i < 5; i++) {
        wait(NULL);  // Wait for all child processes
    }

    // Detach from shared memory
    if (shmdt(ticket_number) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Cleanup: Remove the semaphore and shared memory after use
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl (IPC_RMID)");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl (IPC_RMID)");
        exit(EXIT_FAILURE);
    }

    printf("All processes finished. Semaphore and shared memory removed.\n");

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Process 44150 is generating ticket number: 1
Process 44148 is generating ticket number: 2
Process 44149 is generating ticket number: 3
Process 44151 is generating ticket number: 4
Process 44152 is generating ticket number: 5
All processes finished. Semaphore and shared memory removed.
*/
