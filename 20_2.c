#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>



int main() {
    char buffer[100];

    // Open the FIFO for reading
    int fd = open("Messiah", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open FIFO for reading");
        exit(EXIT_FAILURE);
    }

    // Read message from FIFO
    int bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead > 0) {
       // buffer[bytesRead] = '\0'; // Null-terminate the string
        printf("Read from FIFO: %s\n", buffer);
    } else {
        perror("Failed to read from FIFO");
    }

    // Close the FIFO
    close(fd);

    return 0;
}
