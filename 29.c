
/*Name : 29
Author : Susmita Roy
29. Write a program to remove the message queue.
Date: 23rd Sep, 2024.
*/

 #include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;

    // Generate unique key (same as the key used to create the message queue)
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

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID error");
        exit(EXIT_FAILURE);
    }

    printf("Message queue removed successfully.\n");

    return 0;
}
