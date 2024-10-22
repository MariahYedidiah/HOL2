/*Name : 13_2.c
Author : Susmita Roy
13. Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include<unistd.h>
int main() {
    pid_t target_pid;

    // Ask the user for the PID of the first program
    printf("Enter the PID of the target process: ");
    scanf("%d", &target_pid);

    // Send the SIGSTOP signal to the target process
    if (kill(target_pid, SIGSTOP) == -1) {
        perror("kill - failed to send SIGSTOP to target process");
        return 1;
    }

    printf("Sent SIGSTOP to process %d\n", target_pid);

    // Wait for a few seconds and send SIGCONT to resume the process
    sleep(12);

    if (kill(target_pid, SIGCONT) == -1) {
        perror("kill - SIGCONT failed to resume");
        return 1;
    }

    printf("Sent SIGCONT to resume process %d\n", target_pid);

    return 0;
}
