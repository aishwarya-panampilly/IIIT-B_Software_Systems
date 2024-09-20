/***************************************************************************************************
 *Name: 27a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to receive messages from the message queue.
                a. with 0 as a flag
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

    // Get the message queue ID (it must exist)
    msqid = msgget(key, 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    // Receive the message from the queue (blocking mode with flag 0)
    if (msgrcv(msqid, &msg, sizeof(msg.msg_text), 0, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }

    // Print the received message
    printf("Received message: %s\n", msg.msg_text);

    return 0;
}


/******************************************OUTPUT************************************************/
/*
Enter the file name to generate the key: file1
Received message: hello!
*/

