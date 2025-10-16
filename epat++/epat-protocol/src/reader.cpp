#include "reader.h"
#include "CLexer.h"
#include "CParser.h"
#include "type_helper.h"
#include <sstream>

using namespace epat;
using namespace std;

std::pair<Root::ptr, bool> parseFromStream(std::istream& in)
{
    antlr4::ANTLRInputStream input(in);
    CLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CParser parser(&tokens);
    auto cu = parser.compilationUnit();

    // for debug
    // cout << cu->getText() << endl;

    // TODO: parser错误处理
    return {std::move(parser.root_), true};
}

epat::Reader::Reader(std::istream& in)
{
    std::tie(root, valid) = parseFromStream(in);
}

epat::Reader::Reader(const std::string& in)
{
    istringstream _in(in);
    std::tie(root, valid) = parseFromStream(_in);
}

Root::ptr epat::Reader::getRoot()
{
    return move(root);
}
