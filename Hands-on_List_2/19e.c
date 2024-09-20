/***************************************************************************************************
 *Name: 19e.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Create a FIFO file by
                e. mkfifo library function
 *Date: 20th September, 2024
***************************************************************************************************/
/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    const char *fifo_path = "fifo_10";

    // Create FIFO
    if (mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo failed");
        exit(1);
    }

    printf("FIFO '%s' created successfully.\n", fifo_path);
    return 0;
}

/******************************************OUTPUT************************************************/
/*
FIFO 'fifo_10' created successfully.
*/
