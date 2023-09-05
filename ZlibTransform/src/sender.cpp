#include <iostream>
#include <zlib.h>
#include "include/tools.hpp"
#include <proc/readproc.h>

std::vector<proc_t> procs;
std::vector<nlohmann::json> jsonVector;

int main() {
    procs = readFromProc();
    jsonVector = pushToVector(procs);

    std::string json_str = nlohmann::json(jsonVector).dump();

    // 压缩数据
    uLong sourceLen = json_str.length();
    uLong destLen = compressBound(sourceLen);
    std::vector<Bytef> compressedData(destLen);
    if (compress(&compressedData[0], &destLen, (const Bytef*)json_str.c_str(), sourceLen) != Z_OK) {
        std::cerr << "Compression failed" << std::endl;
        return 1;
    }

    std::cout << destLen << std::endl;

    sendZlibByUDP(compressedData, destLen, INADDR_LOOPBACK, 12345);

    return 0;

}