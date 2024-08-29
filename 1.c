/***************************************************************************************************
 *Name: 1.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Create the following types of a files using (i) shell command (ii) system call
                      a. soft link (symlink system call)
                      b. hard link (link system call)
                      c. FIFO (mkfifo Library Function or mknod system call) 
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/

/*********SHELL COMMANDS***********/

/******SOFT LINK ********

 * Linking special files to existing files 
 * ln -s (file path to be pointed to) (new file path)
 * If we are taking existing file "file1.txt" which contains text "Hello World!" and making
 *"file2.txt" point to it, use the following
 * ln -s file1.txt file2.txt
 * Link can be checked using ls -l command
 
 ******HARD LINK ********
 
 * Linking file names and actual data stored on file system
 * Initially there is one link , a new hard link can be created using command
 * ln (original file path) (new file path)
 * If we take exisitng file "file1.txt" as above and make "file3.txt" point to it, use as follows
 * ln file1.txt file3.txt
 * Use find . -samefile file1.txt to check hardlink
 
 ******FIFO **************
 
 * It is a named pipe
 * mkfifo (filename)
 * If filename is hop1fifo then 
 * mkfifo hop1fifo
 * Write into this pipe with 
 * echo "Hello World!" > hop1fifo &
 * Use cat to display file contents
 
*/
/******SYSTEM CALL******************/
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
  //creating a new file 
  FILE *fp;
  fp = fopen("file4.txt","w");
  int ch;
  while(1) {
    printf ("Choose Option for file4.txt \n 1. Soft Link \n 2. Hard Link \n 3. FIFO \n 4. Exit\n");
    scanf ("%d",&ch);
    switch (ch)
    {
      case 1 : { 
          //creating a softlink to this file using symlink
          int sftlnk = symlink("file4.txt","file5.txt");
          //check if it is created
          if (sftlnk == 0) {
            printf("Soft Link from file5.txt to file4.txt created successfully\n");
          }
          break;
        }
    
      case 2 : {
          //creating a hardlink to this file using link
          int hrdlnk = link ("file4.txt","file6.txt");
          //check if it is created
          if (hrdlnk == 0) {
            printf("Hard Link created successfully.file4.txt and file6.txt linked to same data\n");
          }
          break;
        }
    
      case 3 : {
          int fif = mkfifo ("file7.txt",0666); // read & write permissions for everyone
          //check if it is created
          if (fif == 0) {
            printf("FIFO file titled file7.txt created successfully\n");
          }
          break;
        }
    
      case 4 : exit(0);
    
      default : printf("Incorrect Option Entered!");
        break;
    } 
  }
  return 0;
}
  
/******************************************OUTPUT***********************************************/
/***** SHELL COMMAND *****/
/*
  Soft Link
  aishjp@Aish-Linux:~/my-repo$ ln -s file1.txt file2.txt
  aishjp@Aish-Linux:~/my-repo$ ls -l file1.txt file2.txt
  -rw-rw-r-- 1 aishjp aishjp 54 Aug 22 08:36 file1.txt
  lrwxrwxrwx 1 aishjp aishjp  9 Aug 29 07:27 file2.txt -> file1.txt
  
  Hard Link
  aishjp@Aish-Linux:~/my-repo$ ln file1.txt file3.txt
  aishjp@Aish-Linux:~/my-repo$ ls -l file1.txt file3.txt
  -rw-rw-r-- 2 aishjp aishjp 54 Aug 22 08:36 file1.txt
  -rw-rw-r-- 2 aishjp aishjp 54 Aug 22 08:36 file3.txt
  aishjp@Aish-Linux:~/my-repo$ find . -samefile file1.txt
  ./file1.txt
  ./file3.txt
  
  FIFO
  aishjp@Aish-Linux:~/my-repo$ mkfifo 1prog
  aishjp@Aish-Linux:~/my-repo$ echo "Hello World!" > 1prog &
  [1] 20727
  aishjp@Aish-Linux:~/my-repo$ cat 1prog
  Hello World!
  [1]+  Done                    echo "Hello World!" > 1prog
  aishjp@Aish-Linux:~/my-repo$ ls -l 1prog
  prw-rw-r-- 1 aishjp aishjp 0 Aug 29 07:34 1prog
  
*/
/****** PROGRAM ******/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 1.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose Option for file4.txt 
    1. Soft Link 
    2. Hard Link 
    3. FIFO 
    4. Exit
  1
  Soft Link from file5.txt to file4.txt created successfully
  Choose Option for file4.txt 
    1. Soft Link 
    2. Hard Link 
    3. FIFO 
    4. Exit
  2
  Hard Link created successfully.file4.txt and file6.txt linked to same data
  Choose Option for file4.txt 
    1. Soft Link 
    2. Hard Link 
    3. FIFO 
    4. Exit
  3
  FIFO file titled file7.txt created successfully
  Choose Option for file4.txt 
    1. Soft Link 
    2. Hard Link 
    3. FIFO 
    4. Exit
  4
  aishjp@Aish-Linux:~/my-repo$ ls -l file4.txt file5.txt file6.txt file7.txt
  -rw-rw-r-- 2 aishjp aishjp 0 Aug 29 07:20 file4.txt
  lrwxrwxrwx 1 aishjp aishjp 9 Aug 29 07:20 file5.txt -> file4.txt
  -rw-rw-r-- 2 aishjp aishjp 0 Aug 29 07:20 file6.txt
  prw-rw-r-- 1 aishjp aishjp 0 Aug 29 07:20 file7.txt
  aishjp@Aish-Linux:~/my-repo$ find . -samefile file4.txt
  ./file6.txt
  ./file4.txt

*/  


