/***************************************************************************************************
 *Name: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Problem Statement : Write a program to open an existing file with read write mode. Try O_EXCL  
                      also.
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main() 
{
  int fp;
  // opening read and write mode
  fp = open("file1.txt", O_EXCL | O_CREAT | O_RDWR,0666); //O_EXCL will make open() fail if file exists
  if ( fp == -1 ) {
    printf("Error opening file.File might already exist\n");
    exit(1); // exit out of program if file cannot be opened/ already exists
  }
  // to check if it is actually read/write file
  char* buffer = "Hello World!";
  //here we declare a buffer with text to write into file
  int wr = write (fp,buffer,strlen(buffer));
  if ( wr != -1 )
    printf("Successfully written string to file\n");
  else {
    printf("String could not be written to file\n");
    exit(1); //exiting from program 
    }
  // read from file onto the terminal by declaring a second buffer
  char buffer2[strlen(buffer)];
  // move file pointer back to beginning of file
  lseek(fp, 0, SEEK_SET);
  int rd = read (fp,buffer2,strlen(buffer));
  if (rd != -1) {
    buffer2[strlen(buffer)] = '\0'; //read() doesn't put termination so manually adding
    printf ("The file contents are : %s\n",buffer2);
    }
  else
    printf ("Read error\n");
  close(fp);
  return 0;
}
