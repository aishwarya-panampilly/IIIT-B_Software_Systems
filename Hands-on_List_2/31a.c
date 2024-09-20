/***************************************************************************************************
 *Name: 31a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to create a semaphore and initialize value to the semaphore.
                a. create a binary semaphore
 *Date: 21th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

int main() {
    key_t key;
    int semid;
    struct sembuf sb;  // Structure for semaphore operations

    // Generate a unique key for the semaphore
    key = ftok("semfile", 65);  // Use a file and project ID to generate a key
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a semaphore set with 1 semaphore (binary semaphore)
    semid = semget(key, 1, 0666 | IPC_CREAT);  // Create semaphore
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize the semaphore value to 1 (binary semaphore unlocked state)
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl (SETVAL)");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore created and initialized to 1 (unlocked).\n");

    sb.sem_num = 0;   // Semaphore index 0 (since we have only one semaphore in the set)
    sb.sem_op = -1;   // Decrement semaphore (lock)
    sb.sem_flg = 0;   // Wait until semaphore is available

    printf("Locking the semaphore (decrementing it)...\n");
    if (semop(semid, &sb, 1) == -1) {
        perror("semop (lock)");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore locked.\n");

    // Unlock (increment semaphore)
    sb.sem_op = 1;    // Increment semaphore (unlock)

    printf("Unlocking the semaphore (incrementing it)...\n");
    if (semop(semid, &sb, 1) == -1) {
        perror("semop (unlock)");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore unlocked.\n");
    
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl (IPC_RMID)");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore set removed.\n");

    return 0;
}

/******************************************OUTPUT************************************************/
/*
Semaphore created and initialized to 1 (unlocked).
Locking the semaphore (decrementing it)...
Semaphore locked.
Unlocking the semaphore (incrementing it)...
Semaphore unlocked.
Semaphore set removed.
*/

