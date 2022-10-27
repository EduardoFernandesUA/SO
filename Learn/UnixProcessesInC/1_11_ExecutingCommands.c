#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int pid = fork();
    if (pid == -1) {
        return 1;
    }

    if (pid == 0) {
        // child process
        execlp("ping", "ping", "-c", "3", "google.com", NULL);
    } else {
        // parent process
        wait(NULL);
        printf("Sucess!\n");
        printf("Some post processing goes here!\n");
    }

    return 0;
}
