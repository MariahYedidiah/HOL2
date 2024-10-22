/*Name : 5.c
Author : Susmita Roy
5. Write a program to print the system limitation of
a. maximum length of the arguments to the exec family of functions.
b. maximum number of simultaneous process per user id.
c. number of clock ticks (jiffy) per second.
d. maximum number of open files
e. size of a page
f. total number of pages in the physical memory
g. number of currently available pages in the physical memory.
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
int main()
{
	
    // a. Maximum length of the arguments to the exec family of functions
    long arg_max = sysconf(_SC_ARG_MAX);
    if (arg_max != -1) {
        printf("Maximum length of the arguments to the exec family of functions: %ld\n", arg_max);
    } else {
        perror("sysconf(_SC_ARG_MAX) failed");
    }

    // b. Maximum number of simultaneous processes per user id
    long max_procs_per_uid = sysconf(_SC_CHILD_MAX);
    if (max_procs_per_uid != -1) {
        printf("Maximum number of simultaneous processes per user ID: %ld\n", max_procs_per_uid);
    } else {
        perror("sysconf(_SC_CHILD_MAX) failed");
    }

    // c. Number of clock ticks (jiffy) per second
    long clock_ticks = sysconf(_SC_CLK_TCK);
    if (clock_ticks != -1) {
        printf("Number of clock ticks (jiffy) per second: %ld\n", clock_ticks);
    } else {
        perror("sysconf(_SC_CLK_TCK) failed");
    }

    // d. Maximum number of open files
    long max_open_files = sysconf(_SC_OPEN_MAX);
    if (max_open_files != -1) {
        printf("Maximum number of open files: %ld\n", max_open_files);
    } else {
        perror("sysconf(_SC_OPEN_MAX) failed");
    }

    // e. Size of a page
    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size != -1) {
        printf("Size of a page: %ld bytes\n", page_size);
    } else {
        perror("sysconf(_SC_PAGESIZE) failed");
    }

    // f. Total number of pages in physical memory
    long total_pages = sysconf(_SC_PHYS_PAGES);
    if (total_pages != -1) {
        printf("Total number of pages in physical memory: %ld\n", total_pages);
    } else {
        perror("sysconf(_SC_PHYS_PAGES) failed");
    }

    // g. Number of currently available pages in physical memory
    long avail_pages = sysconf(_SC_AVPHYS_PAGES);
    if (avail_pages != -1) {
        printf("Number of currently available pages in physical memory: %ld\n", avail_pages);
    } else {
        perror("sysconf(_SC_AVPHYS_PAGES) failed");
    }

	return 0;
}
/*
 * Maximum length of the arguments to the exec family of functions: 2097152
Maximum number of simultaneous processes per user ID: 62382
Number of clock ticks (jiffy) per second: 100
Maximum number of open files: 1024
Size of a page: 4096 bytes
Total number of pages in physical memory: 4011191
Number of currently available pages in physical memory: 533946
*/
