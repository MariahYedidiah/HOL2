/*Name : 21
Author : Susmita Roy
Description :21. Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 23rd Sep, 2024.
*/


#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
int main() {
    char message_received[100];
    //char * message_to_send;
    char message_to_send[100];
    int k=read(0,message_to_send,100);
// Wait for message from Program 1
    int fd_receive = open("YAHWEH", O_RDONLY);
    if (fd_receive == -1) {
        perror("open fifo_to_prog2 for reading failed");
        exit(EXIT_FAILURE);
    }
    printf("Hi,prog 2 printing my received message\n");
int l= read(fd_receive, message_received,100);
    write(1,message_received,l);
    close(fd_receive);

    // Send reply to Program 1
    int fd_send = open("EL SHADDAI", O_WRONLY);
    if (fd_send == -1) {
        perror("open fifo_to_prog1 for writing failed");
        exit(EXIT_FAILURE);
    }

   
    printf("Program 2: Sending reply to Program 1...\n");
    write(fd_send, message_to_send, k);
    close(fd_send);

    return 0;
}


