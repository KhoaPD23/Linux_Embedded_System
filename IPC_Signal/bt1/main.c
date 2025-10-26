#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/wait.h>
#include "pthread.h"
#include "signal.h"

unsigned char count = 0;

void sig_handler_int(int num);

void sig_handler_int(int num)
{
    printf("SIGINT received\n");
    count++;

    if(count > 2)
    {
        exit(EXIT_SUCCESS);
    }
}

int main(void)
{
    if(signal(SIGINT, sig_handler_int) == SIG_ERR)
    {
        perror("Can not sign in handler for SIGINT");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        sleep(1);
    }

    return 0;
}
