#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
int num = 0;
int main()
{
	pid_t pid,pid1;
	pid = fork();
	if (pid<0){
		fprintf(stderr,"Fork Failed");
		return 1;
	}
	else if (pid == 0 )
	{
		num = 1;
		pid1=getpid();
		printf("child:pid = %d\n",pid);
		printf("child:pid1 = %d\n",pid1);
		printf("child:num = %d,child:*num = %p\n",num,&num);
	}
	else{
		num = -1;
		pid1 = getpid();
		printf("parent:pid = %d\n",pid);
		printf("parent:pid1 = %d\n",pid1);
		printf("parent:num = %d,parent:*num = %p\n",num,&num);
		wait(NULL);
	}
	return 0;
}
