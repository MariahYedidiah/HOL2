/*Name : 32b
Author : Susmita Roy
Description :Write a program to implement semaphore to protect any critical section.

b. protect shared memory from concurrent write access
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

// Define semaphore operations (P and V)
void sem_lock(int semid) {
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op--; // Wait (P operation)
    sop.sem_flg = 0;
    semop(semid, &sop, 1);
}

void sem_unlock(int semid) {
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op = 1; // Signal (V operation)
    sop.sem_flg = 0;
    semop(semid, &sop, 1);
}

int main() {
    key_t key;
    int shmid, semid;
    int *shared_data;
    
    
    // Create a unique key for semaphore and shared memory
    key = ftok(".", 777);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create shared memory segment
    shmid = shmget(key, sizeof(int), 777 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to shared memory
    shared_data = (int *)shmat(shmid, NULL, 0);
    if (shared_data == (int *)-1) {
        perror("shmat");
        exit(1);
    }
    *shared_data=1;

    // Create a semaphore for synchronizing access
    semid = semget(key, 1, 777 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the semaphore to 1 (binary semaphore)
    union semun {
        int val;
    } sem_union;
    sem_union.val = 1;
    if (semctl(semid, 0, SETVAL, sem_union) == -1) {
        perror("semctl");
        exit(1);
    }

    // Simulate writing to shared memory (critical section)
    for (int i = 0; i < 5; i++) {
        sem_lock(semid); // Lock semaphore (enter critical section)

        // Write to shared memory
        (*shared_data)++;
        printf("Process %d wrote: %d\n", getpid(), *shared_data);
        
        sem_unlock(semid); // Unlock semaphore (exit critical section)

        sleep(1); // Simulate some work
    }

    // Detach from shared memory
    shmdt(shared_data);

    return 0;
}
