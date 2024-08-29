/***************************************************************************************************
 *Name: 30.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description: Write a program to run a script at a specific time using a Daemon process
 *Date: 29th August,2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//A daemon is a background process that typically starts at system boot and runs continuously
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

void daemonize() {
    pid_t pid;

    // Fork off the parent process to allow child to run in the background
    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    // If we got a good PID, then we can exit the parent process.
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
    
    umask(0); // full access to files created by the daemon


    // Create a new SID for the child process to detach from the controlling terminal
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    // Change the current working directory to avoid blocking file systems
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    // Close out the standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Open new file descriptors to /dev/null
    open("/dev/null", O_RDONLY);  
    open("/dev/null", O_WRONLY);  
    open("/dev/null", O_WRONLY);  
}

void run_script_at_specific_time(int target_hour, int target_minute, const char *script_path) {
    while (1) {
        time_t now = time(NULL);
        struct tm *current_time = localtime(&now);
        if (current_time->tm_hour == target_hour && current_time->tm_min == target_minute) {
            system(script_path);
            // Sleep for 60 seconds to avoid running the script multiple times within the same minute
            sleep(60);
        }
        // Sleep for 30 seconds before checking the time again
        sleep(30);
    }
}

int main() {
    char script_path[256];
    int target_hour, target_minute;
    printf("Enter the full path of the script to run: ");
    fgets(script_path, sizeof(script_path), stdin);
    // Remove newline character if present
    script_path[strcspn(script_path, "\n")] = '\0';

    printf("Enter the hour (0-23) at which to run the script: ");
    scanf("%d", &target_hour);
    printf("Enter the minute (0-59) at which to run the script: ");
    scanf("%d", &target_minute);

    // Daemonize the process
    daemonize();

    // Run the script at the specified time
    run_script_at_specific_time(target_hour, target_minute, script_path);
    return 0;
}
// for testing output a sample script addition_script which adds two numbers and displays the result is created. We check the /tmp/ directory before the script is scheduled to execute and after its execution to find an additional file present
/******************************************OUTPUT***********************************************/
/* 
  aishjp@Aish-Linux:~/my-repo$ gcc 30.c
  aishjp@Aish-Linux:~/my-repo$ ./a.out
  Enter the full path of the script to run: /home/aishjp/my-repo/addition_script.sh
  Enter the hour (0-23) at which to run the script: 15
  Enter the minute (0-59) at which to run the script: 52
  aishjp@Aish-Linux:~/my-repo$ cd ..
  aishjp@Aish-Linux:~$ cd /tmp/
  aishjp@Aish-Linux:/tmp$ ls
  snap-private-tmp
  systemd-private-936e048120f54c5a96123179949669dc-bluetooth.service-Kwq4zq
  systemd-private-936e048120f54c5a96123179949669dc-colord.service-reBsOL
  systemd-private-936e048120f54c5a96123179949669dc-fwupd.service-Xxb6ai
  systemd-private-936e048120f54c5a96123179949669dc-ModemManager.service-aaxGOp
  systemd-private-936e048120f54c5a96123179949669dc-polkit.service-PS0Vnq
  systemd-private-936e048120f54c5a96123179949669dc-power-profiles-daemon.service-wLQfw7
  systemd-private-936e048120f54c5a96123179949669dc-switcheroo-control.service-Azntat
  systemd-private-936e048120f54c5a96123179949669dc-systemd-logind.service-nxNAwW
  systemd-private-936e048120f54c5a96123179949669dc-systemd-oomd.service-gzUVtB
  systemd-private-936e048120f54c5a96123179949669dc-systemd-resolved.service-NiUb35
  systemd-private-936e048120f54c5a96123179949669dc-systemd-timesyncd.service-0jWADL
  systemd-private-936e048120f54c5a96123179949669dc-upower.service-LWFxMu
  VMwareDnD
  vmware-root_995-4257069371
  aishjp@Aish-Linux:/tmp$ ls
  addition_result.txt
  snap-private-tmp
  systemd-private-936e048120f54c5a96123179949669dc-bluetooth.service-Kwq4zq
  systemd-private-936e048120f54c5a96123179949669dc-colord.service-reBsOL
  systemd-private-936e048120f54c5a96123179949669dc-fwupd.service-Xxb6ai
  systemd-private-936e048120f54c5a96123179949669dc-ModemManager.service-aaxGOp
  systemd-private-936e048120f54c5a96123179949669dc-polkit.service-PS0Vnq
  systemd-private-936e048120f54c5a96123179949669dc-power-profiles-daemon.service-wLQfw7
  systemd-private-936e048120f54c5a96123179949669dc-switcheroo-control.service-Azntat
  systemd-private-936e048120f54c5a96123179949669dc-systemd-hostnamed.service-u96KEm
  systemd-private-936e048120f54c5a96123179949669dc-systemd-logind.service-nxNAwW
  systemd-private-936e048120f54c5a96123179949669dc-systemd-oomd.service-gzUVtB
  systemd-private-936e048120f54c5a96123179949669dc-systemd-resolved.service-NiUb35
  systemd-private-936e048120f54c5a96123179949669dc-systemd-timesyncd.service-0jWADL
  systemd-private-936e048120f54c5a96123179949669dc-upower.service-LWFxMu
  VMwareDnD
  vmware-root_995-4257069371
  aishjp@Aish-Linux:/tmp$ cat addition_result.txt
  The result of adding 10 and 20 is: 30

*/
