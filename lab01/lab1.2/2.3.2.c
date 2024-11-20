#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdlib.h>
int shared_var = 0;
sem_t sem;
void print_ids(const char* prefix) {
    pid_t pid = getpid();
    pid_t tid = syscall(SYS_gettid); // 获取线程 ID
    printf("%s: PID = %d, TID = %ld\n", prefix, pid, (long)tid);
}
void* add_100(void*arg){
	printf("thread1 is created successfully\n");
	 print_ids("Before exec() call in thread_exec");
	 execl("./system_call", "system_call", NULL);
    perror("exec failed");
        for(int i=0;i<10000;i++)
        {
		sem_wait(&sem);
                shared_var =shared_var+ 100;
		sem_post(&sem);
        }
        return NULL;
}

void* sub_100(void*arg){
	printf("thread2 is created successfully\n");
	 print_ids("Before exec() call in thread_exec");
	execl("./system_call", "system_call", NULL);
   	 perror("exec failed");
        for(int i=0;i<10000;i++)
        {
		sem_wait(&sem);
                shared_var  =shared_var - 100;
		sem_post(&sem);
        }
        return NULL;
}
int main()
{
	sem_init(&sem,0,1);
	pthread_t thread1,thread2;
	pthread_create(&thread1,NULL,add_100,NULL);
	pthread_create(&thread2,NULL,sub_100,NULL);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	sem_destroy(&sem);
	 printf("Final value of shared_var: %d\n", shared_var);
	 return 0;

}

