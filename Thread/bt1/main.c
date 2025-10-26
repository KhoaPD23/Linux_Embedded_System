#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/wait.h>
#include "pthread.h"

pthread_t tid1, tid2;

void* thread_function(void* arg)
{
    if(pthread_equal(tid1, pthread_self()) != 0)
    {
        printf("Thread 1 with ID %lu is running\n", (unsigned long)tid1);
        sleep(3);
    }
    else if(pthread_equal(tid2, pthread_self()) != 0)
    {
        printf("Thread 2 with ID %lu is running\n", (unsigned long)tid2);
        sleep(3);
    }
    else
    {
        // Do nothing
    }
    pthread_exit(NULL);
}

int main(void)
{
    if(pthread_create(&tid1, NULL, thread_function, NULL) != 0)
    {
        perror("Can not create thread1");
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&tid2, NULL, thread_function, NULL) != 0)
    {
        perror("Can not create thread2");
        exit(EXIT_FAILURE);
    }

    printf("Thread ID 1: %lu\n", (unsigned long)tid1);
    printf("Thread ID 2: %lu\n", (unsigned long)tid2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Completed.\n");
    return 0;
}
