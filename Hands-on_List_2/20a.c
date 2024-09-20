/***************************************************************************************************
 *Name: 20a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write two programs so that both can communicate by FIFO -Use one way communication.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
// this is the writer program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_FILE "myfifo"

int main() {
    int fd;
    char buffer[100];

    // Create the FIFO (named pipe)
    if (mkfifo(FIFO_FILE, 0666) == -1) {
        perror("mkfifo failed");
        exit(EXIT_FAILURE);
    }

    printf("FIFO created. Writer is ready to send data...\n");

    // Open the FIFO for writing
    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    // Get user input
    printf("Enter a message to send: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Write the user input to the FIFO
    write(fd, buffer, strlen(buffer) + 1);

    // Close the FIFO
    close(fd);

    printf("Data written to the FIFO.\n");
    return 0;
}
/******************************************OUTPUT************************************************/
/*
FIFO created. Writer is ready to send data...
Enter a message to send: Hello from writer!
Data written to the FIFO.
*/
