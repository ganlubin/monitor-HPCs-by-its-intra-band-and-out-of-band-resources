#include <iostream>
#include <vector>
#include <zlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <nlohmann/json.hpp>

int main() {
    // 设置接收端地址和端口号
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 创建 UDP 套接字
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // 绑定套接字到端口
    if (bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Bind failed" << std::endl;
        close(sock);
        return 1;
    }

    // 接收数据
    const int bufferSize = 65536; // 64 KB buffer
    std::vector<Bytef> receiveBuffer(bufferSize);

    ssize_t receivedBytes = recv(sock, receiveBuffer.data(), bufferSize, 0);
    if (receivedBytes == -1) {
        std::cerr << "Failed to receive data" << std::endl;
        close(sock);
        return 1;
    }

    // 解压数据
    uLong destLen = bufferSize;
    std::vector<Bytef> decompressedData(destLen);

    if (uncompress(decompressedData.data(), &destLen, receiveBuffer.data(), receivedBytes) != Z_OK) {
        std::cerr << "Decompression failed" << std::endl;
        close(sock);
        return 1;
    }

    // 将解压后的数据转化为字符串
    std::string json_str(reinterpret_cast<char*>(decompressedData.data()), destLen);
    std::cout << "Received JSON data: " << json_str << std::endl;

    close(sock);

    return 0;
}

