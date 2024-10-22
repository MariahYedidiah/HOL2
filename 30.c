/*Name : 30.c
Date: 23rd Sep, 2024.

 Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
Date: 23rd Sep, 2024.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of shared memory

int main() {
    key_t key;
    int shmid;
    char *data;

    // Generate a unique key for shared memory
    key = ftok(".", 777);
    if (key == -1) {
        perror("ftok error");
        exit(EXIT_FAILURE);
    }

    // Part (a): Create shared memory
    shmid = shmget(key, SHM_SIZE, 777 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget error");
        exit(EXIT_FAILURE);
    }

    // Attach to shared memory and write some data
    data = (char *)shmat(shmid, (void *)0, 0);  // Attach with read/write permissions
    if (data == (char *)-1) {
        perror("shmat error");
        exit(EXIT_FAILURE);
    }

    printf("Writing data to shared memory...\n");
    strcpy(data, "Hello from shared memory!");

    // Print the written data
    printf("Data written: %s\n", data);

    // Part (b): Attach to shared memory with O_RDONLY and check if we can overwrite
    printf("\nAttaching with O_RDONLY...\n");
    char *read_only_data = (char *)shmat(shmid, (void *)0, SHM_RDONLY);  // Attach with read-only permissions
    if (read_only_data == (char *)-1) {
        perror("shmat error");
        exit(EXIT_FAILURE);
    }

    printf("Data from read-only shared memory: %s\n", read_only_data);

//    printf("Attempting to overwrite the data...\n");
    // Try to overwrite the data in read-only mode (this should fail)
  //  strcpy(read_only_data, "New data");  // This will cause a segmentation fault if executed

    // Detach the read-only shared memory
    if (shmdt(read_only_data) == -1) {
        perror("shmdt error");
        exit(EXIT_FAILURE);
    }

    // Part (c): Detach from shared memory (read/write)
    printf("Detaching from shared memory...\n");
    if (shmdt(data) == -1) {
        perror("shmdt error");
        exit(EXIT_FAILURE);
    }

    // Part (d): Remove shared memory
    printf("Removing shared memory...\n");
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl error");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory removed successfully.\n");

    return 0;
}
/*output
 sudo ./a.out
Writing data to shared memory...
Data written: Hello from shared memory!

Attaching with O_RDONLY...
Data from read-only shared memory: Hello from shared memory!
Detaching from shared memory...
Removing shared memory...
Shared memory removed successfully.
*/
