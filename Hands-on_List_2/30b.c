/***************************************************************************************************
 *Name: 30b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to create a shared memory.
                b. attach with O_RDONLY and check whether you are able to overwrite.
 *Date: 21th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
// attempts to overwrite will result in segmentation fault
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
    key = ftok("shmfile", 65);  // Generate unique key using a file and a project identifier
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);  // Create shared memory segment
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach to the shared memory segment to write data (in read/write mode)
    data = shmat(shmid, NULL, 0);  // Attach to shared memory
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Write some data to the shared memory (in write mode)
    strncpy(data, "Hello, this is shared memory!", SHM_SIZE - 1);
    data[SHM_SIZE - 1] = '\0';  // Null-terminate to avoid overflow

    // Detach from the shared memory after writing
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Now attach to the shared memory in read-only mode
    data = shmat(shmid, NULL, SHM_RDONLY);  // Attach with SHM_RDONLY flag
    if (data == (char *)(-1)) {
        perror("shmat (read-only)");
        exit(EXIT_FAILURE);
    }

    // Attempt to overwrite the data (should fail and cause a segmentation fault)
    printf("Data currently in shared memory (read-only): %s\n", data);
    printf("Attempting to overwrite data in read-only mode...\n");

    // This line should cause a segmentation fault as it's a write attempt in read-only memory
    strncpy(data, "Attempt to overwrite!", SHM_SIZE - 1);

    // Detach from the shared memory segment after trying to overwrite
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl: IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory segment removed successfully.\n");

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Data currently in shared memory (read-only): Hello, this is shared memory!
Attempting to overwrite data in read-only mode...
Segmentation fault (core dumped)
*/

