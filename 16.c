/*Name : 16.c
Author : Susmita Roy
16. Write a program to send and receive data from parent to child vice versa. Use two way
communication.
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    int pipe1[2]; // Parent to Child
    int pipe2[2]; // Child to Parent
    pid_t forkop;

    // Create pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe creation failure");
        exit(EXIT_FAILURE);
    }

    forkop = fork(); // Create child process

    if (forkop < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (forkop > 0) { // Parent process
        close(pipe1[0]); // Close unused read end of pipe1
        close(pipe2[1]); // Close unused write end of pipe2

        char *message = "Hello from Parent";
        write(pipe1[1], message, strlen(message) + 1); // Send message to child

        char buffer[BUFFER_SIZE];
        read(pipe2[0], buffer, BUFFER_SIZE); // Read message from child
        printf("Parent received: %s\n", buffer);

        close(pipe1[1]);
        close(pipe2[0]);
    } else { // Child process
        close(pipe1[1]); // Close unused write end of pipe1
        close(pipe2[0]); // Close unused read end of pipe2

        char buffer[BUFFER_SIZE];
        read(pipe1[0], buffer, BUFFER_SIZE); // Read message from parent
        printf("Child received: %s\n", buffer);

        char *response = "Hello from Child";
        write(pipe2[1], response, strlen(response) + 1); // Send response to parent

        close(pipe1[0]);
        close(pipe2[1]);
    }

    return 0;

}







/*Ordering does'nt matter
 * When we say that read and write are blocking calls, it means that the execution of a program will pause (block) and wait until the requested operation is completed. This is important in inter-process communication (like pipes or sockets), file I/O, and other system operations.
Blocking Behavior:

    read Call:
        The read call is blocking when it waits for data to be available. If there's no data to read (for example, if the pipe or file is empty), the read call will block the program until some data becomes available. This means the program will not continue executing until read receives some data or the pipe/file is closed.
        Example: In a pipe, if the parent tries to read from the pipe but the child hasn't written anything yet, the read call in the parent will block until the child writes data.

    write Call:
        The write call can block if the output buffer (for example, in a pipe or socket) is full. The system cannot accept more data to write until the buffer is flushed (i.e., some data has been read or transmitted).
        Example: If the child tries to write a large amount of data to the pipe, and the parent hasn't read from the pipe yet, the pipe's buffer may fill up. The child’s write call will then block until the parent reads some data, making room in the pipe’s buffer.*/

