/***************************************************************************************************
 *Name: 22.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <string.h>
#include <time.h>

#define FIFO_NAME "my_fifo_new"
#define BUFFER_SIZE 256

int main() {
    // Create FIFO if it does not exist
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Open the FIFO for reading
    int fifo_fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK);
    if (fifo_fd == -1) {
        perror("open (read)");
        exit(EXIT_FAILURE);
    }

    // Open the FIFO for writing
    int write_fd = open(FIFO_NAME, O_WRONLY);
    if (write_fd == -1) {
        perror("open (write)");
        exit(EXIT_FAILURE);
    }

    fd_set read_fds;
    struct timeval timeout;
    char buffer[BUFFER_SIZE];

    while (1) {
        // Clear the set and add the FIFO descriptor
        FD_ZERO(&read_fds);
        FD_SET(fifo_fd, &read_fds);

        // Set timeout for 10 seconds
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        printf("You can write data to the FIFO. Type 'exit' to quit.\n");

        // Wait for data to be written to the FIFO or for the user input
        int result = select(fifo_fd + 1, &read_fds, NULL, NULL, &timeout);

        if (result == -1) {
            perror("select");
            break;
        } else if (result == 0) {
            printf("Timeout occurred! No data written to FIFO in 10 seconds.\n");
        } else {
            // Check if the FIFO is ready for reading
            if (FD_ISSET(fifo_fd, &read_fds)) {
                // Read data from FIFO
                ssize_t bytes_read = read(fifo_fd, buffer, sizeof(buffer) - 1);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';  // Null-terminate the string
                    printf("Received from FIFO: %s\n", buffer);
                }
            }
        }

        // Prompt user for input
        char user_input[BUFFER_SIZE];
        printf("Enter data to write to FIFO (or 'exit' to quit): ");
        if (fgets(user_input, sizeof(user_input), stdin) != NULL) {
            user_input[strcspn(user_input, "\n")] = '\0';  // Remove newline character

            // Check for exit condition
            if (strcmp(user_input, "exit") == 0) {
                break;
            }

            // Write data to FIFO
            write(write_fd, user_input, strlen(user_input) + 1);
        }
    }

    // Cleanup: Close the FIFO and remove it
    close(fifo_fd);
    close(write_fd);
    unlink(FIFO_NAME);

    return 0;
}
/******************************************OUTPUT************************************************/
/*
*** Terminal 1 ***
You can write data to the FIFO. Type 'exit' to quit.
Received from FIFO: hello

Enter data to write to FIFO (or 'exit' to quit): exit

*** Terminal 2 ***
echo "hello" > my_fifo_new
*/


