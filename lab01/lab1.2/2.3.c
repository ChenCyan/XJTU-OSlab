#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdlib.h>
void print_ids(const char* prefix)
{
	pid_t pid = getpid();
	pid_t tid = syscall(SYS_gettid);
	printf("%s: PID = %d, TID = %ld\n", prefix, pid, (long)tid);
}
// 使用 system() 的线程函数
void* thread_system(void* arg) {
	printf("thread create success\n");
    print_ids("Before system() call in thread_system");
    system("./system_call"); // 调用 system_call 程序
    print_ids("After system() call in thread_system");
    return NULL;
}

// 使用 exec 的线程函数
void* thread_exec(void* arg) {
	
printf("thread create success\n");
    print_ids("Before exec() call in thread_exec");
    execl("./system_call", "system_call", NULL); // 调用 exec 替换进程映像
    perror("exec failed");
    return NULL;
}
int main()
{
int args[2] = {1, 2};	
    pthread_t tid1, tid2;

    // 创建线程
    pthread_create(&tid1, NULL, thread_exec, NULL);
    pthread_create(&tid2, NULL, thread_exec, NULL);

    // 等待线程完成
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Main program finished\n");
    return 0;
}

