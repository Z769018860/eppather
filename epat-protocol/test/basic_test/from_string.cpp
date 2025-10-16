#include "reader.h"
#include <string>

int main()
{
    std::string input = R"(
int a;
)";
    epat::Reader parser(input);
    auto root = parser.getRoot();
    std::cout << "code:" << std::endl;
    root->printCode();
    std::cout << "ast:" << std::endl;
    root->printAst();

    return 0;
}
