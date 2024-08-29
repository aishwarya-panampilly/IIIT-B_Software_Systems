/***************************************************************************************************
 *Name: 5.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd
 *Date: 29th Auguest,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
// let us create five files after which the program is executed in the background
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
int main()
{
  // first writing the code for infinite loop as a character array
  int fp[5];
  int wr;
  // using loop with file name as part of character array;
  char *flnames[5] = {"file1.c","file2.c","file3.c","file4.c","file5.c"};
  for ( int i = 0; i < 5; i++ ) {
    fp[i] = open(flnames[i],O_CREAT | O_RDWR,0666);
    if (fp[i] == -1) {  // Check if open() failed
            perror("Error opening file");
            printf("Error opening %s (errno: %d)\n", flnames[i], errno);
    }
    printf("\nFile Descriptor for %s is %d",flnames[i],fp[i]);
   }
   printf("\n"); // flushing buffer
   for (;;){} // infinite loop
  return 0;
}
// file descriptors from 0 to 2 are standard file descriptors 

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 5.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out &
  [7] 21955
  aishjp@Aish-Linux:~/my-repo$ 
  File Descriptor for file1.c is 3
  File Descriptor for file2.c is 4
  File Descriptor for file3.c is 5
  File Descriptor for file4.c is 6
  File Descriptor for file5.c is 7

  aishjp@Aish-Linux:~/my-repo$ cd /proc/21955
  aishjp@Aish-Linux:/proc/21955$ ls
arch_status  comm                fd                 limits     mountstats     pagemap      sessionid     status          wchan
attr         coredump_filter     fdinfo             loginuid   net            patch_state  setgroups     syscall
autogroup    cpu_resctrl_groups  gid_map            map_files  ns             personality  smaps         task
auxv         cpuset              io                 maps       numa_maps      projid_map   smaps_rollup  timens_offsets
cgroup       cwd                 ksm_merging_pages  mem        oom_adj        root         stack         timers
clear_refs   environ             ksm_stat           mountinfo  oom_score      sched        stat          timerslack_ns
cmdline      exe                 latency            mounts     oom_score_adj  schedstat    statm         uid_map
  aishjp@Aish-Linux:/proc/21955$ ls fd
  0  1  2  3  4  5  6  7
  aishjp@Aish-Linux:/proc/21955$ ls -l /proc/21955/fd/{3..7}
  lrwx------ 1 aishjp aishjp 64 Aug 29 09:06 /proc/21955/fd/3 -> /home/aishjp/my-repo/file1.c
  lrwx------ 1 aishjp aishjp 64 Aug 29 09:06 /proc/21955/fd/4 -> /home/aishjp/my-repo/file2.c
  lrwx------ 1 aishjp aishjp 64 Aug 29 09:06 /proc/21955/fd/5 -> /home/aishjp/my-repo/file3.c
  lrwx------ 1 aishjp aishjp 64 Aug 29 09:06 /proc/21955/fd/6 -> /home/aishjp/my-repo/file4.c
  lrwx------ 1 aishjp aishjp 64 Aug 29 09:06 /proc/21955/fd/7 -> /home/aishjp/my-repo/file5.c
  
*/


  
