/***************************************************************************************************
 *Name: 31b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to create a semaphore and initialize value to the semaphore.
                b. create a counting semaphore
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
    int init_value;  // To store the initial value of the counting semaphore
    struct sembuf sb;  // Structure for semaphore operations

    // Generate a unique key for the semaphore
    key = ftok("semfile", 65);  // Use a file and project ID to generate a key
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a semaphore set with 1 semaphore (counting semaphore)
    semid = semget(key, 1, 0666 | IPC_CREAT);  // Create a semaphore
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Get the initial value for the counting semaphore from the user
    printf("Enter initial value for the counting semaphore: ");
    scanf("%d", &init_value);

    // Initialize the semaphore value to the user-specified value
    if (semctl(semid, 0, SETVAL, init_value) == -1) {
        perror("semctl (SETVAL)");
        exit(EXIT_FAILURE);
    }

    printf("Counting semaphore created and initialized to %d.\n", init_value);

    // Perform a semaphore operation to lock (decrement)
    sb.sem_num = 0;   // Semaphore index 0 (since we have only one semaphore in the set)
    sb.sem_op = -1;   // Decrement the semaphore (lock one resource)
    sb.sem_flg = 0;   // Wait until semaphore is available

    printf("Locking one resource (decrementing semaphore)...\n");
    if (semop(semid, &sb, 1) == -1) {
        perror("semop (lock)");
        exit(EXIT_FAILURE);
    }
    printf("Resource locked (semaphore decremented).\n");

    // Perform a semaphore operation to unlock (increment)
    sb.sem_op = 1;    // Increment the semaphore (unlock one resource)

    printf("Unlocking one resource (incrementing semaphore)...\n");
    if (semop(semid, &sb, 1) == -1) {
        perror("semop (unlock)");
        exit(EXIT_FAILURE);
    }
    printf("Resource unlocked (semaphore incremented).\n");
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl: IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore set removed.\n");

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Enter initial value for the counting semaphore: 3
Counting semaphore created and initialized to 3.
Locking one resource (decrementing semaphore)...
Resource locked (semaphore decremented).
Unlocking one resource (incrementing semaphore)...
Resource unlocked (semaphore incremented).
Semaphore set removed.
*/

