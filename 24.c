/*Name : 24
Author : Susmita Roy
Description :24. Write a program to create a message queue and print the key and message queue id.
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;

    // Generate a unique key using ftok
    key = ftok(".", 777);  // "progfile" is a file used to generate the key, and 65 is a project identifier.
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a message queue or get an existing one with read/write permissions for the owner
    msgid = msgget(key, 0777 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Print the key and message queue ID
    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

