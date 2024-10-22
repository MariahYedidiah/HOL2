/*Name : 9.c
Author : Susmita Roy
9. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Custom signal handler for SIGINT
void signal_handler(int sig) {
    printf("SIGINT signal (Ctrl+C) ignored!\n");
}

int main() {
    // Step 1: Set the SIGINT handler to our custom signal handler
    signal(SIGINT, signal_handler);

    printf("SIGINT is now ignored. Press Ctrl+C...\n");
    sleep(10);  // Wait 10 seconds to give the user a chance to press Ctrl+C

    // Step 2: Reset SIGINT to its default action (terminate the process)
    signal(SIGINT, SIG_DFL);
    printf("SIGINT is now reset to default. Press Ctrl+C again to terminate the program...\n");

    sleep(10);  // Wait another 10 seconds for the user to press Ctrl+C again

    printf("Program exiting normally.\n");
    return 0;
}
/*output
 SIGINT is now ignored. Press Ctrl+C...
^CSIGINT signal (Ctrl+C) ignored!
SIGINT is now reset to default. Press Ctrl+C again to terminate the program...
^C
*/
