/***************************************************************************************************
 *Name: 19d.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Create a FIFO file by
                d. mknod system call
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    const char *fifo_path = "my_fifo";

    // Create FIFO
    if (mknod(fifo_path, S_IFIFO | 0666, 0) == -1) {
        perror("mknod failed");
        exit(1);
    }

    printf("FIFO '%s' created successfully.\n", fifo_path);
    return 0;
}
/******************************************OUTPUT************************************************/
/*
FIFO 'my_fifo' created successfully.
*/

