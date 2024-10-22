/*Name : 1_a.c
Author : Susmita Roy
2. Write a program to print the system resource limits. Use getrlimit system call.
Date: 23rd Sep, 2024.
*/

#include<stdio.h>
#include <sys/resource.h>
#include <stdlib.h>
int main()
{

	struct rlimit limit;
int k=getrlimit(RLIMIT_CORE,&limit);
if(k==0){
 printf("%ld ",limit.rlim_cur);
  printf("%ld \n",limit.rlim_max);
}

k=getrlimit(RLIMIT_CPU,&limit);
if(k==0){
 printf("%ld ",limit.rlim_cur);
  printf("%ld \n",limit.rlim_max);
}
k=getrlimit(RLIMIT_DATA,&limit);
if(k==0){
 printf("%ld ",limit.rlim_cur);
  printf("%ld \n",limit.rlim_max);
}
k=getrlimit(RLIMIT_FSIZE,&limit);
if(k==0){
 printf("%ld ",limit.rlim_cur);
  printf("%ld \n",limit.rlim_max);
}
 k=getrlimit(RLIMIT_NOFILE,&limit);
if(k==0){
 printf("%ld ",limit.rlim_cur);
  printf("%ld \n",limit.rlim_max);
}
k=getrlimit(RLIMIT_STACK,&limit);
if(k==0){
 printf("%ld ",limit.rlim_cur);
  printf("%ld \n",limit.rlim_max);
}
k=getrlimit(RLIMIT_AS,&limit);
if(k==0){
 printf("%ld ",limit.rlim_cur);
  printf("%ld \n",limit.rlim_max);
}




	return 0;
}
/*
 OUTPUT

 0 -1
-1 -1
-1 -1
-1 -1
1024 1048576
8388608 -1
-1 -1

*/
