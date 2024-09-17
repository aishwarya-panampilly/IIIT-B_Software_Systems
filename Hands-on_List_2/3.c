/***************************************************************************************************
 *Name: 3.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
 *Date: 17th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>
void print_rlimit (const char* name, int resource)
{
  struct rlimit limit;
    if (getrlimit(resource,&limit) == 0 ) // successful call
    {
      printf("%s \n",name);
      printf("Soft Limit : %ld\n",limit.rlim_cur);
      printf("Hard Limit : %ld\n\n",limit.rlim_max);
    }
    else {  perror ("getrlimit system call error!"); }
}

int main()
{
  struct rlimit new_limit;
  printf("Current Limit for Open Files\n");
  print_rlimit("Number of files",RLIMIT_NOFILE);
  
  //setting new limits
  new_limit.rlim_cur = 2048;
  new_limit.rlim_max = 4096;
  
  if ( setrlimit(RLIMIT_NOFILE,&new_limit) == 0) {
    printf("New limits set successfully\n\n");
  } else {  perror("Error in setting limits"); }

  printf("New Limit for Open Files\n");
  print_rlimit("Number of files",RLIMIT_NOFILE);
  return 0;
}

/*****************************************OUTPUT************************************************/
/*
Current Limit for Open Files
Number of files 
Soft Limit : 1024
Hard Limit : 1048576

New limits set successfully

New Limit for Open Files
Number of files 
Soft Limit : 2048
Hard Limit : 4096
*/

