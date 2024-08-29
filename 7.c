/***************************************************************************************************
 *Name: 7.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to copy file1 into file2 ($cp file1 file2)
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1024  

int main(int argc, char *argv[]) 
{
  // we are using the command line to enter the names of the two files 
  // First file is opened for reading, this file must already be present 
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("Error in opening file\n");
    return 1;
  }
  // Second file is opened for writing
  int fd1 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC , 0666); //trunc is used to truncate file contents if it already exists
  if (fd1 == -1) {
    perror("Error opening file\n");
    return 1;
  }

  char buffer[BUFFER_SIZE];
  ssize_t rdbyte, wrbyte; //to get return values of read and write

  // Copying the file content
  while ((rdbyte = read(fd, buffer, BUFFER_SIZE)) > 0) 
  {
      wrbyte = write(fd1, buffer, rdbyte);
      if (wrbyte != rdbyte) {
          perror("Error writing to file\n");
          return 1;
      }
  }

  if (rdbyte == -1) {
        perror("Reading error\n");
  }

  // Closing the files
  close(fd);
  close(fd1);
  printf("Successfully copied from one file to another\n");
  return 0;
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 7.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out file1.txt file2.txt
  Successfully copied from one file to another
*/

