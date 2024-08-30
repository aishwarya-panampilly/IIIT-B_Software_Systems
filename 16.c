/***************************************************************************************************
 *Name: 16.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to perform mandatory locking.
               a. Implement write lock
               b. Implement read lock
 *Date: 30th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//Mandatory locking is a file locking mechanism in Unix-like operating systems that enforces access control on files such that the operating system will automatically block any access (read or write) to a file that is locked by another process. Unlike advisory locking, where processes voluntarily cooperate to follow the locking protocol, mandatory locking forces all processes to respect the lock
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

void set_mandatory_locking_mode(const char *file_name) {
    struct stat file_stat;

    // Get current file permissions
    if (stat(file_name, &file_stat) < 0) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Set SGID bit and remove group-execute permission
    if (chmod(file_name, (file_stat.st_mode | S_ISGID) & ~S_IXGRP) < 0) {
        perror("chmod");
        exit(EXIT_FAILURE);
    }
}

void apply_lock(int fd, short lock_type) {
    struct flock lock;
    lock.l_type = lock_type;   // F_WRLCK for write lock, F_RDLCK for read lock
    lock.l_whence = SEEK_SET;  // Lock from the beginning of the file
    lock.l_start = 0;          // Start offset
    lock.l_len = 0;            // Lock the whole file (0 means until EOF)

    // Apply the lock
    if (fcntl(fd, F_SETLKW, &lock) < 0) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    printf("Lock applied.\n");
}

void release_lock(int fd) {
    struct flock lock;
    lock.l_type = F_UNLCK;     // Unlock
    lock.l_whence = SEEK_SET;  // From the beginning of the file
    lock.l_start = 0;          // Start offset
    lock.l_len = 0;            // Unlock the whole file

    // Release the lock
    if (fcntl(fd, F_SETLK, &lock) < 0) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    printf("Lock released.\n");
}

int main() {
    const char *file_name = "testfile.txt";
    int choice;
    char release;

    int fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);  // Create file with read and write permissions
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    close(fd);

    // Set mandatory locking mode on the file
    set_mandatory_locking_mode(file_name);

    // Open the file again for read/write
    fd = open(file_name, O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Choose an operation:\n");
    printf("1. Apply write lock\n");
    printf("2. Apply read lock\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:  // Write Lock
            printf("Applying write lock...\n");
            apply_lock(fd, F_WRLCK);

            // Perform some write operations
            write(fd, "Hello, World!", 13);
            printf("Data written to file.\n");

            // Wait for the user to release the lock
            printf("Press any key followed by Enter to release the lock...\n");
            scanf(" %c", &release);

            // Release the write lock
            release_lock(fd);
            break;

        case 2:  // Read Lock
            printf("Applying read lock...\n");
            apply_lock(fd, F_RDLCK);

            // Simulate reading from the file
            char buffer[100];
            lseek(fd, 0, SEEK_SET);  // Move file pointer to the beginning
            read(fd, buffer, sizeof(buffer));
            printf("Data read from file: %s\n", buffer);

            // Wait for the user to release the lock
            printf("Press any key followed by Enter to release the lock...\n");
            scanf(" %c", &release);

            // Release the read lock
            release_lock(fd);
            break;

        default:
            printf("Invalid choice.\n");
            break;
    }

    // Close the file
    close(fd);

    return 0;
}

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 16.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose an operation:
  1. Apply write lock
  2. Apply read lock
  Enter your choice: 1
  Applying write lock...
  Lock applied.
  Data written to file.
  Press any key followed by Enter to release the lock...
  
  //opening up a new terminal and executing the program again
  
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose an operation:
  1. Apply write lock
  2. Apply read lock
  Enter your choice: 1
  Applying write lock...
  
  //this will wait until the other lock has been released, we release the other lock
  
  aishjp@Aish-Linux:~/my-repo$ gcc 16.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose an operation:
  1. Apply write lock
  2. Apply read lock
  Enter your choice: 1
  Applying write lock...
  Lock applied.
  Data written to file.
  Press any key followed by Enter to release the lock...
  1
  Lock released.
  
  //Now the second terminal will apply the write lock that can also be released according to user wishes
  
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Choose an operation:
  1. Apply write lock
  2. Apply read lock
  Enter your choice: 1
  Applying write lock...
  Lock applied.
  Data written to file.
  Press any key followed by Enter to release the lock...
  2
  Lock released.
*/


  
  


