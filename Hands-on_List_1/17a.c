/***************************************************************************************************
 *Name: 17a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to simulate online ticket reservation. Implement write lock
Write a program to open a file, store a ticket number and exit. Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
 *Date: 30th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
// This program is for initialisiing the ticket number
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define FILE_NAME "ticket.txt"

// Function to initialize the ticket number in the file
void initialize_ticket_number() {
    int fd;
    int ticket_number = 1;
    printf("*******TICKET RESERVATION********\n");
    // Open the file for writing and create it if it doesn't exist
    fd = open(FILE_NAME, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write the initial ticket number to the file
    if (write(fd, &ticket_number, sizeof(ticket_number)) != sizeof(ticket_number)) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Ticket number initialized to %d.\n", ticket_number);

    // Close the file
    close(fd);
}

int main() {
    initialize_ticket_number();
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
