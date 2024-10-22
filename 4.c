/*Name : 4.c
Author : Susmita Roy
4. Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
Date: 23rd Sep, 2024.
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/time.h>
unsigned long long rdtsc(){
        unsigned long long dst;
        __asm__ __volatile__("rdtsc":"=A"(dst));
}
int main()
{
        int nano;
        unsigned long long int start,end;
        start=rdtsc();
        for(int i=0;i<=100;i++)
                getppid();
        end=rdtsc();
        nano=(end-start)/2.09;
        printf("The function takes %d nano sec\n",nano);

        return 0;
}

/*output
 The function takes 13253 nano sec
*/
