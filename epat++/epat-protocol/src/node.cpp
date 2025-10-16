#include "node.h"
#include "writer.h"
#include <sstream>

using namespace std;

epat::Node::Node() {}

void epat::Node::printAst(std::ostream& os, const std::string& prefix) const
{
    os << prefix << "$Node";
}

void epat::Node::printCode(std::ostream& os, int indent) const
{
    os << SPACES << "$Node";
}

// std::string epat::Node::buildAstString(
//     const list children, std::string parent, std::string prefix
// )
// {
//     ostringstream oss;
//     oss << prefix << parent;
//     // "|-"->"| ". "`-"->"  "
//     if (auto len = prefix.size(); len > 1) {
//         prefix[len - 1] = ' ';
//         if (prefix[len - 2] == '`')
//             prefix[len - 2] = ' ';
//     }
//     auto new_prefix = prefix + "|-";
//     for (int i = 0, n = (int)children.size(); i != n; ++i) {
//         if (i == n - 1)
//             new_prefix[new_prefix.size() - 2] = '`';
//         oss << endl;
//         if (auto& c = children[i])
//             oss << children[i]->getAstString(new_prefix);
//         else
//             oss << new_prefix << "<<NULL>>";
//     }
//     return oss.str();
// }

// std::string epat::Node::getAstString(std::string prefix) const
// {
//     return prefix + "Node";
// }

// std::string epat::Node::getCode(int indent) const
// {
//     return string(indent, ' ') + "$Node";
// }
