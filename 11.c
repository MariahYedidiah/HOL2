/*Name : 11.c
Author : Susmita Roy
11. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
use sigaction system call.
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    struct sigaction sa;

    // Step 1: Ignore the SIGINT signal
    sa.sa_handler = SIG_IGN;            // Set handler to ignore
    sigemptyset(&sa.sa_mask);           // Initialize sa_mask to block no signals
    sa.sa_flags = 0;                    // No special flags
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }
    
    printf("SIGINT (Ctrl+C) is now ignored. Try pressing Ctrl+C...\n");
    sleep(5);  // Wait for 5 seconds where SIGINT is ignored

    // Step 2: Reset SIGINT to default action
    sa.sa_handler = SIG_DFL;            // Set handler back to default
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("SIGINT is reset to default action. Try pressing Ctrl+C again...\n");
    
    // Infinite loop to wait for SIGINT
    while (1) {
        printf("Running... (Press Ctrl+C to exit)\n");
        sleep(2);
    }

    return 0;
}/*output

 SIGINT (Ctrl+C) is now ignored. Try pressing Ctrl+C...
^C
^CSIGINT is reset to default action. Try pressing Ctrl+C again...
Running... (Press Ctrl+C to exit)
Running... (Press Ctrl+C to exit)
^C
*/
