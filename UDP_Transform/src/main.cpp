#include <arpa/inet.h>
#include <cstring>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <nlohmann/json.hpp>
#include <proc/readproc.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

const std::string LOCAL_HOST = "127.0.0.1";
const int MAX_PACKET_SIZE = 1024;

PROCTAB *proc;
proc_t proc_info;
std::vector<proc_t> processes;
// 创建一个存储 JSON 数据的数组
std::vector<nlohmann::json> proc_json;

void pushToVector(const std::vector<proc_t> &, std::vector<nlohmann::json> &);
void sendFragmentedUDP(const std::string &, const int &);
void readFromProc(PROCTAB *, proc_t &);
void printToFile(const std::vector<nlohmann::json> &);
bool fileExists(const std::string &);

int main() {

  readFromProc(proc, proc_info);

  pushToVector(processes, proc_json);

  sendFragmentedUDP(LOCAL_HOST, 60060);

  // printToFile(proc_json);

  return 0;
}

void sendFragmentedUDP(const std::string &targetAddr, const int &targetPort) {
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket");
    return;
  }

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(targetPort);
  serverAddr.sin_addr.s_addr = inet_addr(targetAddr.c_str());

  std::string jsonString = nlohmann::json(proc_json).dump(4);

  // 计算需要分片的数量
  int numFragments = jsonString.length() / MAX_PACKET_SIZE;
  if (jsonString.length() % MAX_PACKET_SIZE != 0) {
    numFragments++;
  }

  // 发送分片
  for (int i = 0; i < numFragments; i++) {
    int start = i * MAX_PACKET_SIZE;
    int end = std::min((i + 1) * MAX_PACKET_SIZE,
                       static_cast<int>(jsonString.length()));
    std::string fragment = jsonString.substr(start, end - start);

    ssize_t bytesSent =
        sendto(sockfd, fragment.c_str(), fragment.length(), 0,
               (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    if (bytesSent < 0) {
      perror("sendto");
      close(sockfd);
      return;
    }

    // // 保存文件
    // std::string filename = "./testfolder/fragment_" + std::to_string(i + 1) + ".json";
    // std::ofstream outFile(filename);
    // if (!outFile) {
    //   std::cerr << "Error opening file for writing: " << filename << std::endl;
    //   close(sockfd);
    //   return;
    // }

    // outFile << fragment;
    // outFile.close();

    std::cout << "Sent " << bytesSent << " bytes of data (Fragment " << i + 1
              << "/" << numFragments << ")" << std::endl;
  }

  close(sockfd);
  return;
}

void pushToVector(const std::vector<proc_t> &processes,
                  std::vector<nlohmann::json> &proc_json) {
  for (const proc_t &tt : processes) {
    nlohmann::json jsonObject;
    jsonObject["tid"] = tt.tid;
    jsonObject["ppid"] = tt.ppid;
    jsonObject["state"] = tt.state;
    jsonObject["size"] = tt.size;
    jsonObject["resident"] = tt.resident;
    jsonObject["share"] = tt.share;
    jsonObject["trs"] = tt.trs;
    jsonObject["lrs"] = tt.lrs;
    jsonObject["drs"] = tt.drs;
    jsonObject["dt"] = tt.dt;
    jsonObject["vm_size"] = tt.vm_size;
    jsonObject["vm_lock"] = tt.vm_lock;
    jsonObject["vm_rss"] = tt.vm_rss;
    jsonObject["vm_rss_anon"] = tt.vm_rss_anon;
    jsonObject["vm_rss_shared"] = tt.vm_rss_shared;
    jsonObject["vm_data"] = tt.vm_data;
    jsonObject["vm_stack"] = tt.vm_stack;
    jsonObject["vm_swap"] = tt.vm_swap;
    jsonObject["vm_exe"] = tt.vm_exe;
    jsonObject["vm_lib"] = tt.vm_lib;
    jsonObject["cmd"] = tt.cmd;
    jsonObject["nlwp"] = tt.nlwp;
    jsonObject["tgid"] = tt.tgid;
    jsonObject["exit_signal"] = tt.exit_signal;
    jsonObject["processor"] = tt.processor;

    proc_json.push_back(jsonObject);
  }
}

void printToFile(const std::vector<nlohmann::json> &vector) {
  // 目标目录路径
  std::string targetDirectory = "./testfolder/";

  for (size_t i = 0; i < vector.size(); ++i) {
    // 构造文件名，例如 "file1.json", "file2.json", ...
    std::string fileName =
        targetDirectory + "file" + std::to_string(i) + ".json";

    // 检查文件是否存在
    if (!fileExists(fileName)) {
      // 创建文件并打开进行写入
      std::ofstream outputFile(fileName);

      // 检查文件是否成功打开
      if (outputFile.is_open()) {
        // 将 JSON 对象转换为字符串并写入文件
        outputFile << vector[i].dump(4); // 使用 4 个空格缩进格式化输出
        outputFile.close();
        std::cout << "Created and saved to " << fileName << std::endl;
      } else {
        std::cerr << "Failed to open file: " << fileName << std::endl;
      }
    } else {
      std::cerr << "File already exists: " << fileName << std::endl;
    }
  }
}

void readFromProc(PROCTAB *proc, proc_t &proc_info) {
  proc = openproc(PROC_FILLMEM | PROC_FILLSTATUS | PROC_FILLUSR);
  memset(&proc_info, 0, sizeof(proc_info));
  while (readproc(proc, &proc_info) != NULL) {
    proc_t tt;
    if (proc_info.cmd == NULL) {
      continue;
    }
    tt = proc_info;
    processes.push_back(tt);
  }
  std::cout << processes.size() << " processes info got." << std::endl;
}

bool fileExists(const std::string &fileName) {
  struct stat buffer;
  return (stat(fileName.c_str(), &buffer) == 0);
}