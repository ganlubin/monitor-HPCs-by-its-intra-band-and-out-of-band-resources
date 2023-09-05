#include <iostream>

#include "include/tools.hpp"

#include <proc/readproc.h>

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
  if (bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
    std::cerr << "Bind failed" << std::endl;
    close(sock);
    return 1;
  }

  // 接收数据
  const int bufferSize = 65536 << 1; // 64 << 1 KB buffer
  std::vector<Bytef> receiveBuffer(bufferSize);

  ssize_t receivedBytes = recv(sock, receiveBuffer.data(), bufferSize, 0);
  if (receivedBytes == -1) {
    std::cerr << "Failed to receive data" << std::endl;
    close(sock);
    return 1;
  }
  std::cout << "Received compressed data length: " << receivedBytes << " bytes"
            << std::endl;


  // 解压数据
  uLong destLen = bufferSize;
  std::vector<Bytef> decompressedData(bufferSize);

  int uncompressResult = uncompress(decompressedData.data(), &destLen,
                                    receiveBuffer.data(), receivedBytes);
  if (uncompressResult != Z_OK) {
    std::cerr << "Decompression failed with error code: " << uncompressResult
              << std::endl;
    close(sock);
    return 1;
  }

  // 将解压后的数据转化为字符串
  std::string json_str(reinterpret_cast<char *>(decompressedData.data()),
                       destLen);
  
  std::size_t sizeInBytes = json_str.size();
  std::cout << sizeInBytes << std::endl;

  saveToFile(json_str, "./text.txt", 'w');

  close(sock);
}