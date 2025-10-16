// 从test_case读取测试用例并分析
#include "stmt.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>

int main(int argc, char* argv[])
{
    std::string input_dir, output_file;
    if (argc < 3) {
        std::cout << "use default test cases." << std::endl;
        input_dir = "D:\\Projects\\epat++\\test\\test_case";
    }
    else {
        input_dir = argv[1];
    }
    std::filesystem::path dirPath{input_dir};
    if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath)) {
        std::cerr << "error when reading: " << input_dir << std::endl;
        return 1;
    }
    for (const auto& entry : std::filesystem::recursive_directory_iterator(dirPath)) {
        if (std::filesystem::is_regular_file(entry.status())) {
            if (entry.path().extension() != ".cpath")
                continue;
            try {
                std::ifstream fin(entry.path());
                char buffer[1024];
                fin.getline(buffer, 1024);
                auto str = std::string(buffer);
                std::cout << str << std::endl;
                if (std::string(buffer) == "// error")
                    continue;
                auto root = epat::Root::fromStream(fin);
                std::cout << "log:" << entry.path().filename() << std::endl;
                root->printCode(std::cout);
                std::cout << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "error occurred when testing " << entry.path().filename()
                          << ": " << e.what() << std::endl;
                return 1;
            }
        }
    }

    return 0;
}
