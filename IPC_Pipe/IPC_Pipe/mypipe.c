#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

char pipebuff[1024];

int main(int argc, char *argv[])
{
    int pipefd[2];

    // Create pipe: pipe[0] is reader, pipe[1] is writer
    if(pipe(pipefd) == -1)
    {
        perror("pipe");
        return EXIT_FAILURE;
    }

    // Create 1st child process to execute ls -l
    pid_t pid1 = fork();
    if(pid1 == 0)
    {
        // Close reader of pipe, only write in 1st child process
        if(close(pipefd[0]) == -1)
        {
            perror("close read end (child1)");
            _exit(127);
        }

        // Redirect stdout (fd=1) to the write end of the pipe
        if(dup2(pipefd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2 to stdout (child1)");
            _exit(127);
        }

        // After dup2, pipefd[1] can be closed since stdout is pointing to it
        if(close(pipefd[1]) == -1)
        {
            perror("close write end after dup2 (child1)");
            _exit(127);
        }

        // Execute ls -l
        execlp("ls", "ls", "-l", (char *)NULL);

        // If execlp fail
        perror("execlp ls -l (child1)");
        _exit(127);
    }

    // Create 2nd child process to execute wc -l
    pid_t pid2 = fork();
    if(pid2 == 0)
    {
        // Close writer of pipe, only read in 2nd child process
        if(close(pipefd[1]) == -1)
        {
            perror("close write end (child2)");
            _exit(127);
        }

        // Redirect stdin (fd=0) to the pipe's reader
        if(dup2(pipefd[0], STDIN_FILENO) == -1)
        {
            perror("dup2 to stdin (child2)");
            _exit(127);
        }

        // After dup2, pipefd[0] can be closed since stdin is pointing to it
        if(close(pipefd[0]) == -1)
        {
            perror("close read end after dup2 (child2)");
            _exit(127);
        }

        // Execute "wc -l"
        execlp("wc", "wc", "-l", (char *)NULL);

        // If execlp fail
        perror("execlp wc -l (child2)");
        _exit(127);
    }

    // Parent process
    // Parent process is not use pipe -> close reader and writer
    if(close(pipefd[0]) == -1)
    {
        perror("close read end (parent)");
    }
    if(close(pipefd[1]) == -1)
    {
        perror("close write end (parent)");
    }

    // Waiting 2 children process complete
    int status1, status2;
    if(waitpid(pid1, &status1, 0) == -1)
    {
        perror("waitpid child1");
    }
    if(waitpid(pid2, &status2, 0) == -1)
    {
        perror("waitpid child2");
    }

    // Checking exit code
    if(WIFEXITED(status1))
    {
        // printf("child1 exit code = %d\n", WEXITSTATUS(status1));
    }
    if(WIFEXITED(status2))
    {
        // printf("child2 exit code = %d\n", WEXITSTATUS(status2));
    }

    return 0;
}
