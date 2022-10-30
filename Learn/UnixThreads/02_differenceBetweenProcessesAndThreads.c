/* THREADS */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;

void* routine() {
    x++;
    sleep(2);
    printf("Value of x: %d\n", x);
}

void* routine2() {
    sleep(2);
    printf("Value of x: %d\n", x);
}

int main(int argc, char const *argv[])
{
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL) != 0) return 1;
    if (pthread_create(&t2, NULL, &routine2, NULL) != 0) return 1;
    if (pthread_join(t1, NULL)) return 3;
    if (pthread_join(t2, NULL)) return 4;
    return 0;
}






/* PROCESSES */
/*
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int x = 2;
    int pid = fork();
    if (pid == -1) return 1;

    if (pid == 0) x++;

    sleep(2);
    printf("Value of x: %d\n", x);
    if (pid != 0) {
        wait(NULL);
    }

    return 0;
}
*/

