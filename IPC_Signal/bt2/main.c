#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/wait.h>
#include "pthread.h"
#include "signal.h"

unsigned char count = 0;

void sig_handler_alrm(int num);

void sig_handler_alrm(int num)
{
    printf("Timer: %d seconds\n", count);

    if(count >= 10)
    {
        exit(EXIT_SUCCESS);
    }
}

int main(void)
{
    if(signal(SIGALRM, sig_handler_alrm) == SIG_ERR)
    {
        perror("Can not sign in handler for SIGALRM");
        exit(EXIT_FAILURE);
    }

    printf("Timer: %d seconds\n", count);

    while(1)
    {
        alarm(1);
        count++;
        pause();
    }

    return 0;
}
