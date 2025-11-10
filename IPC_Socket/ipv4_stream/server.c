#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int port_num, len;
    int opt = 1;
    int server_fd, new_socket;
    struct sockaddr_in server_address, client_address;
    int addrlen = sizeof(server_address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "Hello from server";

    if (argc < 2)
    {
        printf("No port provided.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        port_num = atoi(argv[1]);
    }

    memset(&server_address, 0, sizeof(struct sockaddr_in));
    memset(&client_address, 0, sizeof(struct sockaddr_in));

    // 1. Tạo socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Gắn địa chỉ (bind)
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port_num);

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 3. Lắng nghe kết nối
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    len = sizeof(client_address);

    printf("Server listening on port %d...\n", port_num);

    // 4. Chấp nhận kết nối
    if ((new_socket = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t *)&len)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // 5. Đọc dữ liệu từ client
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Client says: %s\n", buffer);

    // 6. G strlen(hello), 0);
    printf("Hello message sent\n");

    // 7. Đóng socket
    close(new_socket);
    close(server_fd);

    return 0;
}
