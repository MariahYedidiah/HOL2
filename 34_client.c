#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char *hello = "Hello from client";

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
//serv_addr.sin_addr.s_addr = INADDR_ANY;
    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) { // Replace "127.0.0.1" with the server's IP,replacing by INADDR_ANY does'nt work
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Send a message to the server
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent to server\n");

    // Read the server's response
    read(sock, buffer, 1024);
    printf("Message from server: %s\n", buffer);

    // Close the socket
    close(sock);

    return 0;
}

