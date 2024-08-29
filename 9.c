/***************************************************************************************************
 *Name: 9.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to print the following information about a given file.
               a. inode
               b. number of hard links
               c. uid
               d. gid
               e. size
               f. block size
               g. number of blocks
               h. time of last access
               i. time of last modification
               j. time of last change
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<time.h>
int main() 
{
  // to find out information about a file, we use the stat() function.. the parameters include pathname to file and a  refernce structure stat buffer
  struct stat buffer;
  stat("file1.txt",&buffer); //this file must exist 
  //now to display properties of the file... check "man 3type stat"
  printf("File Properties\n");
  printf("Inode : %lu\n",buffer.st_ino);
  printf("Number of Hard links : %lu\n",buffer.st_nlink);
  printf("UID : %u\n",buffer.st_uid);
  printf("GID : %u\n",buffer.st_gid);
  printf("Block Size : %lu\n",buffer.st_blksize);
  printf("Number of Blocks : %lu\n",buffer.st_blocks);
  
  // time must first be converted into a readable form 
  //using stat(), the times are provided as time_t values in the struct stat structure. These time_t values are in seconds since the Unix epoch (January 1, 1970). To present these times in a human-readable format, you need to convert them from time_t to a local time representation.
  //Use localtime() to convert these time_t values into struct tm structures. This conversion provides the local time representation, breaking it down into year, month, day, hour, minute, and second.
  //Use strftime() to format the struct tm into a readable string that can be printed.
  
  char time_buf[256];
  
  strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&buffer.st_atime));
  printf("Time of last access : %s\n",time_buf);
  
  strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&buffer.st_mtime));
  printf("Time of last modification : %s\n",time_buf); 
  
  strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&buffer.st_ctime));
  printf("Time of last change : %s\n",time_buf);
  return 0;
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 9.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  File Properties
  Inode : 789183
  Number of Hard links : 1
  UID : 1000
  GID : 1000
  Block Size : 4096
  Number of Blocks : 8
  Time of last access : 2024-08-29 12:11:26
  Time of last modification : 2024-08-29 12:11:26
  Time of last change : 2024-08-29 12:11:26
*/


