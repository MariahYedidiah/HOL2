/*Name : 22
Author : Susmita Roy
Description :22. Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include<sys/select.h>
#define FIFO_NAME "YESHUA"
int main() {
    int fifo_fd;
    char buffer[100];
    fd_set write_fds;
    struct timeval timeout;
    if (mkfifo(FIFO_NAME, 0777) == -1 && errno != EEXIST) {
        perror("error in mkfifo");
        exit(EXIT_FAILURE);
    }

    // Open the FIFO for reading
    fifo_fd = open("YESHUA", O_RDWR | O_NONBLOCK);  // Non-blocking mode
    if (fifo_fd == -1) {
        perror("error opening fifo");
        exit(EXIT_FAILURE);
    }

    // Initialize the file descriptor set
    FD_ZERO(&write_fds);
    FD_SET(fifo_fd, &write_fds);

    // Set the timeout to 30 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for data to be written on FIFO for %ld seconds...\n", timeout.tv_sec);

    // Use select to wait for data to be available for reading on FIFO
    int result = select(fifo_fd + 1, NULL,&write_fds, NULL, &timeout);
printf("result is d\n",result);

    if (result == -1) {
        perror("select has error");
        close(fifo_fd);
        exit(EXIT_FAILURE);
    } else if (result == 0) {
        printf("No data within %ld seconds.\n", timeout.tv_sec);
    } else {int k=read(0,buffer,sizeof(buffer)-1);
        if (FD_ISSET(fifo_fd, &write_fds)) {
            // Data is available to read from the FIFO
            write(fifo_fd, buffer, k);
          /*  if (bytes_read > 0) {
                buffer[bytes_read] = '\0';  // Null-terminate the string
                printf("Read from FIFO: %s\n", buffer);
            } else if (bytes_read == 0) {
                printf("EOF: No more data in FIFO.\n");
            } else {
                perror("read");
            }*/
        }
	
    // Clean up
    close(fifo_fd);
    }
//    unlink(FIFO_NAME);  // Remove the FIFO

    return 0;
}
