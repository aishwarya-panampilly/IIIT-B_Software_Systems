/***************************************************************************************************
 *Name: 25e.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                e.size of the queue
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds buf;

    // Generate a unique key for the message queue
    key = ftok("progfile", 65); // Make sure "progfile" exists
    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    // Get the message queue ID
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    // Retrieve the message queue attributes
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl failed");
        exit(EXIT_FAILURE);
    }

    // Print the size of the queue (number of messages)
    printf("Size of the Message Queue (Number of Messages): %lu\n", buf.msg_qnum);

    // Clean up: Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/******************************************OUTPUT************************************************/
/*
Size of the Message Queue (Number of Messages): 0
*/
