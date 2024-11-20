// system_call.c
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("In system_call program: PID = %d\n", getpid());
    return 0;
}

