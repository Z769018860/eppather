// 从文件中读取C或CPath代码，解析成语法树，并打印相应信息
#include "stmt.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>

// 主函数
int main(int argc, char* argv[])
{
    // if (argc != 3) {
    //     std::cout << "Usage: " << argv[0] << " input_dir output_file" << std::endl;
    //     return 1;
    // }
    std::string input_dir, output_file;
    if (argc < 3) {
        std::cout << "the path of dataset is not passed. use default dataset."
                  << std::endl;
        input_dir = "C:/Projects/epat++/epat-protocol/test/leetcode";
        output_file = "C:/Projects/epat++/epat-protocol/test/1.out";
    }
    else {
        input_dir = argv[1];
        output_file = argv[2];
        // std::ofstream of("C:/Projects/epat++/epat-protocol/test/1.out");
        // of << input_dir << std::endl;
        // of << output_file << std::endl;
        // return 0; // XXX: 崩溃
    }
    for (const auto& file : std::filesystem::directory_iterator(input_dir)) {
        static std::set<std::filesystem::path> exts = {".c"};
        auto& path = file.path();
        if (exts.find(path.extension()) == exts.end()) {
            continue;
        }
        std::cout << "read: " << path << std::endl;
        try {
            std::ifstream fin;
            fin.open(path);
            auto root = epat::Root::fromStream(fin);
            std::cout << "log: code:" << std::endl;
            root->printCode(std::cout);
            std::cout << std::endl;
            // std::cout << "log: ast:" << std::endl;
            // root->printAst(std::cout);
            // std::cout << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
            return 1;
        }
    }
    return 0;
}
