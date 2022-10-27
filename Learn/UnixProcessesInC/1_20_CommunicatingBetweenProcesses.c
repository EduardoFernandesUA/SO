#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int x = 0;

void handle_sigusr1(int sig) {
    if (x==0) printf("\n(HINT) Remenber that multipllication is repetitive addiction\n");
}

int main(int argc, char const *argv[])
{
    int pid = fork();
    if (pid==-1) { return 1; }
    if (pid==0) {
        sleep(5);
        kill(getppid(), SIGUSR1);
    } else {
        // parent process
        struct sigaction sa = {0};
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);

        printf("What is the result of 3x5: ");
        scanf("%d", &x);

        if (x==15) {
            printf("Right!");
        } else {
            printf("Wrong!");
        }
        wait(NULL);
    }
    return 0;
}
