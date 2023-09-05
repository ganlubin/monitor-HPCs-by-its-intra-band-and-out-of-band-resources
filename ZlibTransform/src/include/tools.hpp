// tools.hpp
// author: sokee
// date: 5-9-2023
#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <proc/readproc.h>
#include <vector>
#include <zlib.h>
#include <netinet/in.h>
#include <unistd.h>

/*
    put str into file:Addr
    type: a for adding, w for overwriting
*/
bool saveToFile(const std::string &str, const std::string &Addr, char type);
std::vector<proc_t> readFromProc();
std::vector<nlohmann::json> pushToVector(const std::vector<proc_t> &processes);

bool sendZlibByUDP(std::vector<Bytef> compressedData, uLong destLen, uint32_t __hostlong, unsigned int port);

#endif
