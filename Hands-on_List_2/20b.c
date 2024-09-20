/***************************************************************************************************
 *Name: 20b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write two programs so that both can communicate by FIFO -Use one way communication.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//reader program
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_FILE "myfifo"

int main() {
    int fd;
    char buffer[100];

    // Open the FIFO for reading
    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    printf("Reader is ready to read data from the FIFO...\n");

    // Read data from the FIFO
    read(fd, buffer, sizeof(buffer));

    // Print the data read from the FIFO
    printf("Received: %s\n", buffer);

    // Close the FIFO
    close(fd);

    // Optionally, remove the FIFO after communication is done
    unlink(FIFO_FILE);

    return 0;
}
/******************************************OUTPUT************************************************/
/*
Reader is ready to read data from the FIFO...
Received: Hello from writer!
*/

