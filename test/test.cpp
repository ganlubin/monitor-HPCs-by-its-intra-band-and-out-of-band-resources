#include <iostream>
#include <proc/readproc.h>
#include <cstring>

int main() {
    PROCTAB* proc = openproc(PROC_FILLMEM | PROC_FILLSTAT);  // 打开进程表

    proc_t proc_info;  // 用于存储进程信息的结构体
    memset(&proc_info, 0, sizeof(proc_info));
    while (readproc(proc, &proc_info) != NULL) {  // 读取进程信息，直到没有更多进程
        if (proc_info.cmd == nullptr) continue;
        std::cout << "Process ID: " << proc_info.tid << std::endl;  // 打印进程ID
        std::cout << "Process Name: " << proc_info.cmd << std::endl;  // 打印进程名称
        std::cout << "Process State: " << proc_info.state << std::endl;  // 打印进程状态
        std::cout << "Process Resident Set Size: " << proc_info.rss << std::endl;  // 打印进程的驻留集大小
        std::cout << "------------------------------" << std::endl;
    }
    
    closeproc(proc);  // 关闭进程表
    return 0;
}