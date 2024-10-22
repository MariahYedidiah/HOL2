/*Name : 17_a.c
Author : Susmita Roy
17.Write a program to execute ls -l | wc.
a. use dup
Date: 23rd Sep, 2024.
*/

#include<stdio.h>
#include<unistd.h>

int main(void){
	int fd[2];
	pipe(fd);
	if(!fork()){
		close(fd[0]);
		dup2(fd[1],1);
		execlp("ls","ls","-l",(char *)NULL);
}
else{close(fd[1]);
	dup2(fd[0],0);
	execlp("wc","wc",(char *)NULL);
}
}
/*output
 74     669    4650
 */

