/*Name : 34 a
Author : Susmita Roy
Description : Write a program to create a concurrent server.
a. use fork
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT 8080

void handle_client(int new_socket) {
    char buffer[1024] = {0};
    char *message = "Hello from server";
    
    // Read message from client
    read(new_socket, buffer, 1024);
    printf("Message from client: %s\n", buffer);

    // Send response to the client
    send(new_socket, message, strlen(message), 0);
    printf("Message sent to client\n");

    // Close socket after communication
    close(new_socket);
}

void sigchld_handler(int signo) {
    // Handle child termination
    wait(NULL);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set up the address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    // Handle SIGCHLD signal to clean up terminated child processes
    signal(SIGCHLD, sigchld_handler);

    while (1) {
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }

        // Create a new process for each client connection
        if (fork() == 0) {
            // In child process: handle the client
            close(server_fd);  // Close the listening socket in the child process
            handle_client(new_socket);
            exit(0);  // Terminate the child process after handling the client
        } else {
            // In parent process: close the client socket and continue accepting more connections
            close(new_socket);
        }
    }

    return 0;
}
