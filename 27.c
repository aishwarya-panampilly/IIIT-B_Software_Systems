/***************************************************************************************************
 *Name: 27.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to execute ls -Rl by the following system calls
               a. execl
               b. execlp
               c. execle
               d. execv
               e. execvp
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//exec functions in Unix-like operating systems are used to execute a new program, replacing the current process image with a new process image. When one of the exec functions is called successfully, it does not return to the original program. Instead, the new program takes over the process's memory space and execution context
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    int ch;
    char *args[] = {"ls", "-Rl", NULL};
    printf ("Choose which exec function to execute\n 1.execl\n 2.execlp\n 3.execle\n 4.execv\n 5.execvp\n Enter option: ");
    scanf("%d",&ch);
    switch (ch) 
    {
      case 1 : {
                  
                  printf("Executing with execl:\n"); //Executes a program with a specified list of arguments.
                  execl("/bin/ls", "ls", "-Rl", (char *)NULL);
                  // If execl fails, new program wont be executed, so the following code will be executed
                  perror("execl failed");
                  exit(1);
              }
              break;
      
     case 2 : {
                  //executes ls found in PATH
                  printf("Executing with execlp:\n");
                  execlp("ls", "ls", "-Rl", (char *)NULL);

                  // If execlp fails
                  perror("execlp failed");
                  exit(1);
                }
                break;
                
     case 3 : {
                  //excutes in a custom environment
                  // Environment for execle
                  char *env[] = { NULL };
                  printf("Executing with execle:\n");
                  execle("/bin/ls", "ls", "-Rl", (char *)NULL, env);

                  // If execle fails
                  perror("execle failed");
                  exit(1);
               }
               break;
     
     case 4 : {
                  //executes with arguements in array
                  printf("Executing with execv:\n");
                  execv("/bin/ls", args);
                  // If execv fails
                  perror("execv failed");
                  exit(1);
              }
              break;
              
     case 5 : {
                //executes using arguements and PATH
                printf("Executing with execvp:\n");
                execvp("ls", args);
                // If execvp fails
                perror("execvp failed");
                exit(1);
              }
              break;
              
     default : printf("Invalid option entered");
               break;
    }
    return 0;
}
/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 27.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose which exec function to execute
  1.execl
  2.execlp
  3.execle
  4.execv
  5.execvp
  Enter option: 1
  Executing with execl:
  .:
  total 136
  -rw-rw-r-- 1 aishjp aishjp  3392 Aug 29 14:33 10.c
  -rw-rw-r-- 1 aishjp aishjp  5246 Aug 29 07:37 1.c
  -rw-rw-r-- 1 aishjp aishjp   784 Aug 29 00:10 21.c
  -rw-rw-r-- 1 aishjp aishjp  3246 Aug 29 18:26 27.c
  -rw-rw-r-- 1 aishjp aishjp  2145 Aug 29 16:46 28.c
  -rw-rw-r-- 1 aishjp aishjp  3781 Aug 29 16:23 29.c
  -rw-rw-r-- 1 aishjp aishjp  1971 Aug 29 08:55 2.c
  -rw-rw-r-- 1 aishjp aishjp  5863 Aug 29 15:56 30.c
  -rw-rw-r-- 1 aishjp aishjp  1125 Aug 29 08:55 3.c
  -rw-rw-r-- 1 aishjp aishjp  2622 Aug 29 08:55 4.c
  -rw-rw-r-- 1 aishjp aishjp  3331 Aug 29 09:13 5.c
  -rw-rw-r-- 1 aishjp aishjp  1726 Aug 29 09:41 6.c
  -rw-rw-r-- 1 aishjp aishjp  1882 Aug 29 10:20 7.c
  -rw-rw-r-- 1 aishjp aishjp  2969 Aug 29 11:48 8.c
  -rw-rw-r-- 1 aishjp aishjp  3043 Aug 29 12:14 9.c
  -rwxrwxr-x 1 aishjp aishjp   415 Aug 29 15:37 addition_script.sh
  -rwxrwxr-x 1 aishjp aishjp 16392 Aug 29 18:27 a.out
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 14:07 file1.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:16 file2.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:19 file3.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:27 file4.txt
  -rw-rw-r-- 1 aishjp aishjp   597 Aug 29 11:17 file.txt
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 13:53 hello
  -rw-rw-r-- 1 aishjp aishjp   761 Aug 28 17:22 Program_10.c
  -rw-rw-r-- 1 aishjp aishjp   862 Aug 28 17:11 Program_15.c
  -rw-rw-r-- 1 aishjp aishjp   528 Aug 28 17:32 Program_19.c
  -rw-rw-r-- 1 aishjp aishjp  1644 Aug 28 18:10 Program_20.c
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 13:55 sdsds
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose which exec function to execute
  1.execl
  2.execlp
  3.execle
  4.execv
  5.execvp
  Enter option: 2
  Executing with execlp:
  .:
  total 136
  -rw-rw-r-- 1 aishjp aishjp  3392 Aug 29 14:33 10.c
  -rw-rw-r-- 1 aishjp aishjp  5246 Aug 29 07:37 1.c
  -rw-rw-r-- 1 aishjp aishjp   784 Aug 29 00:10 21.c
  -rw-rw-r-- 1 aishjp aishjp  3246 Aug 29 18:26 27.c
  -rw-rw-r-- 1 aishjp aishjp  2145 Aug 29 16:46 28.c
  -rw-rw-r-- 1 aishjp aishjp  3781 Aug 29 16:23 29.c
  -rw-rw-r-- 1 aishjp aishjp  1971 Aug 29 08:55 2.c
  -rw-rw-r-- 1 aishjp aishjp  5863 Aug 29 15:56 30.c
  -rw-rw-r-- 1 aishjp aishjp  1125 Aug 29 08:55 3.c
  -rw-rw-r-- 1 aishjp aishjp  2622 Aug 29 08:55 4.c
  -rw-rw-r-- 1 aishjp aishjp  3331 Aug 29 09:13 5.c
  -rw-rw-r-- 1 aishjp aishjp  1726 Aug 29 09:41 6.c
  -rw-rw-r-- 1 aishjp aishjp  1882 Aug 29 10:20 7.c
  -rw-rw-r-- 1 aishjp aishjp  2969 Aug 29 11:48 8.c
  -rw-rw-r-- 1 aishjp aishjp  3043 Aug 29 12:14 9.c
  -rwxrwxr-x 1 aishjp aishjp   415 Aug 29 15:37 addition_script.sh
  -rwxrwxr-x 1 aishjp aishjp 16392 Aug 29 18:27 a.out
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 14:07 file1.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:16 file2.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:19 file3.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:27 file4.txt
  -rw-rw-r-- 1 aishjp aishjp   597 Aug 29 11:17 file.txt
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 13:53 hello
  -rw-rw-r-- 1 aishjp aishjp   761 Aug 28 17:22 Program_10.c
  -rw-rw-r-- 1 aishjp aishjp   862 Aug 28 17:11 Program_15.c
  -rw-rw-r-- 1 aishjp aishjp   528 Aug 28 17:32 Program_19.c
  -rw-rw-r-- 1 aishjp aishjp  1644 Aug 28 18:10 Program_20.c
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 13:55 sdsds
  
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose which exec function to execute
  1.execl
  2.execlp
  3.execle
  4.execv
  5.execvp
  Enter option: 3
  Executing with execle:
  .:
  total 136
  -rw-rw-r-- 1 aishjp aishjp  3392 Aug 29 14:33 10.c
  -rw-rw-r-- 1 aishjp aishjp  5246 Aug 29 07:37 1.c
  -rw-rw-r-- 1 aishjp aishjp   784 Aug 29 00:10 21.c
  -rw-rw-r-- 1 aishjp aishjp  3246 Aug 29 18:26 27.c
  -rw-rw-r-- 1 aishjp aishjp  2145 Aug 29 16:46 28.c
  -rw-rw-r-- 1 aishjp aishjp  3781 Aug 29 16:23 29.c
  -rw-rw-r-- 1 aishjp aishjp  1971 Aug 29 08:55 2.c
  -rw-rw-r-- 1 aishjp aishjp  5863 Aug 29 15:56 30.c
  -rw-rw-r-- 1 aishjp aishjp  1125 Aug 29 08:55 3.c
  -rw-rw-r-- 1 aishjp aishjp  2622 Aug 29 08:55 4.c
  -rw-rw-r-- 1 aishjp aishjp  3331 Aug 29 09:13 5.c
  -rw-rw-r-- 1 aishjp aishjp  1726 Aug 29 09:41 6.c
  -rw-rw-r-- 1 aishjp aishjp  1882 Aug 29 10:20 7.c
  -rw-rw-r-- 1 aishjp aishjp  2969 Aug 29 11:48 8.c
  -rw-rw-r-- 1 aishjp aishjp  3043 Aug 29 12:14 9.c
  -rwxrwxr-x 1 aishjp aishjp   415 Aug 29 15:37 addition_script.sh
  -rwxrwxr-x 1 aishjp aishjp 16392 Aug 29 18:27 a.out
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 14:07 file1.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:16 file2.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:19 file3.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:27 file4.txt
  -rw-rw-r-- 1 aishjp aishjp   597 Aug 29 11:17 file.txt
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 13:53 hello
  -rw-rw-r-- 1 aishjp aishjp   761 Aug 28 17:22 Program_10.c
  -rw-rw-r-- 1 aishjp aishjp   862 Aug 28 17:11 Program_15.c
  -rw-rw-r-- 1 aishjp aishjp   528 Aug 28 17:32 Program_19.c
  -rw-rw-r-- 1 aishjp aishjp  1644 Aug 28 18:10 Program_20.c
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 13:55 sdsds
  
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose which exec function to execute
  1.execl
  2.execlp
  3.execle
  4.execv
  5.execvp
  Enter option: 4
  Executing with execv:
  .:
  total 136
  -rw-rw-r-- 1 aishjp aishjp  3392 Aug 29 14:33 10.c
  -rw-rw-r-- 1 aishjp aishjp  5246 Aug 29 07:37 1.c
  -rw-rw-r-- 1 aishjp aishjp   784 Aug 29 00:10 21.c
  -rw-rw-r-- 1 aishjp aishjp  3246 Aug 29 18:26 27.c
  -rw-rw-r-- 1 aishjp aishjp  2145 Aug 29 16:46 28.c
  -rw-rw-r-- 1 aishjp aishjp  3781 Aug 29 16:23 29.c
  -rw-rw-r-- 1 aishjp aishjp  1971 Aug 29 08:55 2.c
  -rw-rw-r-- 1 aishjp aishjp  5863 Aug 29 15:56 30.c
  -rw-rw-r-- 1 aishjp aishjp  1125 Aug 29 08:55 3.c
  -rw-rw-r-- 1 aishjp aishjp  2622 Aug 29 08:55 4.c
  -rw-rw-r-- 1 aishjp aishjp  3331 Aug 29 09:13 5.c
  -rw-rw-r-- 1 aishjp aishjp  1726 Aug 29 09:41 6.c
  -rw-rw-r-- 1 aishjp aishjp  1882 Aug 29 10:20 7.c
  -rw-rw-r-- 1 aishjp aishjp  2969 Aug 29 11:48 8.c
  -rw-rw-r-- 1 aishjp aishjp  3043 Aug 29 12:14 9.c
  -rwxrwxr-x 1 aishjp aishjp   415 Aug 29 15:37 addition_script.sh
  -rwxrwxr-x 1 aishjp aishjp 16392 Aug 29 18:27 a.out
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 14:07 file1.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:16 file2.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:19 file3.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:27 file4.txt
  -rw-rw-r-- 1 aishjp aishjp   597 Aug 29 11:17 file.txt
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 13:53 hello
  -rw-rw-r-- 1 aishjp aishjp   761 Aug 28 17:22 Program_10.c
  -rw-rw-r-- 1 aishjp aishjp   862 Aug 28 17:11 Program_15.c
  -rw-rw-r-- 1 aishjp aishjp   528 Aug 28 17:32 Program_19.c
  -rw-rw-r-- 1 aishjp aishjp  1644 Aug 28 18:10 Program_20.c
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 13:55 sdsds
  
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose which exec function to execute
  1.execl
  2.execlp
  3.execle
  4.execv
  5.execvp
  Enter option: 5
  Executing with execvp:
  .:
  total 136
  -rw-rw-r-- 1 aishjp aishjp  3392 Aug 29 14:33 10.c
  -rw-rw-r-- 1 aishjp aishjp  5246 Aug 29 07:37 1.c
  -rw-rw-r-- 1 aishjp aishjp   784 Aug 29 00:10 21.c
  -rw-rw-r-- 1 aishjp aishjp  3246 Aug 29 18:26 27.c
  -rw-rw-r-- 1 aishjp aishjp  2145 Aug 29 16:46 28.c
  -rw-rw-r-- 1 aishjp aishjp  3781 Aug 29 16:23 29.c
  -rw-rw-r-- 1 aishjp aishjp  1971 Aug 29 08:55 2.c
  -rw-rw-r-- 1 aishjp aishjp  5863 Aug 29 15:56 30.c
  -rw-rw-r-- 1 aishjp aishjp  1125 Aug 29 08:55 3.c
  -rw-rw-r-- 1 aishjp aishjp  2622 Aug 29 08:55 4.c
  -rw-rw-r-- 1 aishjp aishjp  3331 Aug 29 09:13 5.c
  -rw-rw-r-- 1 aishjp aishjp  1726 Aug 29 09:41 6.c
  -rw-rw-r-- 1 aishjp aishjp  1882 Aug 29 10:20 7.c
  -rw-rw-r-- 1 aishjp aishjp  2969 Aug 29 11:48 8.c
  -rw-rw-r-- 1 aishjp aishjp  3043 Aug 29 12:14 9.c
  -rwxrwxr-x 1 aishjp aishjp   415 Aug 29 15:37 addition_script.sh
  -rwxrwxr-x 1 aishjp aishjp 16392 Aug 29 18:27 a.out
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 14:07 file1.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:16 file2.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:19 file3.txt
  -rw-rw-r-- 1 aishjp aishjp    10 Aug 29 14:27 file4.txt
  -rw-rw-r-- 1 aishjp aishjp   597 Aug 29 11:17 file.txt
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 13:53 hello
  -rw-rw-r-- 1 aishjp aishjp   761 Aug 28 17:22 Program_10.c
  -rw-rw-r-- 1 aishjp aishjp   862 Aug 28 17:11 Program_15.c
  -rw-rw-r-- 1 aishjp aishjp   528 Aug 28 17:32 Program_19.c
  -rw-rw-r-- 1 aishjp aishjp  1644 Aug 28 18:10 Program_20.c
  -rw-rw-r-- 1 aishjp aishjp    30 Aug 29 13:55 sdsds
  
*/


