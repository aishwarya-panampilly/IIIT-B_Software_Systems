/***************************************************************************************************
 *Name: 3.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to create a file and print the file descriptor value. Use creat( ) system call
 *Date: 29th August,2024                      
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <fcntl.h>
int main()
{
  int fd = creat ("file1.c", S_IRWXU | S_IRWXG | S_IRWXO); 
  if ( fd == -1 ) 
    printf("Error in creating file\n");
  else
    printf("Successfully created file titled file1.c\n");
  //giving read,write and execute permissions to user,group and others
  printf ("File Descriptor : %d\n",fd);
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 3.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Successfully created file titled file1.c
  File Descriptor : 3
*/

