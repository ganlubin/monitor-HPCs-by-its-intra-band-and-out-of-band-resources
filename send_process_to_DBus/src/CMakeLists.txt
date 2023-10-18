cmake_minimum_required(VERSION 2.6.3)
project(DBusTest)
set(CMAKE_CXX_STANDARD 17)

# 添加第一个可执行文件
add_executable(proc_getter proc_getter.cpp) # 替换为你的源文件名
target_link_libraries(proc_getter PRIVATE systemd procps)

# 添加第二个可执行文件
add_executable(send_process_to_DBus send_process_to_DBus.cpp) # 替换为你的源文件名
target_link_libraries(send_process_to_DBus PRIVATE systemd procps)

