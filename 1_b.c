/*Name : 1_b.c
Author : Susmita Roy
1. Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
b. ITIMER_VIRTUAL
Date: 23rd Sep, 2024.
*/


#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void signal_handler(int sig){
	printf("ITIMER_VIRTUAL Signal Received\n");
}
int main()
{
	struct itimerval timer;
	signal(SIGVTALRM,signal_handler);

	timer.it_value.tv_sec=1;
	timer.it_value.tv_usec=1;
	timer.it_interval.tv_sec=1;
	timer.it_interval.tv_usec=10;

	if(setitimer(ITIMER_VIRTUAL,&timer,NULL)==-1){
		perror("Error in setting timer");
		exit(1);
	}
	while(1){
		for (volatile int i = 0; i < 1000000; i++);
	}
return 0;
}
/*output
 ITIMER_VIRTUAL Signal Received
ITIMER_VIRTUAL Signal Received
ITIMER_VIRTUAL Signal Received
ITIMER_VIRTUAL Signal Received
ITIMER_VIRTUAL Signal Received
ITIMER_VIRTUAL Signal Received
ITIMER_VIRTUAL Signal Received
*/
