/***************************************************************************************************
 *Name: 28.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
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
    struct msqid_ds buf;
    char filename[100];
    int new_perms;

    // Ask user for a file name
    printf("Enter the file name to generate the key: ");
    scanf("%s", filename);

    // Generate an IPC key using the user inputted file name
    key = ftok(filename, 65);  // Project identifier is 65
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the message queue ID (don't cause failure if the queue already exists)
    msqid = msgget(key, 0666 | IPC_CREAT);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    // Get the current message queue status
    if (msgctl(msqid, IPC_STAT, &buf) == -1) {
        perror("msgctl: IPC_STAT");
        exit(1);
    }

    // Display current permissions
    printf("Current permissions: %o\n", buf.msg_perm.mode);

    // Ask user for new permissions in octal format (e.g., 0666, 0600)
    printf("Enter new permissions (in octal): ");
    scanf("%o", &new_perms);

    // Change the permissions
    buf.msg_perm.mode = new_perms;

    // Set the updated message queue information
    if (msgctl(msqid, IPC_SET, &buf) == -1) {
        perror("msgctl: IPC_SET");
        exit(1);
    }

    // Confirm that the permissions were changed
    printf("Permissions successfully updated to: %o\n", buf.msg_perm.mode);

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Enter the file name to generate the key: file1
Current permissions: 666
Enter new permissions (in octal): 644
Permissions successfully updated to: 644
*/
