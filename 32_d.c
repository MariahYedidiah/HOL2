/*Name : 32d
Author : Susmita Roy
Description :Write a program to implement semaphore to protect any critical section.
d. remove the created semaphore
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key;
    int semid;

    // Generate unique key
    key = ftok(".", 777);
    
    // Get the semaphore set
    semid = semget(key, 1, 777);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Remove the semaphore set
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore removed successfully.\n");

    return 0;
}
