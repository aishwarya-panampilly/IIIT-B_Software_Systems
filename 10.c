/***************************************************************************************************
 *Name: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Problem Statement : Write a program to open a file with read write mode, write 10 bytes, move the  
                      file pointer by 10 bytes (use lseek) and write again 10 bytes.
                      a. check the return value of lseek
                      b. open the file with od and check the empty spaces in between the data.
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open the file in read-write mode ,create if it doesn't exist
    int fd = open("testfile.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Write 10 bytes to the file
    const char *data1 = "ABCDEFGHIJ";
    ssize_t bytes_written = write(fd, data1, 10);
    if (bytes_written != 10) {
        perror("Error writing first 10 bytes");
        close(fd);
        return 1;
    }

    // Move the file pointer 10 bytes forward
    off_t offset = lseek(fd, 10, SEEK_CUR);
    if (offset == (off_t)-1) {
        perror("Error with lseek");
        close(fd);
        return 1;
    } else {
        printf("lseek succeeded. Current file offset: %ld\n", offset);
    }

    // Write another 10 bytes after the gap
    const char *data2 = "KLMNOPQRST";
    bytes_written = write(fd, data2, 10);
    if (bytes_written != 10) {
        perror("Error writing second 10 bytes");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    close(fd);

    printf("Write operations completed. Use 'od -c testfile.txt' to inspect the file.\n");

    return 0;
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc Program_10.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  lseek succeeded. Current file offset: 20
  Write operations completed. Use 'od -c testfile.txt' to inspect the file.
  aishjp@Aish-Linux:~/my-repo$ od -c testfile.txt
  0000000   A   B   C   D   E   F   G   H   I   J   t   h       o   r   i
  0000020   g   i   n   a   K   L   M   N   O   P   Q   R   S   T   c   r
  0000040   i   p   t   o   r  \n   W   r   i   t   i   n   g       w   i
  0000060   t   h       d   u   p       f   i   l   e       d   e   s   c
  0000100   r   i   p   t   o   r  \n   W   r   i   t   i   n   g       w
  0000120   i   t   h       d   u   p   2       f   i   l   e       d   e
  0000140   s   c   r   i   p   t   o   r  \n   W   r   i   t   i   n   g
  0000160       w   i   t   h       f   c   n   t   l       f   i   l   e
  0000200       d   e   s   c   r   i   p   t   o   r  \n
  0000214
*/

