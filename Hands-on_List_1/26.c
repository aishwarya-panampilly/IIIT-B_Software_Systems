/***************************************************************************************************
 *Name: 26.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to execute an executable program.
               a. use some executable program
               b. pass some input to an executable program. (for example execute an executable of $./a.out name)
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/

//too execute an external program from a C program, you can use exec() family functions
// Here we are using a simple program "26_simple.c" as the executable program to which input is passed.It is also available in zip file 
#include <stdio.h>
#include <unistd.h>  // For execvp(), fork()
#include <sys/types.h>  // For fork()
#include <sys/wait.h>  // For wait()

int main() {
    // Define the program and arguments
    const char *program = "./a.out";
    char *const args[] = { (char *)program, "Aishwarya", NULL };

    // Fork a new process
    pid_t pid = fork();
    
    if (pid < 0) {
        printf("Error: Fork failed.\n");
        return 1;
    }
    
    if (pid == 0) {
        // Child process: Execute the external program
        execvp(program, args);
        
        // If execvp() returns, there was an error
        printf("Error: Failed to execute the program.\n");
        return 1;
    } else {
        // Parent process: Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);
        //WIFEXITED checks whether child process is terminated normally
        //WEXITSTATUS extracts exit status of child process
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            printf("Program executed successfully.\n");
        } else {
            printf("Program execution failed.\n");
        }
    }
    return 0;
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 26_simple.c
  aishjp@Aish-Linux:~/my-repo$ gcc -o a.out 26_simple.c
  aishjp@Aish-Linux:~/my-repo$ gcc 26.c -o exec_output
  aishjp@Aish-Linux:~/my-repo$ ./exec_output
  Hello, Aishwarya!
  Program executed successfully.
*/

