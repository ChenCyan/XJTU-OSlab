#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
int shared_var = 0;
sem_t sem;
void* add_100(void*arg){
	printf("thread1 is created successfully\n");
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

