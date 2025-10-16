// test basic_solver
#include "debug.h"
#include "reader.h"
// #include "solver.h"
#include <set>

using namespace std;
using namespace epat;

int main()
{
    std::string cpath = R"(
struct A { int x; };
struct A b;
struct A* a = &b;
int y;

a->x = 1;
@(b.x == y);
)";
    cout << "log: read from string" << endl;
    auto root = Root::fromString(cpath);
    // auto solver = Solver::create(move(root));
    // cout << solver->feasible() << endl;
    // cout << "model:" << endl;
    // cout << solver->getModel() << endl;

    return 0;
}
