# 编译器和编译选项
CXX = g++
CXXFLAGS = -std=c++17 -I include -I ~/vcpkg/installed/x64-linux/include
LIBS = -lprocps -lz

# 源文件和目标文件
SRCS = sender.cpp receiver.cpp tools.cpp
TARGETS = output/sender output/receiver

# 默认目标，编译可执行文件
all: $(TARGETS)

output/sender: sender.cpp tools.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

output/receiver: receiver.cpp tools.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# 清除编译生成的文件
clean:
	rm -f $(TARGETS)

