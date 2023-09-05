#include "myFile.hpp"
#include <iostream>
#include <cstring>
#include <fstream>


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

        file << str; // 写入字符串
        file.close(); // 关闭文件

        return true;
    } catch (const std::exception &e) {
        std::cerr << "保存文件时发生异常: " << e.what() << std::endl;
        return false;
    }
}
