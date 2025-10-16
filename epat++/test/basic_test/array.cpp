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
    int x;
    int *a = (int*)malloc(x * sizeof(int));
memset(a, 0, x * sizeof(int));
  @ a[1] != 0;
    )";
    struct A {
        int x;
    } a[2];
    a[0].x == -a[1].x&& a[1].x != 0;
    cout << "log: read from string" << endl;
    auto root = Root::fromString(cpath);
    cout << "log: code:" << endl;
    cout << root->getCode() << endl;
    cout << "log: ast:" << endl;
    root->printCode(cout);
    cout << endl;
    // auto solver = Solver::create(move(root));
    cout << "log: solve" << endl;
    // cout << solver->feasible() << endl;
    // epat_debug << ":)" << endl;

    return 0;
}
