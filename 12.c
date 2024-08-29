/***************************************************************************************************
 *Name: 12.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to find out the opening mode of a file. Use fcntl.
 *Date: 30th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open a file in read/write mode 
    int fd = open("testfile.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Use fcntl to get the file status flags
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("Error getting file status flags");
        close(fd);
        return 1;
    }

    // Extract the access mode bits
    //O_ACCMODE is a bitmask used to isolate the access mode bits within the file status flags
    //masking out all bits of flags except for the bits that correspond to the file access mode with bitwise &
    int access_mode = flags & O_ACCMODE;

    // Determine the access mode
    if (access_mode == O_RDONLY) {
        printf("The file was opened in read-only mode.\n");
    } else if (access_mode == O_WRONLY) {
        printf("The file was opened in write-only mode.\n");
    } else if (access_mode == O_RDWR) {
        printf("The file was opened in read/write mode.\n");
    } else {
        printf("Unknown file open mode.\n");
    }

    // Close the file descriptor
    close(fd);

    return 0;
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 12.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  The file was opened in read/write mode.
*/

