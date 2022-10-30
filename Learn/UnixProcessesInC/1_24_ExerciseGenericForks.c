#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int n;
    printf("n: ");
    scanf("%d", &n);

    int mx; // initial x
    printf("x: ");
    scanf("%d", &mx);

    int fdFromMain[2];
    int fdToMain[2];
    if (pipe(fdFromMain) < 0) return 1;
    if (pipe(fdToMain) < 0) return 2;

    for(int i=0; i<n; i++) {
        int pid = fork();
        if (pid == 0) {
            int x;
            if (read(fdFromMain[0], &x, sizeof(int)) < 0) return 3;
            x += 5;
            if (write(fdToMain[1], &x, sizeof(int)) < 0) return 4;

            close(fdFromMain[0]);
            close(fdFromMain[1]);
            close(fdToMain[0]);
            close(fdToMain[1]);
            return 0;
        }

        // Parent Process
        if (write(fdFromMain[1], &mx, sizeof(int)) < 0) return 5;
        if (read(fdToMain[0], &mx, sizeof(int)) < 0) return 6;

        wait(NULL);
    }

    close(fdFromMain[0]);
    close(fdFromMain[1]);
    close(fdToMain[0]);
    close(fdToMain[1]);

    printf("Result: %d\n", mx);
    return 0;
}
    /*
    int fd[n][2];
    int i;
    for(i=0; i<3; i++){
        if (pipe(fd[i]) < 0) return 1;
    }

    int pid1 = fork();
    if (pid1 < 0) return 2;

    if (pid1 == 0) {
        // child process
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);

        int x;
        if (read(fd[0][0], &x, sizeof(int)) < 0) return 3;

        x += 5;
        if (write(fd[1][1], &x, sizeof(int)) < 0) return 4;

        close(fd[0][0]);
        close(fd[1][1]);

        return 0;
    }

    int pid2 = fork();
    if (pid2 < 0) return 5;

    if (pid2 == 0) {
        // child process 2
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);

        int x;
        if (read(fd[1][0], &x, sizeof(int)) < 0) return 6;

        x += 5;
        if (write(fd[2][1], &x, sizeof(int)) < 0) return 7;

        close(fd[1][0]);
        close(fd[2][1]);

        return 0;
    }

    // Parent process
    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);

    int x = 0;
    printf("Input Number: ");
    scanf("%d", &x);
    if (write(fd[0][1], &x, sizeof(int)) < 0) return 8;

    if (read(fd[2][0], &x, sizeof(int)) < 0) return 9;

    printf("Result is %d\n", x);

    close(fd[0][1]);
    close(fd[2][0]);

    return 0;
}
*/
