/*Name : 10.c
Author : Susmita Roy
10. Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

// Signal handler for SIGSEGV (Segmentation fault)
void handle_sigsegv(int sig) {
    printf("Caught signal SIGSEGV (%d): Segmentation fault\n", sig);
    exit(1); // Exit the program
}

// Signal handler for SIGINT (Interrupt from keyboard, i.e., Ctrl+C)
void handle_sigint(int sig) {
    printf("Caught signal SIGINT (%d): Interrupt from keyboard\n", sig);
    exit(1); // Exit the program
}

// Signal handler for SIGFPE (Floating point exception)
void handle_sigfpe(int sig) {
    printf("Caught signal SIGFPE (%d): Floating point exception\n", sig);
    exit(1); // Exit the program
}

// Helper function to register signal handlers using sigaction
void register_signal(int sig, void (*handler)(int)) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;

    // Use sigaction to register the signal handler
    if (sigaction(sig, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
}

int main() {
    // Register handlers for SIGSEGV, SIGINT, and SIGFPE
    register_signal(SIGSEGV, handle_sigsegv);
    register_signal(SIGINT, handle_sigint);
    register_signal(SIGFPE, handle_sigfpe);

    printf("Signal handlers registered. Waiting for signals...\n");

    // Infinite loop to keep the program running and catch signals
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}
/*output
 Signal handlers registered. Waiting for signals...
^CCaught signal SIGINT (2): Interrupt from keyboard
*/
