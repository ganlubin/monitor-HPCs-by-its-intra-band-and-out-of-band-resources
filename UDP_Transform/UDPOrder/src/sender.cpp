#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

const std::string LOCAL_HOST = "127.0.0.1";
const int TARGET_PORT = 60060;
const int NUM_PACKETS = 100;

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(TARGET_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(LOCAL_HOST.c_str());

    for (int i = 0; i < NUM_PACKETS; ++i) {
        // 将整数序号打包为字节序列
        int packetNumber = i;
        char buffer[sizeof(int)];
        memcpy(buffer, &packetNumber, sizeof(int));

        ssize_t bytesSent = sendto(sockfd, buffer, sizeof(int), 0,
                                   (struct sockaddr *)&serverAddr, sizeof(serverAddr));

        if (bytesSent < 0) {
            perror("sendto");
            close(sockfd);
            return 1;
        }

        std::cout << "Sent packet with number: " << packetNumber << std::endl;
        usleep(10000);  // 为了演示，添加短暂延迟
    }

    close(sockfd);
    return 0;
}
