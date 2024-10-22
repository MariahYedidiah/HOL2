/*Name : 13_1.c
Author : Susmita Roy
13. Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.
Date: 23rd Sep, 2024.
*/


#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void handle_signal(int sig) {
    if (sig == SIGUSR1) {
        printf("Caught SIGUSR1 signal!\n");
    } else {
        printf("Caught signal %d\n", sig);
    }
}

int main() {
    struct sigaction sa;

    // Clear the sigaction structure
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Attempt to catch SIGSTOP (which will fail)
    if (sigaction(SIGSTOP, &sa, NULL) == -1) {
        perror("sigaction - SIGSTOP");
    }

    // Setup handler for SIGUSR1, which can be caught, to show contrast
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction - SIGUSR1");
    }

    printf("Program is waiting. Try sending SIGUSR1 or SIGSTOP.\n");

    // Infinite loop to keep the program running
    while (1) {
        printf("Waiting for signals...\n");
        sleep(5);
    }

    return 0;
}
/*    The program tries to catch SIGSTOP using sigaction, but SIGSTOP cannot be caught, so this will fail.
    It can catch other signals like SIGUSR1, which you can use to compare behaviors.
    The program enters an infinite loop and waits for signals.

*/
