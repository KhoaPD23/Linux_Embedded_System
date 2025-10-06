#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/wait.h>

int main(void)
{
    int ret_val = 0;
    int status = 0;
    int ret = 0;

    setenv("MY_COMMAND", "ls", 1);

    ret_val = fork();

    if(ret_val == 0)
    {
        printf("Child process\n");
        printf("Process ID: %d, Parent process ID: %d\n", getpid(), getppid());

        // execlp(file, program_name, parameter, ..., NULL)
        execlp("MY_COMMAND", "MY_COMMAND", NULL);

        perror("execlp failed");
        exit(123);
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

/*
Khi tiến trình con gọi exec() (ví dụ execlp()), không gian địa chỉ và mã lệnh của tiến trình con sẽ bị thay thế hoàn toàn bởi chương trình mới được chỉ định.
Cụ thể:

Toàn bộ mã lệnh, dữ liệu, stack, heap của tiến trình con sẽ bị ghi đè bởi chương trình mới (ví dụ ls).
PID của tiến trình không thay đổi, nhưng nội dung bên trong tiến trình thì thay đổi hoàn toàn.
Các lệnh sau execlp() sẽ không được thực thi, trừ khi execlp() thất bại.
Nếu execlp() thành công, tiến trình con trở thành tiến trình thực thi lệnh mới (ví dụ ls), như thể nó được khởi động từ đầu.
*/
