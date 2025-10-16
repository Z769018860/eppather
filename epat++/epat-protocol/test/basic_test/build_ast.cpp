// 测试语法树搭建，以及对象的创建与析构
#include "stmt.h"
#include <iostream>
#include <vector>

using namespace epat;
using namespace std;

int main()
{
    return 0;
    // create
    auto proot = Root::create();
    auto& root = *proot;
    auto int_type = BaseType::getInt();
    *proot << VarDecl::create("tmp", int_type, IntLiteral::create(1))
           << SignStmt::create(DeclRefExpr::create(proot->getValueDecl("tmp")));
    auto ary_type = ArrayType::create(int_type, 10);
    root << VarDecl::create("a", ary_type);
    root << VarDecl::create("b", int_type);
    root << VarDecl::create("c", int_type);
    auto structA = StructDecl::create("A");
    root << structA;
    structA->addField(FieldDecl::create("a", int_type, structA.get()));
    root << ArraySubscript::create(DeclRefExpr::create(root.getValueDecl("a")),
                                   IntLiteral::create(1));
    root << BinaryOperator::create(DeclRefExpr::create(root.getValueDecl("b")),
                                   DeclRefExpr::create(root.getValueDecl("c")), "+");
    root << BreakStmt::create();
    auto f = FunctionDecl::create("f", int_type, ParmVarDecl::list());
    root << f;
    *f << ParmVarDecl::create("a", int_type);
    f->getBody() << SignStmt::create(DeclRefExpr::create(f->getValueDecl("a")));
    Expr::list operands;
    operands.push_back(IntLiteral::create(123));
    root << CallExpr::create(f, move(operands));
    root << ContinueStmt::create();
    // TODO: init cond loop body
    auto for_stmt = ForStmt::create();
    root << move(for_stmt);
    root << IfStmt::create(IntLiteral::create(1), {}, {});
    root << ChrLiteral::create('2');
    root << VarDecl::create("sa", StructType::create(structA));
    root << MemberExpr::create(DeclRefExpr::create(root.getValueDecl("sa")), "a");
    root << ReturnStmt::create(IntLiteral::create(0));
    root << SignStmt::create(IntLiteral::create(1));
    root << UnaryOperator::create(IntLiteral::create(10), "!");
    root << WhileStmt::create(IntLiteral::create(0), {});

    // print ast and code.
    cout << "ast:" << endl;
    root.printAst(cout);
    cout << endl << "code:" << endl;
    root.printCode(cout);

    // delete? no, thanks. :)

    return 0;
}
