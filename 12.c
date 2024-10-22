/*Name : 12.c
Author : Susmita Roy
12. Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    // Create a child process
    int forkop = fork();

    if (forkop < 0) {
        // Fork failed
        perror("fork failed");
        exit(1);
    }

    if (forkop == 0) {
        // Child process
        printf("Child process: My PID is %d, Parent PID is %d\n", getpid(), getppid());
        
        // Kill the parent process using SIGKILL
        printf("Child process: Sending SIGKILL to parent process (PID: %d)\n", getppid());
        kill(getppid(), SIGKILL);

        // Sleep to demonstrate that child becomes an orphan
        sleep(5);

        printf("Child process: My new Parent PID is %d (this should be 1, i.e., 'init' or 'systemd')\n", getppid());

        // Child continues executing even after parent is killed
        printf("Child process: Orphan process exiting.\n");
    } else {
        // Parent process
        printf("Parent process: My PID is %d, Child PID is %d\n", getpid(), forkop);
        
        // Let the parent process sleep to give the child time to kill it
        sleep(10);

        printf("Parent process: This should not be printed since parent will be killed by the child.\n");
    }

    return 0;
}
/*output
 Parent process: My PID is 695394, Child PID is 695395
Child process: My PID is 695395, Parent PID is 695394
Child process: Sending SIGKILL to parent process (PID: 695394)
Killed
susmita-roy@susmita-roy-Dell-G15-5530:~/HOL2$ Child process: My new Parent PID is 1862 (this should be 1, i.e., 'init' or 'systemd')
Child process: Orphan process exiting.

*/
