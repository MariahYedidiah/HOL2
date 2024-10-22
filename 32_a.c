
/*Name : 32a
Author : Susmita Roy
Description :Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
Date: 23rd Sep, 2024.
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>

// Define semaphore operations
void sem_lock(int semid) {
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op --; // Lock (P operation)
    sop.sem_flg = 0;
    semop(semid, &sop, 1);
}

void sem_unlock(int semid) {
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op =1; // Unlock (V operation)
    sop.sem_flg = 0;
    semop(semid, &sop, 1);
}

int main() {
    int db;
    int fd;
    key_t key;
    int semid;
    
    // Generate a unique key for the semaphore
    key = ftok(".", 777);  // Ensure "progfile" exists or create it using 'touch progfile'
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create or get the semaphore set with 1 semaphore (binary semaphore)
    semid = semget(key, 1, 777 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the semaphore to 1 (only once, assuming no other init done)
    union semun {
        int val;
    } sem_union;
    
    sem_union.val = 1; // Set the binary semaphore to 1 (available)
    if (semctl(semid, 0, SETVAL, sem_union) == -1) {
        perror("semctl");
        exit(1);
    }

    // Open the file for reading and writing
    fd = open("dbfile", O_RDWR);
    if (fd == -1) {
        printf("Error opening file\n");
        exit(1);
    }

    // Read the current ticket number from the file
    read(fd, &db, sizeof(db));
    
    // Before entering the critical section
    printf("Before entering critical section\n");

    // Lock the semaphore (enter critical section)
    sem_lock(semid);
    
    // Inside critical section
    printf("Inside critical section\n");
    printf("Current ticket no: %d\n", db);
    
    // Increment the ticket number
    db++;
    
    // Move the file pointer to the start and write the new ticket number
    lseek(fd, 0, SEEK_SET);
    write(fd, &db, sizeof(db));

    // Wait for user input to unlock
    printf("Press Enter to unlock\n");
    getchar();

    // Unlock the semaphore (exit critical section)
    sem_unlock(semid);

    // Close the file
    close(fd);
    printf("Unlocked\n");

    return 0;
}
/*output
 
  sudo ./a.out
[sudo] password for susmita-roy:
Before entering critical section
Inside critical section
Current ticket no: 16
Press Enter to unlock

Unlocked
*/
