/*Name : 7.c
Author : Susmita Roy
7. Write a simple program to print the created thread ids.
Date: 23rd Sep, 2024.
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* print_thread_id(void* arg) {
    printf("Thread ID: %lu\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[3];

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, print_thread_id, NULL);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);  // Wait for all threads to finish
    }

    return 0;
}
/*output
 Thread ID: 140633748526784
Thread ID: 140633765312192
Thread ID: 140633756919488
*/
