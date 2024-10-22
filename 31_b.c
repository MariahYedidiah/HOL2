/*Name : 31b
Author : Susmita Roy
Description :Write a program to implement semaphore to protect any critical section.
b. create a counting semaphore
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

// Function to initialize the semaphore
void initialize_semaphore(int semid, int value) {
    union semun {
        int val; // value for SETVAL
    } sem_union;

    sem_union.val = value;

    // Initialize the counting semaphore value
    if (semctl(semid, 0, SETVAL, sem_union) == -1) {
        perror("semctl");
        exit(1);
    }
}

int main() {
    key_t key;
    int semid;

    // Create a unique key
    key = ftok(".", 777);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a counting semaphore (1 semaphore)
    semid = semget(key, 1, 777 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the counting semaphore to 5 (can allow up to 5 resources)
    initialize_semaphore(semid, 5);
    printf("Counting semaphore created and initialized to 5.\n");

    return 0;
}
/*output
 sudo ./a.out
Counting semaphore created and initialized to 5.
*/
