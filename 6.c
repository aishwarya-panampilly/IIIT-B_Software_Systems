/***************************************************************************************************
 *Name: 6.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Problem Statement : Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_LENGTH 1024
int main() 
{
  char* buffer = (char*)malloc(MAX_LENGTH*sizeof(char)); //buffer of user desired length
  printf ("Enter input : ");
  fflush(stdout); 
  //this is used to ensure that message is printed before user input
  int rd = read (STDIN_FILENO,buffer,MAX_LENGTH); 
  //STDIN_FILENO is file descriptor for standard input with initial value of 0
  if ( rd == -1 ) {
    printf("Read error");
    exit(1);
  }
  else {
    buffer[rd] = '\0'; // terminating read with number of bytes read
    printf("Read successfully\n");
    // now writing to stdout using STDOUT_FILENO which is standard output file descriptor. Its typical value is 1
    printf("Required Output : ");
    fflush(stdout);
    int wr = write(STDOUT_FILENO,buffer,rd); // writing rd bytes only
    if ( wr == -1 ) {
      printf("Write error");
      exit(1);
    }
  }
  return 0;
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 6.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Enter input : Hello everyone!
  Read successfully
  Required Output : Hello everyone!
*/

  
