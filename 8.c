/***************************************************************************************************
 *Name: 8.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 1024  
#define MAX_LENGTH 256
int main() 
{ 
    char filename[MAX_LENGTH];
    // opening read and write mode withour O_EXCL
    printf ("Enter filename: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    // Remove the newline character from the filename if present
    filename[strcspn(filename, "\n")] = '\0';
    //opening file in read only mode
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file\n");
        return 1;
    }
    char buffer[BUFFER_SIZE];
    char line[BUFFER_SIZE]; // to keep track of the line
    ssize_t rd;
    ssize_t len = 0; // to keep track of length of line 

    // Read the file content
    while ((rd = read(fd, buffer, BUFFER_SIZE)) > 0) 
    {
        for (ssize_t i = 0; i < rd; i++) 
        {
            // fill line array with buffer value
            line[len++] = buffer[i];

            // If a newline character is encountered, write the line to standard output
            if (buffer[i] == '\n') 
            {
                line[len] = '\0'; // terminating the line
                sleep(1); // wait a sec before printing the line
                if (write(STDOUT_FILENO, line, len) != len) 
                {
                    perror("Error writing\n");
                    close(fd);
                    return 1;
                }
                // Reset line length after writing each line
                len = 0;
            }
        }
    }

    // If there was an error reading the file
    if (rd == -1) {
        perror("Error reading file");
    }

    // if there is any other data in the buffer which doesn't end with a newline, show error
    if (len > 0) {
        if (write(STDOUT_FILENO, line, len) != len) {
            perror("Writing error");
        }
    }
    close(fd);
    return 0;
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 8.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Enter filename: file.txt
  I am an invisible man. 
  No, I am not a spook like those who haunted Edgar Allan Poe; nor am I one of your Hollywood-movie ectoplasms. 
  I am a man of substance, of flesh and bone, fiber and liquids—and I might even be said to possess a mind. 
  I am invisible, understand, simply because people refuse to see me. 
  Like the bodiless heads you see sometimes in circus sideshows, it is as though I have been surrounded by mirrors of hard, distorting glass. 
  When they approach me they see only my surroundings, themselves, or figments of their imagination—indeed, everything and anything except me.

*/

