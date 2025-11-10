#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_SOCKET_PATH "/tmp/unix_dgram_server"
#define CLIENT_SOCKET_PATH "/tmp/unix_dgram_client"
#define BUFFER_SIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_un server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);

    // 1. Tạo socket datagram
    if ((sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Xóa file socket client cũ nếu tồn tại
    unlink(CLIENT_SOCKET_PATH);

    // 2. Thiết lập địa chỉ client
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, CLIENT_SOCKET_PATH, sizeof(client_addr.sun_path) - 1);

    // Bind client để nhận phản hồi
    if (bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 3. Thiết lập địa chỉ server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SERVER_SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // 4. Gửi dữ liệu đến server
    const char *hello = "Hello from UNIX Datagram client";
    sendto(sockfd, hello, strlen(hello), 0, (struct sockaddr *)&server_addr, addr_len);
    printf("Message sent to server\n");

    // 5. Nhận phản hồi
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
    buffer[n] = '\0';
    printf("Server says: %s\n", buffer);

    close(sockfd);
    unlink(CLIENT_SOCKET_PATH);
    return 0;
}
