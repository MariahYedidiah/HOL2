/*Name : 15.c
Author : Susmita Roy
15. Write a simple program to send some data from parent to the child process.
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>
int main() {
    int pipefd[2];        // Array to hold the two ends of the pipe
    int forkop;            // Process ID
    char write_msg[] = "\nJESUS is God of the whole world\n";
    char read_msg[100];   // Buffer to store the message read from the pipe

    // Create a pipe, pipefd[0] is for reading, pipefd[1] is for writing
    if (pipe(pipefd) == -1) {
        perror("pipe creation\n");
        exit(EXIT_FAILURE);
    }

    // Fork the process to create a child
    forkop = fork();

    if (forkop < 0) {
        perror("unsuccessful fork");
        exit(EXIT_FAILURE);
    }

    if (forkop > 0) {  // Parent process
        // Close the read end of the pipe
        
	 close(pipefd[0]);
	write(1,"\nim parent\n",11);
        // Write a message to the pipe
        write(pipefd[1], write_msg, strlen(write_msg)+1 ); // +1 to include the null terminator
        close(pipefd[1]);  // Close the write end after writing

wait(0);//ensures sequential execution of parent and child threads
printf("\nparent exitting\n");

    } else {        // Child process
        // Close the write end of the pipe
        sleep(7);
	    close(pipefd[1]);

	write(1,"\nim child",10);
        // Read the message from the pipe
        read(pipefd[0], read_msg, sizeof(read_msg));

        // Display the message on the monitor
        printf("\nMessage from parent for child  process: %s\n", read_msg);

        // Close the read end after reading
        close(pipefd[0]);
	printf("\nchild exitting\n");
    }

    return 0;
}
/*output
 im parent

im child
Message from parent for child  process: 
JESUS is God of the whole world


child exitting

parent exitting
*/
