/***************************************************************************************************
 *Name: 2.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to print the system resource limits. Use getrlimit system call.
 *Date: 17th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
// function to print resource limit
void print_rlimit(const char* name, int resource)
{
    //structure which defines soft limit and hard limit
    //soft-limit is the value that the kernel enforces for corresponding resource
    //hard-limit is the ceiling for soft limit
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
  printf("System Resource Limits\n\n");
  print_rlimit("Address Space",RLIMIT_AS);
  print_rlimit("Core File Size",RLIMIT_CORE);
  print_rlimit("CPU Time",RLIMIT_CPU);
  print_rlimit("Data Segment Size",RLIMIT_DATA);
  print_rlimit("File Size",RLIMIT_FSIZE);
  print_rlimit("Process Stack Size",RLIMIT_STACK);
  print_rlimit("Number of Queued Signals",RLIMIT_SIGPENDING);
  print_rlimit("Message Queue Size",RLIMIT_MSGQUEUE);
  print_rlimit("RAM Locked Memory",RLIMIT_MEMLOCK);
  print_rlimit("Combined Number of Locks",RLIMIT_LOCKS);
  print_rlimit("NICE value",RLIMIT_NICE);
  print_rlimit("Real-Time Scheduling Policy",RLIMIT_RTTIME);
  print_rlimit("Real-Time Priority",RLIMIT_RTPRIO);
  print_rlimit("Resident Set Size",RLIMIT_RSS);
  print_rlimit("Number of Processes",RLIMIT_NPROC);
  print_rlimit("Number of Files",RLIMIT_NOFILE);
}
      
/******************************************OUTPUT************************************************/
/*
System Resource Limits

Address Space 
Soft Limit : -1
Hard Limit : -1

Core File Size 
Soft Limit : 0
Hard Limit : -1

CPU Time 
Soft Limit : -1
Hard Limit : -1

Data Segment Size 
Soft Limit : -1
Hard Limit : -1

File Size 
Soft Limit : -1
Hard Limit : -1

Process Stack Size 
Soft Limit : 8388608
Hard Limit : -1

Number of Queued Signals 
Soft Limit : 15194
Hard Limit : 15194

Message Queue Size 
Soft Limit : 819200
Hard Limit : 819200

RAM Locked Memory 
Soft Limit : 507011072
Hard Limit : 507011072

Combined Number of Locks 
Soft Limit : -1
Hard Limit : -1

NICE value 
Soft Limit : 0
Hard Limit : 0

Real-Time Scheduling Policy 
Soft Limit : -1
Hard Limit : -1

Real-Time Priority 
Soft Limit : 0
Hard Limit : 0

Resident Set Size 
Soft Limit : -1
Hard Limit : -1

Number of Processes 
Soft Limit : 15194
Hard Limit : 15194

Number of Files 
Soft Limit : 1024
Hard Limit : 1048576

*/
