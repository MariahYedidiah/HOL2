#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

// Define semaphore operations
void sem_lock(int semid) {
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op --; // Lock
    sop.sem_flg = 0;
    semop(semid, &sop, 1);
}

void sem_unlock(int semid) {
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op = 1; // Unlock
    sop.sem_flg = 0;
    semop(semid, &sop, 1);
}

int main() {
    key_t key;
    int semid, shmid, *ticket_number;
    
    // Create a semaphore for mutual exclusion
    key = ftok(".", 777);
    semid = semget(key, 1, 777 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize the semaphore to 1
    union semun {
        int val;
    } sem_union;
    sem_union.val = 1;
    if (semctl(semid, 0, SETVAL, sem_union) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    // Create shared memory segment
    shmid = shmget(key, sizeof(int), 777 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach to shared memory
    ticket_number = (int *)shmat(shmid, NULL, 0);
    if (ticket_number == (int *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Initialize ticket number in shared memory
    *ticket_number = 0;

    // Critical section: increment the ticket number
    for (int i = 0; i < 10; i++) {
        sem_lock(semid); // Enter critical section
        (*ticket_number)++;
        printf("Ticket Number (Shared Memory): %d\n", *ticket_number);
        sem_unlock(semid); // Exit critical section
        
    }

    return 0;
}
