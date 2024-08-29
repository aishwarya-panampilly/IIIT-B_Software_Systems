/***************************************************************************************************
 *Name: 4.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to open an existing file with read write mode. Try O_EXCL also
 *Date: 29th August,2024
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
  int opt;
  // opening read and write mode withour O_EXCL
  printf ("Choose to open file \n1.With O_EXCL \n2.Without O_EXCL\n");
  scanf("%d",&opt);
  if (opt == 1) 
    fp = open("file1.txt", O_EXCL | O_CREAT | O_RDWR,0666); 
    //O_EXCL will make open() fail if file exists 
  else if (opt == 2)
    fp = open("file0.txt",O_CREAT | O_RDWR,0666);
  else
    printf("Incorrect Option\n");
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

/******************************************OUTPUT***********************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 4.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose to open file 
  1.With O_EXCL 
  2.Without O_EXCL
  1
  Successfully written string to file
  The file contents are : Hello World!
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose to open file 
  1.With O_EXCL 
  2.Without O_EXCL
  2
  Successfully written string to file
  The file contents are : Hello World!
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose to open file 
  1.With O_EXCL 
  2.Without O_EXCL
  1
  Error opening file.File might already exist

*/
