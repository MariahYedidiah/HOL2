/*Name : 19_d.c
Author : Susmita Roy
19. Create a FIFO file by
d. mkfifo library function
Date: 23rd Sep, 2024.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    

    // Create the FIFO using the mkfifo library function
    if (mkfifo("Christ", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    printf("FIFO created using mkfifo\n");
    return 0;
}

