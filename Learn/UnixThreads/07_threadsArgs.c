#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2,3,5,7,11,13,17,19,23,29};

void* routine(void* arg) {
    int index = *(int*)arg;
    printf("%d ", primes[index]);
    free(arg);
}

int main(int argc, char const *argv[])
{
    pthread_t th[10];
    for(int i=0; i<10; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) return 1;
    }
    for(int i=0; i<10; i++) {
        if (pthread_join(th[i], NULL) != 0) return 1;
    }
    return 0;
}
