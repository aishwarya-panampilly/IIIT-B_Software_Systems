/***************************************************************************************************
 *Name: 25h.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                h. pid of the msgsnd and msgrcv
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>   // For open()
#include <unistd.h>  // For close()

int main() {
    key_t key;
    int msqid;
    struct msqid_ds buf;
    char filename[100];

    // Ask user for a file name
    printf("Enter the file name to generate the key: ");
    scanf("%s", filename);

    // Check if the file exists, if not, create it
    int fd = open(filename, O_CREAT | O_RDONLY, 0666); // Open the file, create if necessary
    if (fd == -1) {
        perror("open");
        return 1;
    }
    close(fd); // We don't need the file descriptor anymore, just needed to ensure the file exists

    // Generate an IPC key using the user inputted file name
    key = ftok(filename, 65);  // Project identifier is 65
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Get or create the message queue
    msqid = msgget(key, 0666 | IPC_CREAT);  // Create the queue if it doesn't exist
    if (msqid == -1) {
        perror("msgget");
        return 1;
    }

    // Get message queue information
    if (msgctl(msqid, IPC_STAT, &buf) == -1) {
        perror("msgctl");
        return 1;
    }

    // Print information about the last message sent and received
    printf("Last message sent by process ID: %d\n", buf.msg_lspid);
    printf("Last message received by process ID: %d\n", buf.msg_lrpid);

    return 0;
}

/******************************************OUTPUT***********************************************/
/*
Enter the file name to generate the key: file1
Last message sent by process ID: 0
Last message received by process ID: 0
*/
