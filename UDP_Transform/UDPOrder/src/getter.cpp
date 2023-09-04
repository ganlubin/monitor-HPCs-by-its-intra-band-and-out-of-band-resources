#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

const int LISTEN_PORT = 60060;
const int NUM_PACKETS = 100;

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in serverAddr, clientAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(LISTEN_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind");
        close(sockfd);
        return 1;
    }

    for (int i = 0; i < NUM_PACKETS; ++i) {
        char buffer[sizeof(int)];
        socklen_t clientAddrLen = sizeof(clientAddr);

        ssize_t bytesRead = recvfrom(sockfd, buffer, sizeof(int), 0,
                                     (struct sockaddr *)&clientAddr, &clientAddrLen);

        if (bytesRead < 0) {
            perror("recvfrom");
            close(sockfd);
            return 1;
        }

        if (bytesRead != sizeof(int)) {
            std::cerr << "Received packet with invalid size." << std::endl;
            continue;
        }

        int packetNumber;
        memcpy(&packetNumber, buffer, sizeof(int));

        std::cout << "Received packet with number: " << packetNumber << std::endl;
    }

    close(sockfd);
    return 0;
}
