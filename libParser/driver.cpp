#include "driver.h"
#include "parser.h"
#include "scanner.h"
#include "solver.h"
#include "debug.h"
#include "expression.h"

#include "location.hh"

#include <sstream>
#include <fstream>

using namespace std;

void tool::Driver::setQualType(const QualType& qt)
{
    this->qt = qt;
}

QualType& tool::Driver::getQualType()
{
    return qt;
}

void tool::Driver::reset()
{
    analyzed = parsed = false;
    // path_type = 0;
    source_name = "no source";
    lexer = nullptr;
    qt = QualType();
    while (!ctxs.empty()) {
        if (ctxs.back())
            delete ctxs.back();
        ctxs.pop_back();
    }

    auto global = new Context();
    BuildInType::get(global, "void", 0);
    BuildInType::get(global, "int");
    BuildInType::get(global, "char");
    // TODO: 目前不支持
    BuildInType::get(global, "float");

    // FunctionDecl::create(global, "scanf", global->getVoidType());
    VarDecl::create(global, "%av", QualType(global->getIntType()) * 0, nullptr);
    ctxs.push_back(global);
}

tool::Driver::Driver()
  : res(tool::result::unknown),
    qt(*new QualType()),
    trace_parsing (false), trace_scanning (false),
    location(*new tool::location())
{
}

tool::Driver::~Driver()
{
    if (solver) delete solver;
    delete &qt;
    for (auto ii = ctxs.rbegin(), ie = ctxs.rend(); ii != ie; ++ii) {
        auto c = *ii;
        if (c)
            delete c;
    }
    delete &location;
}

void tool::Driver::push(Context* ctx)
{
    ctxs.push_back(ctx);
}

void tool::Driver::pop()
{
    ctxs.pop_back();
}

void tool::Driver::pushAST(Node* node) {
    getContext()->ASTs.push_back(node);
}

void tool::Driver::printAST()
{
    getContext()->ASTs.front()->print(cout);
}

void tool::Driver::printAST(ostream& os)
{
    getContext()->ASTs.front()->print(os);
}

void tool::Driver::printCode()
{
    getContext()->ASTs.front()->printCode(cout);
}

void tool::Driver::printCode(std::ostream& os)
{
    getContext()->ASTs.front()->printCode(os);
}

bool tool::Driver::feasible()
{
    //auto _ctx = z3::context();
    //auto _solver = z3::solver(_ctx);
    //auto a = _ctx.real_const("a"),
    //	b = _ctx.real_const("b"),
    //	c = _ctx.real_const("c");
    //_solver.add(a / (b + c) + b / (a + c) + c / (a + b) == 1);
    //_solver.add(b + c != 0);
    //_solver.add(a + c != 0);
    //_solver.add(a + b != 0);
    //auto _res = _solver.check();
    //if (_res == z3::check_result::sat) {
    //	cout << "right" << std::endl;
    //	cout << _solver.get_model() << std::endl;
    //}
    //return false;
    // cout << "进入driver::feasible" << std::endl;
    if (!parsed) {
        cout << "请先设定输入流。" << std::endl;
        return false;
    }
    if (analyzed) {
        cout << "已经分析过了？" << std::endl;
        return false;
    }
    if (solver)
        delete solver;
    solver = new Solver(*getContext());
    res = solver->feasible();
    analyzed = true;
    return res == result::feasible;
}

int tool::Driver::feasible(std::istream& in, const std::string& in_name)
{
    if (!parseStream(in, in_name))
        return feasible();
    return -1;
}

int tool::Driver::feasible(const std::string& in, const std::string& in_name)
{
    if (!parseString(in, in_name))
        return feasible();
    return -1;
}

/*
int tool::Driver::feasible(const std::string& file_name)
{
    if (parseFile(file_name))
        return feasible();
    return -1;
}
*/

int tool::Driver::parseStream(istream& in, const string& in_name)
{
    reset();

    source_name = in_name;
    Scanner scanner(&in);
    scanner.set_debug(trace_scanning);
    lexer = &scanner;

    Parser parser(*this);
    parser.set_debug_level(trace_parsing);

    int res = 1;
    try {
        res = parser.parse();
    }
    catch (exception& e) {
        cout << e.what() << std::endl;
    }
    catch (...) {
        cout << "解析出现未知错误:(" << std::endl;
    }

    if (res)
        cout << "解析\"" << in_name << "\"时出错！" << std::endl;
    else {
        cout << "路径解析完成，路径为C" << getContext()->getPathType() << std::endl;
        parsed = true;
    }

    return res;
}

int tool::Driver::parseString(const string& in, const string& in_name)
{
    istringstream iss(in);
    return parseStream(iss, in_name);
}

int tool::Driver::parseFile(const string& file_name)
{
    ifstream in(file_name.c_str());
    if (!in.good()) {
        cout << "无法打开文件" << file_name << "!" << std::endl;
        return 99;
    }
    return parseStream(in, file_name);
}

void tool::Driver::printModel(std::ostream& os)
{
    os << getModel() << std::endl;
}

std::string tool::Driver::getModel()
{
    if (!analyzed) {
        cout << "在获取模型前请先调用feasible" << std::endl;
        return ":(";
    }
    return solver->getModel();
}

void tool::Driver::printSMT2(std::ostream& os)
{
    os << getSMT2() << std::endl;
}

std::string tool::Driver::getSMT2()
{
    if (!analyzed) {
        cout << "在获取SMT2前请先调用feasible" << std::endl;
        return ":(";
    }
    return solver->getSMT2();
}

void tool::Driver::printMem(std::ostream& os)
{
    os << getMem() << std::endl;
}

int tool::Driver::getMem()
{
    if (!analyzed) {
        cout << "在获取mem前请先调用feasible" << std::endl;
        return 0;
    }
    return solver->getMem();
}
