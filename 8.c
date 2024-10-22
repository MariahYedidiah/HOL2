/*Name : 8.c
Author : Susmita Roy
8. Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
d. SIGALRM (use alarm system call)
e. SIGALRM (use setitimer system call)
f. SIGVTALRM (use setitimer system call)
g. SIGPROF (use setitimer system call)
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

// Signal Handlers
void handle_sigsegv(int sig) {
    printf("Caught SIGSEGV (Segmentation Fault)\n");
    exit(1);
}

void handle_sigint(int sig) {
    printf("Caught SIGINT (Interrupt Signal - Ctrl+C)\n");
    exit(0);
}

void handle_sigfpe(int sig) {
    printf("Caught SIGFPE (Floating Point Exception)\n");
    exit(1);
}

void handle_sigalrm(int sig) {
    printf("Caught SIGALRM (Alarm Signal)\n");
}

void handle_sigvtalrm(int sig) {
    printf("Caught SIGVTALRM (Virtual Timer Signal)\n");
}

void handle_sigprof(int sig) {
    printf("Caught SIGPROF (Profiling Timer Signal)\n");
}

// Function to generate SIGFPE (Floating Point Exception)
void generate_sigfpe() {
    int x = 1 / 0;  // Causes divide by zero exception
}

// Function to generate SIGSEGV (Segmentation Fault)
void generate_sigsegv() {
    int *p = NULL;
    *p = 42;  // Causes segmentation fault
}

int main() {
    // Register signal handlers
    signal(SIGSEGV, handle_sigsegv);   // Catch segmentation fault
    signal(SIGINT, handle_sigint);     // Catch interrupt signal (Ctrl+C)
    signal(SIGFPE, handle_sigfpe);     // Catch floating point exception
    signal(SIGALRM, handle_sigalrm);   // Catch alarm signal
    signal(SIGVTALRM, handle_sigvtalrm); // Catch virtual timer alarm
    signal(SIGPROF, handle_sigprof);   // Catch profiling timer alarm

    // Setting SIGALRM using alarm()
    alarm(3);  // Sends SIGALRM after 3 seconds

    // Setting SIGALRM using setitimer()
    struct itimerval timer_real;
    timer_real.it_value.tv_sec = 5;    // Initial value of timer after which it expires
    timer_real.it_value.tv_usec = 0;
    timer_real.it_interval.tv_sec = 2; // Interval after first expiration after which it repeats
    timer_real.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer_real, NULL);  // Sends SIGALRM on expiration

    // Setting SIGVTALRM using setitimer()
    struct itimerval timer_virtual;
    timer_virtual.it_value.tv_sec = 7;     
    timer_virtual.it_value.tv_usec = 0;
    timer_virtual.it_interval.tv_sec = 3;  
    timer_virtual.it_interval.tv_usec = 0;
    setitimer(ITIMER_VIRTUAL, &timer_virtual, NULL);  // Sends SIGVTALRM on expiration

    // Setting SIGPROF using setitimer()
    struct itimerval timer_prof;
    timer_prof.it_value.tv_sec = 10;     // First expiration after 10 seconds
    timer_prof.it_value.tv_usec = 0;
    timer_prof.it_interval.tv_sec = 4;   // Repeats every 4 seconds
    timer_prof.it_interval.tv_usec = 0;
    setitimer(ITIMER_PROF, &timer_prof, NULL);  // Sends SIGPROF on expiration

    // Uncomment the lines below to trigger signals for testing
    // generate_sigfpe();  // Uncomment to generate SIGFPE
//     generate_sigsegv(); // Uncomment to generate SIGSEGV

    // Infinite loop to keep the program running, allowing signals to be caught
    while (1) {
        pause();  // Wait for signals
    }

    return 0;
}
/*output
 Caught SIGALRM (Alarm Signal)
Caught SIGALRM (Alarm Signal)
Caught SIGALRM (Alarm Signal)
Caught SIGALRM (Alarm Signal)
Caught SIGALRM (Alarm Signal)
^CCaught SIGINT (Interrupt Signal - Ctrl+C)
*/
