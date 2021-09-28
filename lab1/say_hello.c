#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("PID of say_hello = %d\n", getpid());
    printf("Hello\n");
    return 0;
}