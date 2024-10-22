/*Name : 1_c.c
Author : Susmita Roy
1. Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
c.ITIMER_PROF
Date: 23rd Sep, 2024.
*/

#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void signal_handler(int sig){
	printf("\nITIMER_PROF Signal Received\n");
}
int main()
{
	struct itimerval timer;
	signal(SIGPROF,signal_handler);

	timer.it_value.tv_sec=1;
	timer.it_value.tv_usec=10;
	timer.it_interval.tv_sec=1;
	timer.it_interval.tv_usec=10;

	if(setitimer(ITIMER_PROF,&timer,NULL)==-1){
		perror("Error in setting timer");
		exit(1);
	}

  for (volatile int i = 0; i < 100000000000; i++);  // Busy work to consume CPU time
for(int i=0;i<10000;i++)	 write(1,"\nJesus",7);
/*while(1){          // Simulate some system time
	pause();
     }*/
return 0;
}
/*
 output
 ITIMER_PROF Signal Received

ITIMER_PROF Signal Received

ITIMER_PROF Signal Received

ITIMER_PROF Signal Received

ITIMER_PROF Signal Received
*/
