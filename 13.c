/***************************************************************************************************
 *Name: 13.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to verify whether the data is available within 10 seconds or not (check in $man 2 select).
 *Date: 30th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//select() system call can be used to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O operation
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

int main() {
    // Set up the file descriptor set
    fd_set readfds;
    FD_ZERO(&readfds);  // Clear the set
    FD_SET(STDIN_FILENO, &readfds);  // Add STDIN to the set

    // Set up the timeout
    struct timeval timeout;
    timeout.tv_sec = 10;  // seconds
    timeout.tv_usec = 0;  // microseconds

    // Call select to wait for input on STDIN
    printf("Waiting for input on STDIN (10 seconds)...\n");
    int retval = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select error");
    } else if (retval == 0) {
        printf("No data was entered within 10 seconds.\n");
    } else {
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            printf("Data is available on STDIN!\n");
            char buffer[1024];
            int bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';  // Null-terminate the string
                printf("You entered: %s", buffer);
            } else {
                printf("Error reading from STDIN.\n");
            }
        }
    }

    return 0;
}
/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 13.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Waiting for input on STDIN (10 seconds)...
  hello there
  Data is available on STDIN!
  You entered: hello there
*/

