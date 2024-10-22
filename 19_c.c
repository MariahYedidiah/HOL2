/*Name : 19_c.c
Author : Susmita Roy
19. Create a FIFO file by
c. mknod system call
d. mkfifo library function
Date: 23rd Sep, 2024.
*/


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    

    // Create the FIFO using mknod system call
    if (mknod("Emmanuel", S_IFIFO| 0666, 0) == -1) {
        perror("mknod");
        return 1;
    }

    printf("FIFO created using mknod\n");
    return 0;
}
