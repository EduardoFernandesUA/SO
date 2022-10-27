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
        int error = execlp("ping", "ping", "-c", "3", "google.com", NULL);
        if (error==-1) {
            printf("Could not find program to execute!\n");
            return 2;
        }

    } else {
        int wstatus;
        // parent process 
        wait(&wstatus);

        if (WIFEXITED(wstatus)) {
            int statusCode = WEXITSTATUS(wstatus);
            if (WEXITSTATUS(statusCode)==0) {
                printf("Sucess!\n");
            } else {
                printf("Failure with status code %d\n", statusCode);
            }
        }

        printf("Some post processing goes here!\n");
    }

    return 0;
}
