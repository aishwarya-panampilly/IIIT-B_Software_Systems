/***************************************************************************************************
 *Name: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Problem Statement : Find out the priority of your running program. Modify the priority with nice
                      command
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <sys/resource.h> //for getpriority()
#include <unistd.h> // for nice()
#include <stdlib.h>
#include <errno.h> //for errno
int main()
{
  // to find out priority we need to use getpriority() with PRIO_PROCESS that indicates priority of a process. This requires pid of process
  pid_t procid;
  int pr; //to store priority value
  procid = getpid();
  pr = getpriority(PRIO_PROCESS,procid);
  // failure will give -1 and set errno but success can also give -1 so check errno 
  if ( pr == -1 && errno != 0) 
  {
    printf("Error!\n");
    exit(1);
  }
  printf ("The priority of the running process with PID: %d is %d\n",procid,pr);
  // now using nice(inc) to change priority by inc value, higher nice means lower priority
  pr = nice(5); //increasing nice value and decreasing priority
  // if we want to increase priority we must run this program as root user
  // failure will give -1 and set errno but success can also give -1 so check errno 
  if ( pr == -1 && errno != 0) 
  {
    printf("Error!\n");
    exit(1);
  }
  printf("The new priority of the running process with PID: %d id %d\n",procid,pr);
  return 0;
}
  
  
  

