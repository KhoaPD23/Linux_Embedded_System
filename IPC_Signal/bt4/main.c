#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>

volatile int sigint_received = 0;
volatile int sigterm_received = 0;

void handle_sigint(int sig)
{
    sigint_received = 1;
}

void handle_sigterm(int sig)
{
    sigterm_received = 1;
}

int main(void)
{
    printf("Process ID: %d\n", getpid());

    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigterm);

    char buffer[1024];

    while(1)
    {
        if(sigterm_received)
        {
            printf("SIGTERM received. Exiting...\n");
            break;
        }

        if(sigint_received)
        {
            printf("SIGINT received.\n");
            sigint_received = 0;  // Reset flag
        }

        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        int ready = select(STDIN_FILENO + 1, &readfds, NULL, NULL, NULL);

        if(ready > 0 && FD_ISSET(STDIN_FILENO, &readfds))
        {
            if(fgets(buffer, sizeof(buffer), stdin) != NULL)
            {
                buffer[strcspn(buffer, "\n")] = '\0';
                printf("You entered: %s\n", buffer);
            }
        }
    }

    return 0;
}
