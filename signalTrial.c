#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
void my_handler(int sig);/*function prototype*/
int main(void){
	signal(SIGINT,my_handler);//can do this for all signals,not just SIGINT, except for 2 SIGKILL and
				  // SIGSTOP,no.s -4 and 19,respectively
				  //SIGINT =ctrl +c 
	printf("Catching SIGINT\n");
	sleep(3);
	printf("No SIGINT within 3 secs\n");
   signal(SIGINT ,SIG_IGN);//SIG_IGN ignores the signal
   printf("Ignoring SIGINT\n");
   sleep(3);
   printf("No SIGINT within 3 secs\n");
   signal(SIGINT,SIG_DFL);//SIG_DFL sets default action of the signal
   printf("Default action for SIGINT\n");
   sleep(3);
   printf("No SIGINT within 3 secs\n");
   return 0;
}
void my_handler(int sig){
	printf("I got SIGINT ,number %d\n",sig);
	exit(0);
}
