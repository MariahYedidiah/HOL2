/*Name : 6.c
Author : Susmita Roy
6. Write a simple program to create three threads.
Date: 23rd Sep, 2024.
*/

#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void *myThreadFun(void *vargp)
{printf("printing Jesus...from thread\n");
	sleep(1);
	return NULL;
}
int main()
{ pthread_t tid;
	pthread_create(&tid,NULL,myThreadFun,NULL);//each thread runs a function
	pthread_create(&tid,NULL,myThreadFun,NULL);//each thread runs a function
        pthread_create(&tid,NULL,myThreadFun,NULL);
getchar();
pthread_join(tid,NULL);//not a good idea,just waits for last created thread,since threadids overwritten everytime
exit(0);
}
/*output
 printing Jesus...from thread
printing Jesus...from thread
printing Jesus...from thread
*/
