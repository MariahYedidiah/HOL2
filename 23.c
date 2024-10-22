/*Name : 23
Author : Susmita Roy
Description :23. Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    // Get the maximum number of open files
    long max_files = sysconf(_SC_OPEN_MAX);
    if (max_files == -1) {
        perror("sysconf");
        return 1;
    }

    // Get the size of a pipe (circular buffer)
    long pipe_size = fpathconf(0, _PC_PIPE_BUF);
    if (pipe_size == -1) {
        perror("fpathconf");
        return 1;
    }

    printf("Maximum number of open files: %ld\n", max_files);
    printf("Size of a pipe (circular buffer): %ld bytes\n", pipe_size);

    return 0;
}
