/***************************************************************************************************
 *Name: 19c.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Create a FIFO file by
                c. use strace command to find out, which command (mknod or mkfifo) is better.
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
/*
aishjp@Aish-Linux:~/my-repo/Hands-on_List_2$ strace -c mkfifo fifo_1
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 27.26    0.001534          85        18           mmap
 12.42    0.000699         699         1           execve
  8.71    0.000490          81         6           openat
  8.17    0.000460          92         5           mprotect
  8.00    0.000450          56         8           close
  6.79    0.000382          63         6           fstat
  6.49    0.000365          73         5           read
  3.57    0.000201          67         3           brk
  2.91    0.000164          82         2         2 access
  2.79    0.000157          78         2         2 statfs
  2.40    0.000135         135         1           mknodat
  2.31    0.000130          65         2           pread64
  1.76    0.000099          99         1           munmap
  1.62    0.000091          91         1           set_tid_address
  1.21    0.000068          68         1           rseq
  1.15    0.000065          65         1           getrandom
  1.14    0.000064          64         1           arch_prctl
  1.12    0.000063          63         1           set_robust_list
  0.20    0.000011          11         1           prlimit64
------ ----------- ----------- --------- --------- ----------------
100.00    0.005628          85        66         4 total
aishjp@Aish-Linux:~/my-repo/Hands-on_List_2$ strace -c mknod fifo_2
mknod: missing operand after ‘fifo_2’
Try 'mknod --help' for more information.
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 37.28    0.000642         642         1           execve
 23.98    0.000413          21        19           mmap
 10.45    0.000180          16        11         3 openat
  7.14    0.000123          61         2           pread64
  5.40    0.000093          13         7           read
  4.94    0.000085           8        10           close
  3.77    0.000065           8         8           fstat
  1.97    0.000034           8         4           write
  1.34    0.000023          11         2         2 access
  1.28    0.000022           4         5           mprotect
  0.64    0.000011          11         1           rseq
  0.52    0.000009           3         3           brk
  0.46    0.000008           8         1           set_tid_address
  0.41    0.000007           7         1           arch_prctl
  0.41    0.000007           7         1           set_robust_list
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         2         2 statfs
  0.00    0.000000           0         1           prlimit64
  0.00    0.000000           0         1           getrandom
------ ----------- ----------- --------- --------- ----------------
100.00    0.001722          21        81         7 total
*/

//mkfifo is better than mknod because mknod performs additional tasks or system calls whereas mkfifo is specifically tailored to the task.
