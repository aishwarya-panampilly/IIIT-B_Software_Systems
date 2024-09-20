/***************************************************************************************************
 *Name: 25a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                a. access permission
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

    // Print the access permissions
    printf("Access Permissions:\n");
    printf("User Permissions: %o\n", buf.msg_perm.mode & 0077);
    printf("Group Permissions: %o\n", (buf.msg_perm.mode >> 3) & 0077);
    printf("Other Permissions: %o\n", (buf.msg_perm.mode >> 6) & 0077);

    // Clean up: Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/******************************************OUTPUT************************************************/
/*
Access Permissions:
User Permissions: 66
Group Permissions: 66
Other Permissions: 6
*/

