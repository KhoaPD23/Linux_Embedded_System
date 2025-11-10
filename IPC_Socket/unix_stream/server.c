#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "Hello from UNIX server";
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
    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Xóa file socket cũ nếu tồn tại
    unlink(socket_path);

    // 2. Thiết lập địa chỉ
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, socket_path, sizeof(server_addr.sun_path) - 1);

    // 3. Bind
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 4. Listen
    if (listen(server_fd, 3) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("UNIX server listening on %s...\n", socket_path);

    // 5. Accept
    client_len = sizeof(client_addr);
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) < 0)
    {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // 6. Đọc dữ liệu từ client
    read(client_fd, buffer, BUFFER_SIZE);
    printf("Client says: %s\n", buffer);

    // 7. Gửi phản hồi
    send(client_fd, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // 8. Đóng socket
    close(client_fd);
    close(server_fd);
    unlink(socket_path);

    return 0;
}
