#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int port_num;
    int sock = 0;
    struct sockaddr_in client_address;
    char buffer[BUFFER_SIZE] = {0};

    if (argc < 2)
    {
        printf("Error.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        port_num = atoi(argv[2]);
    }

    memset(&client_address, 0, sizeof(struct sockaddr_in));

    // 1. Tạo socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation error");
        return -1;
    }

    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(port_num);

    // 2. Chuyển địa chỉ IP từ text sang binary
    if (inet_pton(AF_INET, argv[1], &client_address.sin_addr) <= 0)
    {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // 3. Kết nối đến server
    if (connect(sock, (struct sockaddr *)&client_address, sizeof(client_address)) < 0)
    {
        perror("Connection Failed");
        return -1;
    }

    // 4. Gửi dữ liệu
    const char *hello = "Hello from client";
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // 5. Nhận phản hồi
    read(sock, buffer, BUFFER_SIZE);
    printf("Server says: %s\n", buffer);

    // 6. Đóng socket
    close(sock);

    return 0;
}
