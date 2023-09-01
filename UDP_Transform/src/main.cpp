#include <cstring>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <proc/readproc.h>
#include <vector>
#include <sys/stat.h>

PROCTAB *proc;
proc_t proc_info;
std::vector<proc_t> processes;

void readFromProc(PROCTAB *, proc_t &);
void printToFile(const std::vector<nlohmann::json>&);
bool fileExists(const std::string&);

int main() {
  //     // 创建一个 MyStruct 结构体对象
  //     MyStruct person;
  //     person.name = "John";
  //     person.age = 30;
  //     person.salary = 50000.0;

  //     // 使用 nlohmann/json 库创建一个 JSON 对象并映射结构体字段
  //     nlohmann::json jsonObject;
  //     jsonObject["name"] = person.name;
  //     jsonObject["age"] = person.age;
  //     jsonObject["salary"] = person.salary;

  //     // 将 JSON 对象转换为 JSON 字符串
  //     std::string jsonString = jsonObject.dump();

  //     // 打印 JSON 字符串
  //     std::cout << "JSON Data:\n" << jsonString << std::endl;

  readFromProc(proc, proc_info);

  // 创建一个存储 JSON 数据的数组
  std::vector<nlohmann::json> proc_json;

  for (proc_t &tt : processes) {
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

  printToFile(proc_json);

  return 0;
}

void printToFile(const std::vector<nlohmann::json> &vector) {
    // 目标目录路径
    std::string targetDirectory = "./testfolder/";

    for (size_t i = 0; i < vector.size(); ++i) {
        // 构造文件名，例如 "file1.json", "file2.json", ...
        std::string fileName = targetDirectory + "file" + std::to_string(i) + ".json";

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

bool fileExists(const std::string& fileName) {
    struct stat buffer;
    return (stat(fileName.c_str(), &buffer) == 0);
}