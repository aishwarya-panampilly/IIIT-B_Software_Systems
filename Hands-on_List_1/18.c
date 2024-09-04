/***************************************************************************************************
 *Name: 18.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to perform Record locking.
               a. Implement write lock
               b. Implement read lock
               Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
 *Date: 30th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//Record locking is a technique used to control access to specific parts or records within a file to prevent concurrent access conflicts.

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Record size and file name
#define RECORD_SIZE 32
#define FILE_NAME "records.txt"

// Function to lock a specific record
int lock_record(int fd, int record_num, short lock_type) {
    struct flock lock;
    lock.l_type = lock_type;   // F_WRLCK for write lock, F_RDLCK for read lock
    lock.l_whence = SEEK_SET;  // Relative to the start of the file
    lock.l_start = record_num * RECORD_SIZE;  // Start of the record
    lock.l_len = RECORD_SIZE;  // Length of the record

    // Try to apply the lock
    if (fcntl(fd, F_SETLKW, &lock) < 0) {
        perror("fcntl");
        return -1;
    }
    printf("Lock applied on record %d.\n", record_num + 1);
    return 0;
}

// Function to unlock a specific record
int unlock_record(int fd, int record_num) {
    struct flock lock;
    lock.l_type = F_UNLCK;     // Unlock
    lock.l_whence = SEEK_SET;  // Relative to the start of the file
    lock.l_start = record_num * RECORD_SIZE;  // Start of the record
    lock.l_len = RECORD_SIZE;  // Length of the record

    // Try to release the lock
    if (fcntl(fd, F_SETLK, &lock) < 0) {
        perror("fcntl");
        return -1;
    }
    printf("Lock released on record %d.\n", record_num + 1);
    return 0;
}

// Function to modify a record (write operation)
void modify_record(int fd, int record_num, const char *data) {
    // Lock the record for writing
    if (lock_record(fd, record_num, F_WRLCK) == 0) {
        // Seek to the record position
        lseek(fd, record_num * RECORD_SIZE, SEEK_SET);
        // Write the data (overwrite the record)
        write(fd, data, RECORD_SIZE);
        printf("Record %d modified.\n", record_num + 1);
        // Unlock the record
        unlock_record(fd, record_num);
    }
}

// Function to read a record
void read_record(int fd, int record_num) {
    char buffer[RECORD_SIZE + 1];

    // Lock the record for reading
    if (lock_record(fd, record_num, F_RDLCK) == 0) {
        // Seek to the record position
        lseek(fd, record_num * RECORD_SIZE, SEEK_SET);
        // Read the record
        read(fd, buffer, RECORD_SIZE);
        buffer[RECORD_SIZE] = '\0';  // Null-terminate the string
        printf("Record %d content: %s\n", record_num + 1, buffer);
        // Unlock the record
        unlock_record(fd, record_num);
    }
}

// Initialize the file with three records
void initialize_file(int fd) {
    const char *records[] = {
        "Record 1: Initial Data.            ",
        "Record 2: Initial Data.            ",
        "Record 3: Initial Data.            "
    };

    for (int i = 0; i < 3; i++) {
        write(fd, records[i], RECORD_SIZE);
    }
}

int main() {
    int fd;
    char data[RECORD_SIZE];
    int choice, record_num;

    // Create the file if it doesn't exist and open it for reading and writing
    fd = open(FILE_NAME, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Initialize the file with three records
    initialize_file(fd);

    while (1) {
        printf("\n1. Modify a record (Write Lock)\n");
        printf("2. Read a record (Read Lock)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter record number (1-3) to modify: ");
                scanf("%d", &record_num);
                if (record_num < 1 || record_num > 3) {
                    printf("Invalid record number!\n");
                    break;
                }
                printf("Enter new data for record %d (max %d characters): ", record_num, RECORD_SIZE - 1);
                getchar();  // Consume newline
                fgets(data, RECORD_SIZE, stdin);
                data[strcspn(data, "\n")] = 0;  // Remove newline from input
                modify_record(fd, record_num - 1, data);
                break;

            case 2:
                printf("Enter record number (1-3) to read: ");
                scanf("%d", &record_num);
                if (record_num < 1 || record_num > 3) {
                    printf("Invalid record number!\n");
                    break;
                }
                read_record(fd, record_num - 1);
                break;

            case 3:
                close(fd);
                exit(EXIT_SUCCESS);

            default:
                printf("Invalid choice! Please select a valid option.\n");
        }
    }

    return 0;
}

/******************************************OUTPUT***********************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 18.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  1. Modify a record (Write Lock)
  2. Read a record (Read Lock)
  3. Exit
  Enter your choice: 1
  Enter record number (1-3) to modify: 1
  Enter new data for record 1 (max 31 characters): hello
  Lock applied on record 1.
  Record 1 modified.
  Lock released on record 1.
  
  1. Modify a record (Write Lock)
  2. Read a record (Read Lock)
  3. Exit
  Enter your choice: 2
  Enter record number (1-3) to read: 1
  Lock applied on record 1.
  Record 1 content: hello
  Lock released on record 1.
  
  1. Modify a record (Write Lock)
  2. Read a record (Read Lock)
  3. Exit 
  Enter your choice: 3
*/




