/***************************************************************************************************
 *Name: 21a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write two programs so that both can communicate by FIFO -Use two way communications.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//client program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO1 "fifo_client_to_server"
#define FIFO2 "fifo_server_to_client"

int main() {
    int fd_write, fd_read;
    char write_buffer[100], read_buffer[100];

    // Create FIFO1 and FIFO2
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    // Open FIFO1 for writing (Client to Server) and FIFO2 for reading (Server to Client)
    fd_write = open(FIFO1, O_WRONLY);
    fd_read = open(FIFO2, O_RDONLY);

    if (fd_write == -1 || fd_read == -1) {
        perror("Error opening FIFOs");
        exit(EXIT_FAILURE);
    }

    // Send message to the server
    printf("Enter message for server: ");
    fgets(write_buffer, sizeof(write_buffer), stdin);
    write(fd_write, write_buffer, strlen(write_buffer) + 1);

    // Read response from the server
    read(fd_read, read_buffer, sizeof(read_buffer));
    printf("Server says: %s\n", read_buffer);

    // Close FIFOs
    close(fd_write);
    close(fd_read);

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Enter message for server: Hello from client!
Server says: Hello from server!
*/

