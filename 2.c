/***************************************************************************************************
 *Name: 2.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a simple program to execute in an infinite loop at the background. Go to /proc directory and identify all the process related information in the corresponding proc directory.
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
int main()
{
  while (1) {
    //simple infinite loop 
    }
    return 0;
}
// output with "./a.out & " to get pid then cd to home, cd to /proc/pid to reach process then ls
// run ps aux | grep hop2.c to see the pid of process... ls /proc/pid to list process

/******************************************OUTPUT************************************************/
/*
  aishjp@Aish-Linux:~/my-repo$ gcc 2.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out &
  [1] 20972
  
  aishjp@Aish-Linux:~/my-repo$ cd /proc/20972
  aishjp@Aish-Linux:/proc/20972$ ls
  arch_status  comm                fd                 limits     mountstats     pagemap      sessionid     status          wchan
attr         coredump_filter     fdinfo             loginuid   net            patch_state  setgroups     syscall
autogroup    cpu_resctrl_groups  gid_map            map_files  ns             personality  smaps         task
auxv         cpuset              io                 maps       numa_maps      projid_map   smaps_rollup  timens_offsets
cgroup       cwd                 ksm_merging_pages  mem        oom_adj        root         stack         timers
clear_refs   environ             ksm_stat           mountinfo  oom_score      sched        stat          timerslack_ns
cmdline      exe                 latency            mounts     oom_score_adj  schedstat    statm         uid_map

*/

