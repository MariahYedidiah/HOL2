// writer.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>



int main() {
    // Create a FIFO special file (named Messiah)
    if (mkfifo("Messiah", 0777) == -1) {
        perror("mkfifo failed");
        exit(EXIT_FAILURE);
    }

    // Open the FIFO for writing
    int fd = open("Messiah", O_WRONLY);
    if (fd == -1) {
        perror("Failed to open FIFO for writing");
        exit(EXIT_FAILURE);
    }

    // Write messages to FIFO
    char * message ; scanf("%s",message);
    printf("Writing to FIFO: %s\n", message);
    write(fd, message, sizeof(message));

    // Close the FIFO
    close(fd);

    return 0;
}
