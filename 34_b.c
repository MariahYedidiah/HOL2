/*Name : 34b
Author : Susmita Roy
Description : Write a program to create a concurrent server.
b. use pthread_create
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080

void *handle_client(void *socket_desc) {
    int new_socket = *(int*)socket_desc;
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

    free(socket_desc);  // Free the allocated memory for the socket descriptor
    return NULL;
}

int main() {
    int server_fd, new_socket, *new_sock;
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

    while (1) {
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }

        // Allocate memory for the socket descriptor to pass to the thread
        new_sock = malloc(sizeof(int));
        *new_sock = new_socket;

        // Create a new thread for each client connection
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void*)new_sock) < 0) {
            perror("pthread_create failed");
            free(new_sock);
            continue;
        }

        printf("Handler assigned for client\n");
    }

    return 0;
}
