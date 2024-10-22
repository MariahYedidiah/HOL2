/*Name : 31a
Author : Susmita Roy
Description :Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

// Function to initialize the semaphore
void initialize_semaphore(int semid, int value) {
    // sembuf structure: used for semaphore operations
    struct sembuf sop;
    sop.sem_num = 0;  // semaphore number, here we use only one semaphore (binary)
    sop.sem_op = value; // set the value
    sop.sem_flg = 0;

    // Initialize the semaphore value
    if (semop(semid, &sop, 1) == -1) {
        perror("semop");
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

    // Create a binary semaphore (1 semaphore)
    semid = semget(key, 1, 777 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the binary semaphore to 1 (open state)
    initialize_semaphore(semid, 1);
    printf("Binary semaphore created and initialized to 1.\n");

    return 0;
}
/*output
 sudo ./a.out
Binary semaphore created and initialized to 1.
*/
