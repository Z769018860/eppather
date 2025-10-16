// 从test_case读取测试用例并分析
#include "solver.h"
#include "stmt.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>

int main()
{
    std::string src_dir = TEST_SRC_DIR;
    std::filesystem::path dirPath{src_dir};
    if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath)) {
        std::cerr << "error when reading: " << src_dir << std::endl;
        return 1;
    }
    std::ofstream fout("reg_test.txt");
    int error_cnt = 0;
    // 递归遍历子目录
    for (const auto& entry : std::filesystem::recursive_directory_iterator(dirPath)) {
        if (std::filesystem::is_regular_file(entry.status())) {
            if (entry.path().extension() != ".cpath")
                continue;
            try {
                std::cout << "-----" << entry.path().parent_path() << "/"
                          << entry.path().filename() << "-----" << std::endl;
                std::ifstream fin(entry.path());
                std::string ans;
                std::getline(fin, ans);
                if (!ans.empty() && ans[ans.size() - 1] == '\r')
                    ans.erase(ans.size() - 1);
                if (ans.size() < 3)
                    continue;
                ans = ans.substr(3);
                // std::cout << "ans:" << ans << std::endl;
                if ("error" == ans)
                    continue; // 暂不处理语法错误的样例
                auto root = epat::Root::fromStream(fin);
                // std::cout << "log:" << entry.path().filename() << std::endl;
                // std::cout << "code:" << std::endl << root->getCode() << std::endl;
                // std::cout << "ast:" << std::endl << root->getAstString() << std::endl;
                auto solver = epat::Solver::create(std::move(root));
                // std::cout << "mem: " << solver->getMem() << std::endl;
                auto res = solver->feasible();
                // std::cout << "smt:" << std::endl << solver->getSMT2() << std::endl;
                // std::cout << "res: " << res << std::endl;
                // if (result::feasible == res) {
                //     std::cout << "model:" << std::endl << solver->getModel() <<
                //     std::endl;
                // }
                std::ostringstream oss;
                oss << res;
                if (ans != oss.str()) {
                    ++error_cnt;
                    std::cout << "WA"
                              << " " << ans << " " << oss.str() << std::endl;
                    fout << entry.path().filename() << "\tWA"
                         << " " << ans << " " << oss.str() << std::endl;
                }
                else {
                    std::cout << "AC"
                              << " " << ans << std::endl;
                    fout << entry.path().filename() << "\tAC" << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cout << "error occurred when testing " << entry.path().filename()
                          << ": " << e.what() << std::endl;
                return 1;
            }
        }
    }
    return error_cnt;
}
