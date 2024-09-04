/***************************************************************************************************
 *Name: 17b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to simulate online ticket reservation. Implement write lock
Write a program to open a file, store a ticket number and exit. Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
 *Date: 30th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//This program is for incrementing the ticket number
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define FILE_NAME "ticket.txt"

// Function to apply a write lock and update the ticket number
void update_ticket_number() {
    int fd;
    int ticket_number;
    struct flock lock;
    printf("*******TICKET RESERVATION********\n");
    // Open the file for reading and writing
    fd = open(FILE_NAME, O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Set up the lock structure for a write lock
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(ticket_number);

    // Apply the write lock
    if (fcntl(fd, F_SETLKW, &lock) < 0) {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Read the current ticket number
    if (read(fd, &ticket_number, sizeof(ticket_number)) != sizeof(ticket_number)) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Increment the ticket number
    ticket_number++;

    // Seek to the beginning of the file and write the new ticket number
    lseek(fd, 0, SEEK_SET);
    if (write(fd, &ticket_number, sizeof(ticket_number)) != sizeof(ticket_number)) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("New ticket number is %d.\n", ticket_number);

    // Release the lock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) < 0) {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Close the file
    close(fd);
}

int main() {
    update_ticket_number();
    return 0;
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc -o initialise 17a.c
  aishjp@Aish-Linux:~/my-repo$ gcc -o update 17b.c
  aishjp@Aish-Linux:~/my-repo$ ./initialise
  *******TICKET RESERVATION********
  Ticket number initialized to 1.
  aishjp@Aish-Linux:~/my-repo$ ./update
  *******TICKET RESERVATION********
  New ticket number is 2.
  aishjp@Aish-Linux:~/my-repo$ ./update
  *******TICKET RESERVATION********
  New ticket number is 3.
*/

