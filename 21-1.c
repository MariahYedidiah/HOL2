/*Name : 21
Author : Susmita Roy
Description :21. Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    // Create both FIFOs
    if (mkfifo("YAHWEH", 0777) == -1) {
        perror("mkfifo fifo_to_prog2 failed");
        exit(EXIT_FAILURE);
    }
    if (mkfifo("EL SHADDAI", 0777) == -1) {
        perror("mkfifo fifo_to_prog1 failed");
        exit(EXIT_FAILURE);
    }
//    char * message_to_send;
    char  message_to_send[100];
int k=read(0,message_to_send,100);
    char message_received[100];
int fd_send = open("YAHWEH", O_WRONLY);
    if (fd_send == -1) {
        perror("open fifo_to_prog2 for writing failed");
        exit(EXIT_FAILURE);
	}
	printf("Program 1: Sending message to Program 2...\n");

write(fd_send, message_to_send, k);
close(fd_send);

 int fd_receive = open("EL SHADDAI", O_RDONLY);
    if (fd_receive == -1) {
        perror("open fifo_to_prog1 for reading failed");
        exit(EXIT_FAILURE);
    }
printf("Hi,prog 1 printing my received message\n");

int l=read(fd_receive, message_received,100);
    write(1, message_received,l);
    close(fd_receive);

return 0;
    }
