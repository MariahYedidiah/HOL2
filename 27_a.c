/*Name : 27a
Author : Susmita Roy
Description :27. Write a program to receive messages from the message queue.
a. with 0 as a flag
Date: 23rd Sep, 2024.
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Structure for message queue

int main() {
    key_t key;
    int msgid;
    long msg_type;
    char msg_text[100];
    // Generate unique key
    key = ftok(".", 777);
    if (key == -1) {
        perror("ftok error");
        exit(EXIT_FAILURE);
    }

    // Get the message queue ID
    msgid = msgget(key, 777 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget error");
        exit(EXIT_FAILURE);
    }

    // Receive the message from the queue
    printf("Waiting for a message...\n");
    if (msgrcv(msgid, &msg_type,sizeof(msg_text), 1, 0) == -1) {  // 0 flag: blocking
        perror("msgrcv error");
        exit(EXIT_FAILURE);
    }

    // Print the received message
    printf("Received message: %s\n", msg_text);

    return 0;
}
