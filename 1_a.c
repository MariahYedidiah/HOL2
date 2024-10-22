/*Name : 1_a.c
Author : Susmita Roy
1. Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
a. ITIMER_REAL
Date: 23rd Sep, 2024.
*/


#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void signal_handler(int sig){
	printf("ITIMER_REAL Signal Received\n");
}
int main()
{
	struct itimerval timer;
	signal(SIGALRM,signal_handler);

	timer.it_value.tv_sec=1;
	timer.it_value.tv_usec=10;
	timer.it_interval.tv_sec=1;
	timer.it_interval.tv_usec=10;

	if(setitimer(ITIMER_REAL,&timer,NULL)==-1){
		perror("Error in setting timer");
		exit(1);
	}
	getchar();
return 0;
}/*output
   ITIMER_REAL Signal Received
ITIMER_REAL Signal Received
ITIMER_REAL Signal Received
ITIMER_REAL Signal Received
...*/
