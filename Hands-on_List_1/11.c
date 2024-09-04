/***************************************************************************************************
 *Name: 11.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not.
a. use dup
b. use dup2
c. use fcntl
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    // Open the file for appending
    int fd = open("testfile.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Duplicate the file descriptor using dup 
    int fd_dup = dup(fd);
    if (fd_dup == -1) {
        perror("Error duplicating file descriptor with dup");
        close(fd);
        return 1;
    }

    // Duplicate the file descriptor using dup2 which duplicates to a specific value
    int fd_dup2 = dup2(fd, 10); // Duplication to file descriptor 10
    if (fd_dup2 == -1) {
        perror("Error duplicating file descriptor with dup2");
        close(fd);
        close(fd_dup);
        return 1;
    }

    // Duplicate the file descriptor using fcntl
    int fd_fcntl = fcntl(fd, F_DUPFD, 0); // Duplicating the fd to the lowest available fd >= 0
    if (fd_fcntl == -1) {
        perror("Error duplicating file descriptor with fcntl");
        close(fd);
        close(fd_dup);
        close(fd_dup2);
        return 1;
    }

    // Write to the original file descriptor
    const char *text1 = "Writing with original file descriptor\n";
    if (write(fd, text1, strlen(text1)) == -1) {
        perror("Error writing to file with original fd");
    }

    // Write to the duplicated file descriptor (dup)
    const char *text2 = "Writing with dup file descriptor\n";
    if (write(fd_dup, text2, strlen(text2)) == -1) {
        perror("Error writing to file with dup fd");
    }

    // Write to the duplicated file descriptor (dup2)
    const char *text3 = "Writing with dup2 file descriptor\n";
    if (write(fd_dup2, text3, strlen(text3)) == -1) {
        perror("Error writing to file with dup2 fd");
    }

    // Write to the duplicated file descriptor (fcntl)
    const char *text4 = "Writing with fcntl file descriptor\n";
    if (write(fd_fcntl, text4, strlen(text4)) == -1) {
        perror("Error writing to file with fcntl fd");
    }

    // Close all file descriptors
    close(fd);
    close(fd_dup);
    close(fd_dup2);
    close(fd_fcntl);

    // Check the content of the file
    printf("Check the content of 'testfile.txt' to ensure the writes were successful.\n");

    return 0;
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 11.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Check the content of 'testfile.txt' to ensure the writes were successful.
  
  testfile.txt ***************************
  Writing with original file descriptor
  Writing with dup file descriptor
  Writing with dup2 file descriptor
  Writing with fcntl file descriptor
*/

