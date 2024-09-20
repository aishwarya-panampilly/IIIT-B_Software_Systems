/***************************************************************************************************
 *Name: 29.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to remove the message queue.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    key_t key;
    int msqid;
    char filename[100];

    // Ask user for a file name
    printf("Enter the file name to generate the key: ");
    scanf("%s", filename);

    // Generate an IPC key using the user inputted file name
    key = ftok(filename, 65);  // Project identifier is 65
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the message queue ID (assuming it already exists)
    msqid = msgget(key, 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    // Remove the message queue using msgctl with IPC_RMID
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl: IPC_RMID");
        exit(1);
    }

    printf("Message queue with ID %d removed successfully.\n", msqid);

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Enter the file name to generate the key: file1
Message queue with ID 8 removed successfully.
*/

