#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/wait.h>
#include "pthread.h"
#include "signal.h"

unsigned char count = 0;

void sig_handler_usr1(int num);

void sig_handler_usr1(int num)
{
    printf("Received signal from parent\n");
    count++;
    printf("Count = %d\n", count);
    if(count > 4)
    {
        exit(EXIT_SUCCESS);
    }
}

int main(void)
{
    

    return 0;
}
