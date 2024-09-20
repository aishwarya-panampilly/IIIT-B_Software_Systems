/***************************************************************************************************
 *Name: 26.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to send messages to the message queue. Check $ipcs -q
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

    // Get or create the message queue
    msqid = msgget(key, 0666 | IPC_CREAT);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    // Prepare the message
    msg.msg_type = 1;  // The message type must be a positive number
    printf("Enter the message to send: ");
    getchar();  // Clear the newline from previous input
    fgets(msg.msg_text, MAX_TEXT, stdin);  // Get the message text

    // Send the message to the queue
    if (msgsnd(msqid, &msg, strlen(msg.msg_text) + 1, 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent successfully!\n");

    // Check queue status with the command: ipcs -q

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Enter the file name to generate the key: file1
Enter the message to send: hello!
Message sent successfully!

**** CHECKING ****
aishjp@Aish-Linux:~/my-repo/Hands-on_List_2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x41030df6 8          aishjp     666        8            1           
*/


