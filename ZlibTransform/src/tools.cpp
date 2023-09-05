#include "include/tools.hpp"

bool saveToFile(const std::string &str, const std::string &Addr, char type) {
  try {
    std::ofstream file;
    if (type == 'a' || type == 'A') {
      // 以追加模式打开文件，如果文件不存在则创建
      file.open(Addr, std::ios::out | std::ios::app);
    } else if (type == 'w' || type == 'W') {
      // 以覆盖模式打开文件，如果文件不存在则创建
      file.open(Addr, std::ios::out);
    } else {
      // 无效的模式
      std::cerr << "无效的文件写入模式: " << type << std::endl;
      return false;
    }

    if (!file.is_open()) {
      std::cerr << "无法打开文件: " << Addr << std::endl;
      return false;
    }

    file << str;  // 写入字符串
    file.close(); // 关闭文件

    return true;
  } catch (const std::exception &e) {
    std::cerr << "保存文件时发生异常: " << e.what() << std::endl;
    return false;
  }
}

std::vector<proc_t> readFromProc() {
  PROCTAB *proc = nullptr;
  proc_t proc_info;
  std::vector<proc_t> processes;
  processes.clear();
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
  return processes;
}

std::vector<nlohmann::json> pushToVector(const std::vector<proc_t> &processes) {
  std::vector<nlohmann::json> proc_json;
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
  return proc_json;
}

bool sendZlibByUDP(std::vector<Bytef> compressedData, uLong destLen, uint32_t __hostlong, unsigned int port) {
  // 设置接收端地址和端口号
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = htonl(__hostlong);

  // 创建 UDP 套接字
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1) {
    std::cerr << "Failed to create socket" << std::endl;
    return 0;
  }

  // 发送压缩后的数据
  ssize_t sentBytes =
      sendto(sock, compressedData.data(), destLen, 0,
             (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  if (sentBytes == -1) {
    std::cerr << "Failed to send data" << std::endl;
    close(sock);
    return 0;
  }

  close(sock);
  return 1;
}