#include <iostream>
#include <proc/readproc.h>
#include <stdio.h>
#include <string.h>
#include <typeinfo>

int main() {
  PROCTAB *proc = openproc(PROC_FILLMEM | PROC_FILLSTAT); // 打开进程表

  proc_t proc_info; // 用于存储进程信息的结构体
  memset(&proc_info, 0, sizeof(proc_info));
  while (readproc(proc, &proc_info) != NULL) { // 读取进程信息，直到没有更多进程
    if (proc_info.cmd == NULL) {
      continue;
    }
    std::cout << proc_info.state << std::endl;
  }
  std::cout << "Over" << std::endl;
  closeproc(proc); // 关闭进程表
  return 0;
}