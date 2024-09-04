/***************************************************************************************************
 *Name: 14.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to find the type of a file.
               a. Input should be taken from command line.
               b. program should be able to identify any type of a file.
 *Date: 30th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    struct stat file_stat;

    // Use stat to retrieve file information
    if (stat(file_path, &file_stat) == -1) {
        perror("Error getting file information");
        return 1;
    }

    // Determine and print the type of the file
    if (S_ISREG(file_stat.st_mode)) {
        printf("%s is a regular file.\n", file_path);
    } else if (S_ISDIR(file_stat.st_mode)) {
        printf("%s is a directory.\n", file_path);
    } else if (S_ISCHR(file_stat.st_mode)) {
        printf("%s is a character device.\n", file_path);
    } else if (S_ISBLK(file_stat.st_mode)) {
        printf("%s is a block device.\n", file_path);
    } else if (S_ISFIFO(file_stat.st_mode)) {
        printf("%s is a FIFO (named pipe).\n", file_path);
    } else if (S_ISLNK(file_stat.st_mode)) {
        printf("%s is a symbolic link.\n", file_path);
    } else if (S_ISSOCK(file_stat.st_mode)) {
        printf("%s is a socket.\n", file_path);
    } else {
        printf("%s is of unknown type.\n", file_path);
    }

    return 0;
}
/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 14.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out file.txt
  file.txt is a regular file.
*/
