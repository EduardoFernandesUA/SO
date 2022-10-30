#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;

void* routine() {
    for(int i=0; i<1000000; i++)
        mails++;
}

int main(int argc, char const *argv[])
{
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL) != 0) return 1;
    if (pthread_create(&t2, NULL, &routine, NULL) != 0) return 1;
    if (pthread_join(t1, NULL)) return 3;
    if (pthread_join(t2, NULL)) return 4;
    printf("Number of mails: %d\n", mails);
    return 0;
}