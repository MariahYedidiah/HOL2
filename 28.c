/*Name : 28
Author : Susmita Roy
28. Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 23rd Sep, 2024.
*/


#includie <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>

// Function to print current permissions
void print_permissions(struct msqid_ds msg_queue_ds) {
    printf("Current Permissions: %o\n", msg_queue_ds.msg_perm.mode & 0777);
}

int main() {
    key_t key;
    int msgid;
    struct msqid_ds msg_queue_ds;

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

    // Retrieve the current permissions using IPC_STAT
    if (msgctl(msgid, IPC_STAT, &msg_queue_ds) == -1) {
        perror("msgctl IPC_STAT error");
        exit(EXIT_FAILURE);
    }

    // Print the current permissions
    printf("Before permission change:\n");
    print_permissions(msg_queue_ds);

    // Change the permissions (e.g., change to 0600 for read/write by owner only)
    msg_queue_ds.msg_perm.mode = 0500;

    // Apply the new permissions using IPC_SET
    if (msgctl(msgid, IPC_SET, &msg_queue_ds) == -1) {
        perror("msgctl IPC_SET error");
        exit(EXIT_FAILURE);
    }

    // Retrieve and print the new permissions to verify the change
    if (msgctl(msgid, IPC_STAT, &msg_queue_ds) == -1) {
        perror("msgctl IPC_STAT error after change");
        exit(EXIT_FAILURE);
    }

    printf("After permission change:\n");
    print_permissions(msg_queue_ds);

    return 0;
}

/*
 output
susmita-roy@susmita-roy-Dell-G15-5530:~/HOL2$ cc 28.c
susmita-roy@susmita-roy-Dell-G15-5530:~/HOL2$ ./a.out
Before permission change:
Current Permissions: 777
After permission change:
Current Permissions: 600
susmita-roy@susmita-roy-Dell-G15-5530:~/HOL2$ vi 28.c
susmita-roy@susmita-roy-Dell-G15-5530:~/HOL2$ cc 28.c
susmita-roy@susmita-roy-Dell-G15-5530:~/HOL2$ ./a.out
msgget error: Permission denied
susmita-roy@susmita-roy-Dell-G15-5530:~/HOL2$ sudo ./a.out
[sudo] password for susmita-roy: 
Before permission change:
Current Permissions: 600
After permission change:
Current Permissions: 500
*/
