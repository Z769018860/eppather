#include "c1_solver.h"
#include "memory_model.h"
#include "my_stack.h"
#include "solver.h"
#include "stmt.h"
#include <iostream>

using namespace epat;

void solve()
{
    std::string in = R"(
// feasible
int a[5];
int n;
int m;
int i=0;
int temp;
m==(n+1)/2;
i;
@(i<m);
i=i+1;
i;
int j;
j=n-1-i;
temp=a[i];
a[i]=a[j];
a[j]=temp;
)";
    auto root = Root::fromString(in);
    std::cout << "code:" << std::endl << root->getCode() << std::endl;
    // std::cout << "ast:" << std::endl << root->getAstString() << std::endl;
    auto solver = Solver::create(std::move(root));
    std::cout << "mem: " << solver->getMem() << std::endl;
    auto res = solver->feasible();
    // std::cout << "smt:" << std::endl << solver->getSMT2() << std::endl;
    std::cout << "res: " << res << std::endl;
    if (result::feasible == res) {
        std::cout << "model:" << std::endl << solver->getModel() << std::endl;
    }
}

int main()
{
    try {
        solve();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    // epat::MyStack<int> s;
    // try {
    //     s.pop();
    // }
    // catch (std::exception& e) {
    //     std::cout << e.what() << std::endl;
    // }
    // std::cout << ":)" << std::endl;

    // auto lm = epat::LinearMemory();
    // std::cout << lm.array_.operator bool() << std::endl;

    // z3::solver s(gc);
    // auto a = gc.int_const("a"), b = gc.int_const("b");
    // s.add(a * a > 2);
    // std::cout << s << std::endl;

    // auto root = Root::create();
    // root << VarDecl::create("a", BaseType::getInt());
    // auto blk = Block::create(root.get());
    // auto pblk = blk.get();
    // root << std::move(blk);
    // *pblk << VarDecl::create("a", BaseType::getInt());
    // std::cout << root->getCode() << std::endl;
    // // auto lm = LinearMemory();
    // auto slv = C1Solver<LinearMemoryLValue>();
    // std::cout << slv.getUniqueName(*pblk->getValueDecl("a")) << std::endl
    //           << slv.getUniqueName(*root->getValueDecl("a")) << std::endl
    //           << slv.getUniqueName(*pblk->getValueDecl("a")) << std::endl
    //           << slv.getUniqueName(*root->getValueDecl("a")) << std::endl;

    // auto lm = epat::LinearMemory();
    // auto a0 = lm.alloc(epat::_1);
    // auto a1 = lm.alloc(epat::gc.int_const("a") * 0);
    // auto a2 = lm.alloc(epat::_1);
    // auto a3 = lm.alloc(epat::gc.int_const("a"));
    // auto a4 = lm.alloc(epat::_1);
    // // std::cout << lm->hello_world() << std::endl;

    // std::cout << a0 << std::endl
    //           << a1 << std::endl
    //           << a2 << std::endl
    //           << a3 << std::endl
    //           << a4 << std::endl;

    // for (auto& a : {a0, a1, a2, a3, a4})
    //     std::cout << a.simplify() << "\t" << a.simplify().id() << std::endl;

    return 0;
}
