#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int sockfd;
    int port_num;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);
    const char *hello = "Hello from UDP server";

    if (argc < 2)
    {
        printf("No port provided.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        port_num = atoi(argv[1]);
    }

    // 1. Tạo socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Thiết lập địa chỉ server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_num);

    // 3. Bind
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UDP Server listening on port %d...\n", port_num);

    // 4. Nhận dữ liệu từ client
    while (1)
    {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';
        printf("Client says: %s\n", buffer);

        // 5. Gửi phản hồi
        sendto(sockfd, hello, strlen(hello), 0, (struct sockaddr *)&client_addr, addr_len);
        printf("Response sent\n");
    }

    close(sockfd);
    return 0;
}
