#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

// chefs = threads
// stove = shared data (+mutex)

pthread_mutex_t stoveMutex;
int stoveFuel[4] = {100,100,100,100};

void* routine(void* args) {
    pthread_mutex_lock(&stoveMutex);
    int fuelNeeded = (rand() % 20);
    if (stoveFuel - fuelNeeded < 0) {
        printf("No more fuel... going home\n");
    } else {
        stoveFuel -= fuelNeeded;
        usleep(500000);
        printf("Fuel left %d\n", stoveFuel);
    }
    pthread_mutex_unlock(&stoveMutex);
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int n = 10;
    pthread_t* th = malloc(sizeof(pthread_t) * n);
    pthread_mutex_init(&stoveMutex, NULL);

    for (int i = 0; i < n; i++) {
        if (pthread_create(th+i, NULL, &routine, NULL) != 0) return 1;
    }

    for (int i = 0; i < n; i++) {
        pthread_join(th[i], NULL);
    }
    
    pthread_mutex_destroy(&stoveMutex);


    return 0;
}
