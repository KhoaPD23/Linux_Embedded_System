#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_un server_addr;
    char buffer[BUFFER_SIZE] = {0};
    char *socket_path;

    if (argc < 2)
    {
        printf("No mysocket file provided.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        socket_path = argv[1];
    }

    // 1. Tạo socket
    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Thiết lập địa chỉ server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, socket_path, sizeof(server_addr.sun_path) - 1);

    // 3. Kết nối đến server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    // 4. Gửi dữ liệu
    const char *hello = "Hello from UNIX client";
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // 5. Nhận phản hồi
    read(sock, buffer, BUFFER_SIZE);
    printf("Server says: %s\n", buffer);

    // 6. Đóng socket
    close(sock);

    return 0;
}
