/***************************************************************************************************
 *Name: 25b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                b. uid, gid
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

    // Print the UID and GID
    printf("User ID (UID): %d\n", buf.msg_perm.cuid);
    printf("Group ID (GID): %d\n", buf.msg_perm.cgid);

    // Clean up: Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/******************************************OUTPUT************************************************/
/*
User ID (UID): 1000
Group ID (GID): 1000
*/


