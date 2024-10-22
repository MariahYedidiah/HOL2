/*Name : 27b
Author : Susmita Roy
Description :27. Write a program to receive messages from the message queue.
b. with IPC_NOWAIT as a flag
Date: 23rd Sep, 2024.
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

// Structure for message queue
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    long msg_type;//no need to initialize,since we are receiving
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

    // Try to receive the message using IPC_NOWAIT (non-blocking)
    printf("Trying to receive message...\n");
    if (msgrcv(msgid, &msg_type, sizeof(msg_text), 1, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            printf("No message available in the queue right now.\n");
        } else {
            perror("msgrcv error");
            exit(EXIT_FAILURE);
        }
    } else {
        // Print the received message
        printf("Received message: %s\n", msg_text);
    }

    return 0;
}
