#include<stdio.h>
#include<pthread.h>
int shared_var = 0;
void* add_100(void*arg){

	printf("thread2 is created successfully\n");
        for(int i=0;i<1000000;i++)
        {
                shared_var += 100;
        }
        return NULL;
}

void* sub_100(void*arg){

	printf("thread2 is created successfully\n");
        for(int i=0;i<1000000;i++)
        {
                shared_var  -= 100;
        }
        return NULL;
}
int main()
{
	pthread_t thread1,thread2;
	pthread_create(&thread1,NULL,add_100,NULL);
	pthread_create(&thread2,NULL,sub_100,NULL);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	 printf("Final value of shared_var: %d\n", shared_var);
	 return 0;

}
