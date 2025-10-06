#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/wait.h>

//Zombie process
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
    }
    else if (ret_val > 0)
    {
        printf("Parent process\n");
        printf("Process ID: %d, Parent process ID: %d\n", getpid(), getppid());
        while(1)
        {
            sleep(1);
        }
    }
    else
    {
        printf("Error\n");
    }

    return 0;
}

/*
Zombie Process:

Nguyên nhân: Tiến trình con kết thúc, nhưng tiến trình cha không gọi wait() để thu thập thông tin kết thúc.
Hệ quả: Tiến trình con vẫn tồn tại trong bảng tiến trình dưới dạng Z+ để lưu thông tin mã thoát.
Ý nghĩa: Nếu không xử lý, zombie sẽ chiếm tài nguyên hệ thống. Quá nhiều zombie có thể gây đầy bảng tiến trình.
*/

//Orphan process
// int main(void)
// {
//     int ret_val = 0;
//     int status = 0;
//     int ret = 0;

//     ret_val = fork();

//     if(ret_val == 0)
//     {
//         printf("Child process\n");
//         printf("Process ID: %d, Parent process ID: %d\n", getpid(), getppid());
//         for(int i = 0; i < 5; i++)
//         {
//             printf("Parent process ID: %d\n", getppid());
//             sleep(1);
//         }
//         exit(0);
//     }
//     else if (ret_val > 0)
//     {
//         printf("Parent process\n");
//         printf("Process ID: %d, Parent process ID: %d\n", getpid(), getppid());
//         exit(0);
//     }
//     else
//     {
//         printf("Error\n");
//     }

//     return 0;
// }

/*
Orphan Process:

Nguyên nhân: Tiến trình cha kết thúc trước khi tiến trình con kết thúc.
Hệ quả: Tiến trình con được hệ thống (thường là init hoặc systemd) nhận nuôi.
Ý nghĩa: Linux xử lý orphan rất tốt, không gây hại. Tuy nhiên, nếu tiến trình con cần giao tiếp với cha, việc cha biến mất có thể gây lỗi logic.
*/
