cmake_minimum_required(VERSION 3.12)
project(udp_data_compression)

# 查找并包含 nlohmann/json 库，如果你的项目中使用了该库
find_package(nlohmann_json REQUIRED)

# 查找并包含 zlib 库
find_package(ZLIB REQUIRED)

add_executable(sender sender.cpp)
add_executable(receiver receiver.cpp)

# 链接 nlohmann/json 库
target_link_libraries(sender PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(receiver PRIVATE nlohmann_json::nlohmann_json)

# 链接 zlib 库
target_link_libraries(sender PRIVATE ZLIB::ZLIB)
target_link_libraries(receiver PRIVATE ZLIB::ZLIB)

