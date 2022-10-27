#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int pid = fork();
    if (pid == -1) {
        return 1;
    }

    if (pid == 0) {
        // child process
        int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
        if (file==-1) return 2;

        printf("The fd to pingResults: fd: %d\n", file);
        dup2(file, STDOUT_FILENO);
        close(file);

        int error = execlp("ping", "ping", "-c", "53", "google.com", NULL);
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
