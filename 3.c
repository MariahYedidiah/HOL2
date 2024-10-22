/*Name : 3.c
Author : Susmita Roy
3.Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 23rd Sep, 2024.
*/

#include<stdio.h>
#include <sys/resource.h>
#include <stdlib.h>
int main()
{

        struct rlimit limit;
limit.rlim_cur=1024;
limit.rlim_max=2048;
int k=setrlimit(RLIMIT_CORE,&limit);
if(k!=0)printf("error while setting limit\n");
getrlimit(RLIMIT_CORE,&limit);
if(k==0){
 printf("%ld ",limit.rlim_cur);
  printf("%ld \n",limit.rlim_max);
}

return 0;
}
/*output
 1024 2048 
*/
