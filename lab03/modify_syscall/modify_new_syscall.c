#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/syscall.h>
int main()
{
    int ret = syscall(96, 10, 20); // after modify syscall 78
    printf("%d\n", ret);
    return 0;
}
