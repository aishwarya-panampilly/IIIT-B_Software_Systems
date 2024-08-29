/***************************************************************************************************
 *Name: 10.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
               a. check the return value of lseek
               b. open the file with od and check the empty spaces in between the data.
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256
#define DATA_SIZE 10


int main() {
    char filename[BUFFER_SIZE];
    char first_data[DATA_SIZE + 1];  // +1 for null terminator
    char second_data[DATA_SIZE + 1]; // +1 for null terminator

    printf("Enter the filename: ");
    fflush(stdout);
    ssize_t bytes_read = read(STDIN_FILENO, filename, sizeof(filename) - 1);  // Leave space for null terminator
    if (bytes_read <= 0) {
        perror("Error reading filename");
        return 1;
    }

    // Null-terminate the string and remove newline character if present
    filename[bytes_read] = '\0';
    if (filename[bytes_read - 1] == '\n') {
        filename[bytes_read - 1] = '\0';
    }

    printf("Enter the first 10 bytes to write: ");
    fflush(stdout);
    bytes_read = read(STDIN_FILENO, first_data, DATA_SIZE);
    if (bytes_read != DATA_SIZE) {
        perror("Error reading first data");
        return 1;
    }

    // Null-terminate the first data string
    first_data[DATA_SIZE] = '\0';
    if (first_data[DATA_SIZE - 1] == '\n') {
        first_data[DATA_SIZE - 1] = '\0';
    }

    // Get second 10 bytes of data from user
    printf("Enter the second 10 bytes to write: ");
    fflush(stdout);
    bytes_read = read(STDIN_FILENO, second_data, DATA_SIZE);
    if (bytes_read != DATA_SIZE) {
        perror("Error reading second data");
        return 1;
    }

    // Null-terminate the second data string
    second_data[DATA_SIZE] = '\0';
    if (second_data[DATA_SIZE - 1] == '\n') {
        second_data[DATA_SIZE - 1] = '\0';
    }

    // Open the file in read-write mode, create it if it does not exist
    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // First write: 10 bytes
    ssize_t bytes_written = write(fd, first_data, DATA_SIZE);
    if (bytes_written != DATA_SIZE) {
        perror("Error writing first 10 bytes");
        close(fd);
        return 1;
    }

    // Move the file pointer by 10 bytes using lseek
    off_t offset = lseek(fd, 10, SEEK_CUR);
    if (offset == (off_t)-1) {
        perror("Error using lseek");
        close(fd);
        return 1;
    }
    
    // Print the new file pointer position after lseek
    printf("File pointer moved to byte offset: %ld\n", (long)offset);
    fflush(stdout);

    // Second write: 10 bytes
    bytes_written = write(fd, second_data, DATA_SIZE);
    if (bytes_written != DATA_SIZE) {
        perror("Error writing second 10 bytes");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);

    return 0;
}
