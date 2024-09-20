/***************************************************************************************************
 *Name: 32b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to implement semaphore to protect any critical section.
                b. protect shared memory from concurrent write access
 *Date: 21th September, 2024
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
#define SHM_SIZE 1024  // Size of the shared memory segment

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
    int semid, shmid;
    char *shared_memory;  // Pointer to the shared memory
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

    // Create shared memory for the data
    shmid = shmget(shm_key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Simulate multiple processes writing to shared memory
    for (int i = 0; i < 5; i++) {  // Create 5 processes
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {  // Child process
            // Generate a message to write
            char message[SHM_SIZE];
            snprintf(message, sizeof(message), "Process %d wrote this message.\n", getpid());

            // Enter critical section
            sem_wait(semid);

            // Critical section: write to shared memory
            printf("Process %d is writing to shared memory...\n", getpid());
            snprintf(shared_memory, SHM_SIZE, "%s", message);  // Write message to shared memory

            // Exit critical section
            sem_signal(semid);

            // Detach and exit child process
            shmdt(shared_memory);
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process: wait for all child processes to finish
    for (int i = 0; i < 5; i++) {
        wait(NULL);  // Wait for all child processes
    }

    // Print the content of shared memory after all writes
    printf("Final content of shared memory: %s", shared_memory);

    // Detach from shared memory
    if (shmdt(shared_memory) == -1) {
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

