#include <arpa/inet.h>
#include <cstring>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <nlohmann/json.hpp>
#include <proc/readproc.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

std::vector<proc_t> vector;

int packageGet(const int &);

int main() {
  packageGet(60060);
  return 0;
}

int packageGet(const int &targetPort) {
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket");
    return -1;
  }

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(targetPort);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("bind");
    close(sockfd);
    return -1;
  }

  std::string receivedData;
  char buffer[1024];
  ssize_t bytesRead;

  while (1) {
    bytesRead = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
    if (bytesRead < 0) {
      perror("recvfrom");
      close(sockfd);
      return -1;
    }

    // 打开文件并设置追加模式
    std::ofstream outputFile("./testfolder/info.txt", std::ios::app);

    if (!outputFile) {
      std::cerr << "Error opening file for appending." << std::endl;
      return 1;
    }

    // 将字符串追加到文件
    outputFile << buffer << std::endl;
    outputFile.flush();
    // 关闭文件
    outputFile.close();
  }

  close(sockfd);
  return 0;
}
