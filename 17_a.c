/*Name : 17_b.c
Author : Susmita Roy
17.Write a program to execute ls -l | wc.
b. use dup2
Date: 23rd Sep, 2024.
*/

#include<stdio.h>
#include<unistd.h>
int main(void)
{int fd[2];
	pipe(fd);//1 simplex pipe created for 1 | operator
	if(!fork())
	{close(1);
	close(fd[0]);
	dup(fd[1]);
	execlp("ls","ls-l",(char *)NULL);
	}
	else
	{close(0);
		close(fd[1]);
		dup(fd[0]);
		execlp("wc","wc",(char *)NULL);
	}
return 0;
}
/*output
 73      83     552
*/
