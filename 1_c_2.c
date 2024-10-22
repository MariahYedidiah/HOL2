#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGPROF
void handle_sigprof(int signum) {
    printf("Received SIGPROF: Profiling timer expired\n");
}

int main() {
    struct itimerval timer;

    // Set up the signal handler for SIGPROF
    signal(SIGPROF, handle_sigprof);

    // Set the timer interval to 10 seconds and 10 microseconds
    timer.it_interval.tv_sec = 1;       // Interval of 10 seconds
    timer.it_interval.tv_usec = 10;      // Interval of 10 microseconds
    timer.it_value.tv_sec = 1;          // Initial expiration after 10 seconds
    timer.it_value.tv_usec = 10;         // Initial expiration after 10 microseconds

    // Start the timer with ITIMER_PROF (profiling timer)
    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("Error setting timer");
        exit(EXIT_FAILURE);
    }

    // Simulate some work in the process
    while (1) {
        for (volatile int i = 0; i < 10; i++);  // Busy work to consume CPU time
        sleep(1);  // Simulate some system time
    }

    return 0;
}
