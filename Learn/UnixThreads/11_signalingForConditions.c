#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void* fuel_filling(void* arg) {
    for(int i=0; i<5; i++) {
        pthread_mutex_lock(&mutexFuel);
        fuel += 30;
        printf("Filled fuel... %d\n", fuel);
        pthread_cond_broadcast(&condFuel);
        pthread_mutex_unlock(&mutexFuel);
        sleep(1);
    }
}

void* car(void* arg) {
    pthread_mutex_lock(&mutexFuel);
    while(fuel<40) {
        printf("No fuel. Wainting...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
    }
    printf("Got fuel. Now left: %d\n", fuel);
    fuel -= 40;
    pthread_mutex_unlock(&mutexFuel);
    sleep(1);
}

int main(int argc, char const *argv[])
{
    pthread_t th[6];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);

    for(int i=0; i<6; i++) {
        if (i == 4 || i == 5) {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0) perror("Failed to create thread");
        } else {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0) perror("Failed to create thread");
        }
    }

    for(int i=0; i<6; i++) {
        if (pthread_join(th[i], NULL) != 0) perror("Failed to join thread");
    }

    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}
