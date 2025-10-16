// 测试类型的打印
#include "type.h"
#include <iostream>
#include <vector>

using namespace epat;
using namespace std;

int main()
{
    int res = 0;
    auto int_type = BaseType::getInt();
    int_type->printCode(std::cout);
    std::cout << std::endl;
    res += "int" != int_type->getCode();
    auto pint = PointerType::create(int_type);
    pint->printCode(std::cout);
    std::cout << std::endl;
    res += "int *" != pint->getCode();
    auto ppint = PointerType::create(pint);
    ppint->printCode(std::cout);
    std::cout << std::endl;
    res += "int **" != ppint->getCode();
    // auto int_10 = ArrayType::create(int_type, 10);
    // res += "int[10]" != int_10->getCode();

    return res;
}
