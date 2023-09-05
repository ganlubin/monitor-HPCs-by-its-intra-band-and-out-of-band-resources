# 编译器
CXX = g++
# 编译选项，包括C++17支持和zlib库链接
CXXFLAGS = -std=c++17 -I ~/vcpkg/installed/x64-linux/include

LDFLAGS = -lz

# 目标文件列表
TARGETS = sender receiver

all: $(TARGETS)

# sender.cpp编译为sender可执行文件
sender: sender.cpp
	$(CXX) $(CXXFLAGS) -o sender sender.cpp $(LDFLAGS)

# receiver.cpp编译为receiver可执行文件
receiver: receiver.cpp
	$(CXX) $(CXXFLAGS) -o receiver receiver.cpp $(LDFLAGS)

clean:
	rm -f $(TARGETS)

