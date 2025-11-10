#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/unix_dgram_server"
#define BUFFER_SIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_un server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t client_len = sizeof(client_addr);

    // 1. Tạo socket datagram
    if ((sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Xóa file socket cũ nếu tồn tại
    unlink(SOCKET_PATH);

    // 2. Thiết lập địa chỉ server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // 3. Bind
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UNIX Datagram Server listening on %s...\n", SOCKET_PATH);

    // 4. Nhận dữ liệu từ client
    while (1)
    {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_len);
        buffer[n] = '\0';
        printf("Client says: %s\n", buffer);

        // 5. Gửi phản hồi
        const char *hello = "Hello from UNIX Datagram server";
        sendto(sockfd, hello, strlen(hello), 0, (struct sockaddr *)&client_addr, client_len);
        printf("Response sent\n");
    }

    close(sockfd);
    unlink(SOCKET_PATH);
    return 0;
}
