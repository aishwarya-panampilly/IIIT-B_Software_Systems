/***************************************************************************************************
 *Name: 30.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to create a shared memory.
                a. write some data to the shared memory
                c. detach the shared memory
                d. remove the shared memory
 *Date: 21th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//did not write this as separate programs because of their correlation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>

#define SHM_SIZE 256  // Size of the shared memory segment

int main() {
    key_t key;
    int shmid;
    char *data;

    // Generate a unique key
    key = ftok("shmfile", 65);  // Generate unique key
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);  // Create the shared memory segment
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach to the shared memory segment
    data = shmat(shmid, NULL, 0);  // Attach
    if (data == (char*)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Write some data to the shared memory
    strncpy(data, "Hello, this is shared memory!", SHM_SIZE - 1);
    data[SHM_SIZE - 1] = '\0';  // Ensure null termination

    // Print the data written to shared memory
    printf("Data written to shared memory: %s\n", data);

    // Detach from the shared memory segment
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Attach with read-only access
    data = shmat(shmid, NULL, SHM_RDONLY);
    if (data == (char*)(-1)) {
        perror("shmat (read-only)");
        exit(EXIT_FAILURE);
    }

    // Attempt to read the data from shared memory
    printf("Data currently in shared memory: %s\n", data);

    // Detach from the shared memory segment
    if (shmdt(data) == -1) {
        perror("shmdt (detach)");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory segment detached\n");
    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl: IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory segment removed successfully.\n");

    return 0;
}
/******************************************OUTPUT***********************************************/
/*
Data written to shared memory: Hello, this is shared memory!
Data currently in shared memory: Hello, this is shared memory!
Shared memory segment detached
Shared memory segment removed successfully.
*/


