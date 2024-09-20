/***************************************************************************************************
 *Name: 27b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to receive messages from the message queue.
                b. with IPC_NOWAIT as a flag
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

#define MAX_TEXT 512

// Structure for message
struct message {
    long msg_type;
    char msg_text[MAX_TEXT];
};

int main() {
    key_t key;
    int msqid;
    struct message msg;
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

    // Try to receive the message from the queue using IPC_NOWAIT (non-blocking mode)
    // Here, we receive the first message of any type (msg_type = 0)
    if (msgrcv(msqid, &msg, sizeof(msg.msg_text), 0, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            printf("No messages available in the queue.\n");
        } else {
            perror("msgrcv");
        }
        exit(1);
    }

    // Print the received message
    printf("Received message: %s\n", msg.msg_text);

    return 0;
}

/******************************************OUTPUT************************************************/
/*
Enter the file name to generate the key: file1
Received message: for the 27b program rerun
*/
