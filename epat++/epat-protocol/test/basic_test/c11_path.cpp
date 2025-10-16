// 测试c11path
#include "reader.h"
#include <iostream>
#include <vector>

using namespace epat;
using namespace std;

int main()
{
    std::string input = R"(
struct A {int a;} a;
int b = a.a;
)";
    epat::Reader reader(input);
    if (reader.isValid()) {
        auto path = reader.getRoot();
        std::cout << "code" << std::endl;
        std::cout << path->getCode() << std::endl;
        std::cout << "ast:" << std::endl;
        std::cout << path->getAstString() << std::endl;
    }
    else {
        std::cout << "invalid path!" << std::endl;
    }
    return 0;
}
