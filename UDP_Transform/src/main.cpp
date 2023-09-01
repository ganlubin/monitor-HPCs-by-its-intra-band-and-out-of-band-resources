#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// 定义一个示例的结构体
struct MyStruct {
    std::string name;
    int age;
    double salary;
};

int main() {
    // 创建一个 MyStruct 结构体对象
    MyStruct person;
    person.name = "John";
    person.age = 30;
    person.salary = 50000.0;

    // 使用 nlohmann/json 库创建一个 JSON 对象并映射结构体字段
    json jsonObject;
    jsonObject["name"] = person.name;
    jsonObject["age"] = person.age;
    jsonObject["salary"] = person.salary;

    // 将 JSON 对象转换为 JSON 字符串
    std::string jsonString = jsonObject.dump();

    // 打印 JSON 字符串
    std::cout << "JSON Data:\n" << jsonString << std::endl;

    return 0;
}
