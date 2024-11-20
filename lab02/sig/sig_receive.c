#include<signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>

pid_t child_pid1,child_pid2;
void father_handler(int signum) {
    if (signum == SIGALRM )
    {
        kill(child_pid1,SIGUSR1);
        kill(child_pid2,SIGUSR2);
        wait(NULL);
        wait(NULL);
        printf("[info] Parent process is killed!!\n");
        exit(0);
    }
    else if(signum == SIGQUIT){
        kill(child_pid1,SIGUSR1);
        kill(child_pid2,SIGUSR2);
        wait(NULL);
        wait(NULL);
        printf("[info] Parent process is killed!!\n");
        exit(0);
    }

    else printf("[info] error\n");
}

void child1_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("[info] Child process 1 is killed by parent!!\n");
        exit(0);
    }
}

void child2_handler(int signum) {
    if (signum == SIGUSR2) {
        printf("[info] Child process 2 is killed by parent!!\n");
        exit(0);
    }
}

int main()
{
    child_pid1 = fork();
   if (child_pid1 < 0) {
        fprintf(stderr, "[error] Child 1 Fork Failed");
        return 1;
    }
   else if (child_pid1 == 0){
       signal(SIGUSR1,child1_handler);
       signal(SIGQUIT,SIG_IGN);
       while(1) sleep(1);
   }
   else {
       child_pid2 = fork();

       if (child_pid2 < 0){
           fprintf(stderr, "[error] Child2 Fork Failed");
            return 1;
        }
     else if (child_pid2 == 0) { /* child process 2 */
            signal(SIGUSR2, child2_handler);
            signal(SIGQUIT, SIG_IGN);
            // signal(SIGQUIT, SIG_DFL);
            while (1) sleep(1);
        }
       else {
           signal(SIGQUIT,father_handler);
           signal(SIGALRM,father_handler);
           alarm(5);
           int time = 0;
           while(1){
                printf("[info] time passed: %d\n", ++time);
                sleep(1);
            }
       }}
}
