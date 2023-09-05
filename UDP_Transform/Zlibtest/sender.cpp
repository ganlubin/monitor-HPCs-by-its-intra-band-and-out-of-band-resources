#include <iostream>
#include <vector>
#include <string>
#include <zlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <nlohmann/json.hpp>

int main() {
    // 创建一个示例的 JSON 数据数组
    std::vector<nlohmann::json> data;
    for (int i = 0; i < 1000; ++i) {
        nlohmann::json obj = {{"index", i}, {"value", "This is some data"}};
        data.push_back(obj);
    }

    // 将 JSON 数据序列化为字符串
    std::string json_str = nlohmann::json(data).dump();

    // 压缩数据
    uLong sourceLen = json_str.length();
    uLong destLen = compressBound(sourceLen);
    std::vector<Bytef> compressedData(destLen);
    if (compress(&compressedData[0], &destLen, (const Bytef*)json_str.c_str(), sourceLen) != Z_OK) {
        std::cerr << "Compression failed" << std::endl;
        return 1;
    }

    // 设置接收端地址和端口号
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // 创建 UDP 套接字
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // 发送压缩后的数据
    ssize_t sentBytes = sendto(sock, compressedData.data(), destLen, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (sentBytes == -1) {
        std::cerr << "Failed to send data" << std::endl;
        close(sock);
        return 1;
    }

    close(sock);

    return 0;
}

