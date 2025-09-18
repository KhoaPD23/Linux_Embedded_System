#include "stdio.h"
#include "string.h"
#include "sys/stat.h"
#include "time.h"

const char *get_file_type(mode_t m)
{
    if(S_ISREG(m))
    {
        return "regular file";
    }
    if(S_ISDIR(m))
    {
        return "directory";
    }
    if(S_ISLNK(m))
    {
        return "symbolic link";
    }
    if(S_ISCHR(m))
    {
        return "character device";
    }
    if(S_ISBLK(m))
    {
        return "block device";
    }
    if(S_ISFIFO(m))
    {
        return "FIFO/pipe";
    }
    if(S_ISSOCK(m))
    {
        return "socket";
    }
    return "unknown";
}

int main(int argc, char *argv[])
{
    struct stat st;

    if((argc == 1) || (argc > 2))
    {
        printf("Usage: %s <file_path>\n", argv[0]);
    }

    else
    {
        if(lstat(argv[1], &st) == -1)
        {
            perror("lstat");
            return 1;
        }

        else
        {
            printf("File path: %s\n", argv[1]);
            printf("Type of file: %s\n", get_file_type(st.st_mode));
            printf("Size of file: %ld bytes\n", st.st_size);

            time_t modified_time = st.st_mtime;

            char time_str[100];
            struct tm *timeinfo = localtime(&modified_time);
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);

            printf("Last Modified: %s\n", time_str);
        }
    }

    return 0;
}
