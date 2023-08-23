#include <iostream>
#include <jsoncpp/json/config.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <memory>
#include <string>

int main()
{
    std::string s = R"(
{
    "name":"cjj",
    "age":18,
    "sorce":[123, 333, 122]
}
)";

    Json::CharReaderBuilder crb;
    std::unique_ptr<Json::CharReader> cr(crb.newCharReader());

    Json::Value root;
    Json::String errs;

    bool ret = cr->parse(s.data(), s.data() + s.size(), &root, &errs);
    if (ret == false)
    {
        std::cout << errs << std::endl;
        return -1;
    }

    std::cout << root["name"].asString() << std::endl;
    std::cout << root["age"].asInt() << std::endl;
    for (int i = 0; i < root["sorce"].size(); i++)
    {
        std::cout << root["sorce"][i].asFloat() << std::endl;
    }

    return 0;
}