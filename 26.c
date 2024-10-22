/*Name : 26
Author : Susmita Roy
Description :26.Write a program to send messages to the message queue. Check $ipcs -q
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include<unistd.h>
// Structure for message queue


int main() {
    key_t key;
    int msgid;
    long msg_type=1;
    char msg_text[100];

    // Generate a unique key
    key = ftok(".", 777);  // "progfile" should exist, use a unique identifier
    if (key == -1) {
        perror("ftok error");
        exit(EXIT_FAILURE);
    }

    // Create a message queue and return the identifier
    msgid = msgget(key,777 | IPC_CREAT);  // 0666: Read/write permission
    if (msgid == -1) {
        perror("msgget error");
        exit(EXIT_FAILURE);
    }

    // Input message to send
    printf("Enter the message: ");
    int k=read(0,msg_text,100);

    // Message type (usually positive)
    msg_type = 1;

    // Send message to the queue
    if (msgsnd(msgid, &msg_type,k,0)==-1){
        perror("msgsnd error");
        exit(EXIT_FAILURE);
    }

    printf("Message sent: %s\n", msg_text);

    return 0;
}
/*sudo ./a.out
[sudo] password for susmita-roy: 
Jesus is God
Enter the message: Message sent: Jesus is God

susmita-roy@susmita-roy-Dell-G15-5530:~/HOL2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x09080036 1          susmita-ro 411        13           1 
*/
