/***************************************************************************************************
 *Name: 24.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to create a message queue and print the key and message queue id
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

int main() {
    // Define a key for the message queue
    key_t key;
    
    // Generate a unique key using ftok
    key = ftok("progfile", 65); // You can replace "progfile" with your file
    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    // Create a message queue
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    // Print the key and message queue ID
    printf("Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

/******************************************OUTPUT***********************************************/
/*
Key: 1090719202
Message Queue ID: 0
*/

