/***************************************************************************************************
 *Name: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Problem Statement : Write a program to create a file and print the file descriptor value. Use
                      creat( ) system call
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <fcntl.h>
int main()
{
  int fd = creat ("file1.c", S_IRWXU | S_IRWXG | S_IRWXO); 
  //giving read,write and execute permissions to user,group and others
  printf ("File Descriptor : %d\n",fd);
}
