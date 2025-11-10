#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int port_num;
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);

    if (argc < 2)
    {
        printf("Error.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        port_num = atoi(argv[2]);
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
    server_addr.sin_port = htons(port_num);
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    // 3. Gửi dữ liệu đến server
    const char *hello = "Hello from UDP client";
    sendto(sockfd, hello, strlen(hello), 0, (struct sockaddr *)&server_addr, addr_len);
    printf("Message sent to server\n");

    // 4. Nhận phản hồi từ server
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
    buffer[n] = '\0';
    printf("Server says: %s\n", buffer);

    close(sockfd);
    return 0;
}
