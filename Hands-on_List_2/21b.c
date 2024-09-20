/***************************************************************************************************
 *Name: 21b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write two programs so that both can communicate by FIFO -Use two way communications.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//server program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO1 "fifo_client_to_server"
#define FIFO2 "fifo_server_to_client"

int main() {
    int fd_read, fd_write;
    char read_buffer[100], write_buffer[100];

    // Open FIFO1 for reading (Client to Server) and FIFO2 for writing (Server to Client)
    fd_read = open(FIFO1, O_RDONLY);
    fd_write = open(FIFO2, O_WRONLY);

    if (fd_read == -1 || fd_write == -1) {
        perror("Error opening FIFOs");
        exit(EXIT_FAILURE);
    }

    // Read message from the client
    read(fd_read, read_buffer, sizeof(read_buffer));
    printf("Client says: %s\n", read_buffer);

    // Send response to the client
    printf("Enter response for client: ");
    fgets(write_buffer, sizeof(write_buffer), stdin);
    write(fd_write, write_buffer, strlen(write_buffer) + 1);

    // Close FIFOs
    close(fd_read);
    close(fd_write);

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Client says: Hello from client!

Enter response for client: Hello from server!
*/

