#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int data;
int data_ready = 0;

pthread_mutex_t mutex;
pthread_cond_t cond;

void* producer(void* arg)
{
    for(int i = 0; i < 10; i++)
    {
        int value = rand() % 100;

        pthread_mutex_lock(&mutex);
        data = value;
        data_ready = 1;
        printf("Producer create data: %d\n", data);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg)
{
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex);
        while(!data_ready)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("Consumer receive data: %d\n", data);
        data_ready = 0;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t prod, cons;

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
