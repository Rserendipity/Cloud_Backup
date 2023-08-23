#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

int main()
{
    // 需要序列化的信息
    const char *name = "xiaoming";
    int age = 18;
    float score[] = {77.5, 88, 123};

    // 将数据保存在Value中
    Json::Value root;
    root["name"] = name;
    root["age"] = age;
    for (auto f : score)
    {
        root["score"].append(f);
    }

    // 将数据写入到stringstream里
    Json::StreamWriterBuilder swb;
    std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());

    std::stringstream ss;
    sw->write(root, &ss);

    std::cout << ss.str() << std::endl;

    return 0;
}