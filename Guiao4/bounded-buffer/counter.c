#include  <stdio.h>
#include  <stdlib.h>
#include  <libgen.h>
#include  <unistd.h>
#include  <sys/wait.h>
#include  <sys/types.h>
#include  <pthread.h>
#include  <math.h>
#include <stdint.h>

#include "thread.h"

struct ARGV {
    unsigned int id;
    unsigned int iteractions;
    // unsigned int *number;
};

void* count_n(void* data) {
    int *n = (int *) data;
    pthread_detach(pthread_self());
    for (int i = 0; i < 10; i++)
    {
        *n = *n + 1;
        printf("n: %d", *n);
    }
    pthread_exit(NULL);	
}

void main(int argc, char *argv[]) {
    int threads_number = 5;
    pthread_t thread_id[threads_number];
    int n = 0;
    for (int i = 0; i < threads_number; i++) {
        // ARGV data[];
        // argv
        thread_create(&thread_id[i], NULL, count_n, (void *)&n);
    }
    pthread_exit(NULL);	
    
}