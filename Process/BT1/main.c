#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/wait.h>

int main(void)
{
    int ret_val = 0;
    int status = 0;
    int ret = 0;

    ret_val = fork();

    if(ret_val == 0)
    {
        printf("Child process\n");
        printf("Process ID: %d, Parent process ID: %d\n", getpid(), getppid());
        sleep(3);
        exit(111);
    }
    else if (ret_val > 0)
    {
        printf("Parent process\n");
        printf("Process ID: %d, Parent process ID: %d\n", getpid(), getppid());
        ret = wait(&status);
        if(WIFEXITED(status))
        {
            int exit_code = WEXITSTATUS(status);
            printf("Child exited with code: %d\n", exit_code);

        }
        else
        {
            printf("Issue\n");
        }
    }
    else
    {
        printf("Error\n");
    }

    return 0;
}
