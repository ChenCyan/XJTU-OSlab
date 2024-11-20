

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

#include <assert.h>
#define READ 0
#define WRITE 1

int pid1,pid2;
int main()
{
    int fd[2];
    char Inpipe[4001];
    char* c1="1";
    char* c2="2";
    pipe(fd);
    while( (pid1 = fork()) == -1 );
    if (pid1 == 0) {
        for (int i=0;i<2000;i++)
        {
            write(fd[WRITE],c1,1);
        }
       // sleep(2);
        exit(0);
    }
    else {
        while((pid2 = fork()) == -1);
        if (pid2 == 0){
            for (int i=0;i<2000;i++) {
                write(fd[WRITE],c2,1);
            }
           // sleep(2);
            exit(0);
        }
    else { /* father process */
        wait(NULL);
        wait(NULL);
        read(fd[READ], Inpipe, 4000);
        Inpipe[4000]='\0';
        printf("%s\n",Inpipe);
        exit(0);
    }
    }
        return 0;
    }
