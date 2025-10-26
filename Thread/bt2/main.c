#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/wait.h>
#include <pthread.h>

#define NUM_THREADS 3
#define INCREMENTS 1000000

long long counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* increment_counter(void* arg)
{
    for(int i = 0; i < INCREMENTS; i++)
    {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t threads[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++)
    {
        if(pthread_create(&threads[i], NULL, increment_counter, NULL) != 0)
        {
            perror("Can not create thread\n");
            return EXIT_FAILURE;
        }
    }

    for(int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("counter = %lld\n", counter);

    return 0;
}
