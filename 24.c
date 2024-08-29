/***************************************************************************************************
 *Name: 24.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to create an orphan process
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    // fork() Create a child process
    
    // to prevent terminal from exiting
    int pid = fork();
    if (pid > 0) {
        //getpid() returns process id
        // while getppid() will return parent process id
        printf("Parent process\n");
        printf("ID : %d\n\n", getpid());
    }
    else if (pid == 0) {
        printf("Child process\n");
        // getpid() will return process id of child process
        printf("ID: %d\n", getpid());
        // getppid() will return parent process id of child process
        printf("Parent -ID: %d\n\n", getppid());

        sleep(10);

        // At this time parent process has finished.
        // So if u will check parent process id
        // it will show different process id
        printf("\nChild process \n");
        printf("ID: %d\n", getpid());
        printf("Parent -ID: %d\n", getppid());
    }
    else {
        printf("Failed to create child process");
    }

    return 0;
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 24.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Parent process
  ID : 33283

  Child process
  ID: 33284
  Parent -ID: 2487
  
  aishjp@Aish-Linux:~/my-repo$ 
  Child process 
  ID: 33284
  Parent -ID: 2487
*/

