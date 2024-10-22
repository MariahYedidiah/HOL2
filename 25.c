/*Name : 25
Author : Susmita Roy
Description :25. Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds buf;

    // Generate a unique key
    key = ftok(".", 777);  // Ensure progfile exists or create one using 'touch progfile'
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create or get the message queue
    msgid = msgget(key, 777 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Get the status of the message queue
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    // a. Access permission
    printf("Access Permissions: %o\n", buf.msg_perm.mode);

    // b. UID and GID
    printf("UID: %u\n", buf.msg_perm.uid);
    printf("GID: %u\n", buf.msg_perm.gid);

    // c. Time of last message sent and received
    printf("Time of last message sent: %s", ctime(&buf.msg_stime));
    printf("Time of last message received: %s", ctime(&buf.msg_rtime));

    // d. Time of last change in the message queue
    printf("Time of last change: %s", ctime(&buf.msg_ctime));

    // e. Size of the queue (in bytes)
    printf("Current number of bytes in the queue: %lu\n", buf.__msg_cbytes);

    // f. Number of messages in the queue
    printf("Number of messages in the queue: %lu\n", buf.msg_qnum);

    // g. Maximum number of bytes allowed in the queue
    printf("Maximum number of bytes allowed: %lu\n", buf.msg_qbytes);

    // h. PID of last msgsnd and msgrcv
    printf("PID of last msgsnd: %d\n", buf.msg_lspid);
    printf("PID of last msgrcv: %d\n", buf.msg_lrpid);

    return 0;
}
/*output
 sudo ./a.out
Access Permissions: 411
UID: 1000
GID: 1000
Time of last message sent: Mon Sep 23 21:51:09 2024
Time of last message received: Thu Jan  1 05:30:00 1970
Time of last change: Mon Sep 23 21:39:17 2024
Current number of bytes in the queue: 13
Number of messages in the queue: 1
Maximum number of bytes allowed: 16384
PID of last msgsnd: 687845
PID of last msgrcv: 0
*/
