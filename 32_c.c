/*Name : 32b
Author : Susmita Roy
Description :Write a program to implement semaphore to protect any critical section.
b.protect shared memory from concurrent write access
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

// Define semaphore operations
void sem_wait(int semid) {
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op--; // Wait (P operation)
    sop.sem_flg = 0;
    semop(semid, &sop, 1);
}

void sem_signal(int semid) {
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op = 1; // Signal (V operation)
    sop.sem_flg = 0;
    semop(semid, &sop, 1);
}

int main() {
    key_t key;
    int semid;
    
    // Create a counting semaphore for managing 2 resources
    key = ftok(".", 777);
    semid = semget(key, 1, 777 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize the counting semaphore to 2 (2 resources available)
    union semun {
        int val;
    } sem_union;
    sem_union.val = 2; // 2 pseudo-resources
    if (semctl(semid, 0, SETVAL, sem_union) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    // Simulate using the resources
    for (int i = 0; i < 5; i++) {
        sem_wait(semid); // Request a resource
        printf("Process %d is using a resource.\n", getpid());
        sleep(2); // Simulate work
        printf("Process %d released a resource.\n", getpid());
        sem_signal(semid); // Release the resource
        
    }

    return 0;
}

