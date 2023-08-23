#include "./bundle.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>

void usage(char *argv[])
{
    std::cout << "Usage:\n\t"
              << argv[0] << " [operate] [input file] [output file]\n\t"
              << "operate: \n\t\t -z : zip\n\t\t -u : unzip"
              << std::endl;
}

int main(int argc, char *argv[])
{
    using namespace std;
    if (argc != 4 || (string(argv[1]) != "-u" && string(argv[1]) != "-z"))
    {
        usage(argv);
        return -1;
    }

    string inpath = argv[2];
    string outpath = argv[3];

    // 打开输入文件并得到文件大小
    ifstream ifs(inpath, ios::binary); // 流对象析构会自动close
    ifs.seekg(0, std::ios::end);
    auto size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    // 读取文件
    string raw;
    raw.resize(size);
    ifs.read(const_cast<char *>(raw.data()), size);

    // 压缩/解压缩
    string data;
    if (string(argv[1]) == "-z") // 压缩
    {
        data = bundle::pack(bundle::LZIP, raw);
    }
    else // 解压缩
    {
        data = bundle::unpack(raw);
    }

    // 写文件
    ofstream ofs(outpath, ios::binary);
    ofs.write(data.data(), data.size());

    return 0;
}