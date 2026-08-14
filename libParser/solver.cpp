#include <ostream>
#include <ranges>
#include <cstdint>
#include <limits>
#include <regex>
#include <sstream>

#include "debug.h"
#include "exception.h"
#include "expression.h"
#include "solver.h"

#include "z3++.h"

using namespace z3;
using namespace std;
using namespace tool;

using lvalue = Solver::lvalue;
using rvalue = Solver::rvalue;

tool::Solver::Table::Table(Solver& parent)
    : parent(parent), ctx(parent.getZ3Context()),
    empty(parent.empty), solver(parent.getZ3Solver()),
    node(nullptr), left(-1), right(-1), now(-1),
    memory({ { nullptr, { empty } } })
{
    solver.push();
    check();
}

tool::Solver::Table::Table(const Table& table, Solver& parent)
    : Table(parent)
{
    index = table.index + 1;
    visited = table.visited;
    visiting = table.visiting;
}

tool::Solver::Table::~Table()
{
    //if (node) {
    //    auto vard = parent.getLValue(node->getBase()).vard;
    //    parent.unmapExpr(vard, node->getSubscript(), now);
    //}
    // delete& solver;
    solver.pop();
}

bool tool::Solver::Table::operator==(const Table& other) const
{
    return this == &other;
}

void tool::Solver::Table::check()
{
    auto ret = solver.check();
    parent.m_smt2 = solver.to_smt2();
    if (ret == z3::sat)
        parent.m_model = solver.get_model();
    else
        parent.m_model = model(ctx);
    if (ret == z3::unsat)
        throw feasibility_exception(result::infeasible);
    else if (ret == z3::unknown)
        throw base_expception("未知原因的错误：求解器给出\"unknown\"的结果 :(");
}

void tool::Solver::Table::print(std::ostream& os)
{
    if (!_debug) return;
    os << std::endl << "-----memory-----" << std::endl;
    for (auto& entry : memory) {
        const auto& [vard, ary] = entry;
        if (!vard)
            continue;
        os << vard->getName() << " :";
        for (const auto& v : ary)
            os << " " << v;
        os << endl;
    }
    os << "-----rexpr-----" << std::endl;
    for (const auto& [e, rv] : rvs)
        cout << *e << " : " << rv << std::endl;
}

bool tool::Solver::Table::isVisited(Node* node)
{
    return visited.find(node) != visited.end();
}

void tool::Solver::Table::setBacktrackingPoint(ArraySubscriptExpr* e, int l, int r)
{
    if (node) {
        debug << "setBacktrackPoint时已有node" << tool::endL;
        return;
    }
    node = e;
    now = left = l;
    right = r;
    if (now >= right)
        throw feasibility_exception(result::infeasible);
}

int tool::Solver::Table::getPos() const
{
//    return parent.m_using_sparse_array ? now - left : now;
    return now;
}

void tool::Solver::Table::step()
{
    auto [vard, _] = parent.getLValue(node->getBase());
    auto SS = node->getSubscript();
    auto [next, can] = parent.stepExpr(vard, SS, now);
    if (!can)
        throw feasibility_exception(result::infeasible);
    if (next >= right) // 用不用稀疏数组都一样
        throw feasibility_exception(result::infeasible);
    debug << "迭代节点："
        << "(" << node->getCode() << ")"
        << " = " << next << tool::endL;
    auto e = parent.mapping[vard].contents[now].front();
    addCond(parent.getRValue(SS) != parent.getRValue(e));
    now = next;
}

void tool::Solver::Table::addCond(const z3::expr& cond)
{
    debug << "加入一个条件：" << cond << tool::endL;
    solver.add(cond);
    check();
}

inline string generateValueName(VarDecl *vard, int idx)
{
    return vard->getName() + "@" + to_string(idx);
}

void tool::Solver::Table::alloc(VarDecl* vd, Expr* init)
{
    if (memory.find(vd) != memory.end()) {
        cout << "重复分配？" << endl;
        return;
    }
    // TODO: 仅在使用稀疏数组且VarDecl是数组时，不初始化
    if (parent.usingSparseArray() && vd->getType().isArray())
        return;
    auto& mem = memory[vd];
    int ll = vd->getType().getSize(), lr = 1;
    int len = 1, i = 0;
    // 多值初始化
    if (auto str = dynamic_cast<StrLiteral*>(init)) {
        const auto& v = str->getValue();
        lr = (int)v.size();
        len = min(ll, lr);
        for (; i < len; ++i)
            mem.emplace_back(ctx.int_val(v[i]));
    }
    else if (auto il = dynamic_cast<InitListExpr*>(init)) {
        lr = il->getLenth();
        len = min(ll, lr);
        for (; i < len; ++i)
            mem.emplace_back(getRValue(il->at(i)));
    }
    else if (init) {
        mem.emplace_back(parent.getRValue(init));
        ++i;
    }
    for (; i < ll; ++i)
        mem.emplace_back(ctx.int_const(generateValueName(vd, i).c_str()));
    // print();
}

void tool::Solver::Table::extend(VarDecl* vard)
{
    copyFromPrev(vard);
    auto& mem = memory[vard];
    mem.emplace_back(ctx.int_const(generateValueName(vard, (int)mem.size()).c_str()));
}

void tool::Solver::Table::assign(const lvalue& lv, const rvalue& rv)
{
    const auto& [vard, pos] = lv;
    copyFromPrev(vard);
    if (!vard)
        return;
    // if (!parent.usingSparseArray())
    memory[vard][pos] = rv;
    // parent.printTables(cout);
}

rvalue tool::Solver::Table::getMemory(const lvalue& lv) const
{
    const auto& [vard, pos] = lv;
    auto i = memory.find(vard);
    if (i == memory.end())
        return empty;
    auto& values = i->second;
    if (pos >= values.size())
        return empty;
    return values[pos];
}

void tool::Solver::Table::setLValue(Expr* e, const lvalue& v)
{
    lvs[e] = v;
}

void tool::Solver::Table::setRValue(Expr* e, const rvalue& v)
{
    rvs.insert_or_assign(e, v);
    // rvs[e] = v;
}

lvalue tool::Solver::Table::getLValue(Expr* e) const
{
    auto i = lvs.find(e);
    if (i == lvs.end())
        return { nullptr, 0 };
    return i->second;
}

rvalue tool::Solver::Table::getRValue(Expr* e) const
{
    auto i = rvs.find(e);
    if (i == rvs.end())
        return empty;
    return i->second;
}

void tool::Solver::Table::copyFromPrev(VarDecl* vard)
{
    for (int i = index; i >= 0; --i) {
        auto t = parent.tables[i];
        if (t->memory.find(vard) != t->memory.end()) {
            if (i != index)
                memory[vard] = t->memory[vard];
            break;
        }
    }
}

inline int str2int(const std::string& str)
{
    stringstream ss(str);
    int ret = 0;
    return ss >> ret, ret;
}

std::pair<int, bool> tool::Solver::mapExpr(VarDecl* vard, Expr* e)
{
    auto& [cache, contents, constants] = mapping[vard];
    int pos = 0;
    if (e->isConstant()) {
        int ev = e->getConstantValue();
        auto ii = cache.find(ev);
        if (ii != cache.end()) // 和已缓存值相等
            return { ii->second, false };
        // 否则确定其缓存的值
        for (; constants.find(pos) != constants.end(); ++pos);
        // 找到合适的值
        cache[ev] = pos;
        constants.insert(pos);
    }
    extendMappingTableTo(vard, pos + 1);
    contents[pos].emplace_back(e);
    return { pos, true };
}

//void tool::Solver::unmapExpr(VarDecl* vard, Expr* e, int now)
//{
//    auto& [cache, contents, constants] = mapping[vard];
//    auto& t_now = contents[now];
//    if (t_now.back() != e) {
//        cout << "unmapExpr时：\"" << *e << "\"不是表尾项" << endl;
//        return;
//    }
//    if (e->isConstant()) {
//        int ev = e->getConstantValue();
//        cache.erase(ev);
//        constants.erase(ev);
//    }
//    t_now.pop_back();
//}

void tool::Solver::extendMappingTableTo(VarDecl* vard, int size)
{
    auto& [cache, contents, _] = mapping[vard];
    while (contents.size() < size) {
        contents.emplace_back();
        extend(vard);
    }
}

std::pair<int, bool> tool::Solver::stepExpr(VarDecl* vard, Expr* e, int now)
{
    // 返回true表示未遇到问题
    auto& [cache, contents, constants] = mapping[vard];
    auto& t_now = contents[now];
    if (t_now.back() != e) {
        cout << "stepExpr时：\"" << *e << "\"不是表尾项" << endl;
        return { now, false };
    }
    t_now.pop_back();
    if (t_now.empty()) {
        if (e->isConstant()) {
            int ev = e->getConstantValue();
            cache.erase(ev);
            constants.erase(now);
        }
        // 依赖连续性
        contents.pop_back();
        return { now, false };
    }
    int next = now + 1;
    if (e->isConstant()) { // 确定next
        int ev = e->getConstantValue();
        for (; constants.find(next) != constants.end(); ++next);
        // 找到合适的值
        cache[ev] = next;
        constants.erase(now);
        constants.emplace(next);
    }
    extendMappingTableTo(vard, next + 1);
    contents[next].emplace_back(e);
    return { next, true };
}

void tool::Solver::restoreVarName()
{
    if (m_restored)
        return;
    m_model_str = m_model.to_string();
    restoreVarName(m_model_str);
    // Z3 renders 32-bit bit-vectors as unsigned decimals, while Epat declares
    // them as C `int`.  Preserve the bit pattern but emit a valid signed C
    // literal so concrete replay cannot silently take a different branch.
    {
        regex assignment(R"((\bint\s+[A-Za-z_][A-Za-z_0-9]*(?:\[[0-9]+\])?\s*=\s*)([0-9]+)(\b))");
        string normalized, remaining = m_model_str;
        smatch match;
        while (regex_search(remaining, match, assignment)) {
            normalized += match.prefix().str() + match[1].str();
            try {
                const auto raw = stoull(match[2].str());
                if (raw <= numeric_limits<uint32_t>::max()) {
                    const auto signedValue = raw <= static_cast<uint64_t>(numeric_limits<int32_t>::max())
                        ? static_cast<int64_t>(raw)
                        : static_cast<int64_t>(raw) - (int64_t{1} << 32);
                    normalized += to_string(signedValue);
                } else {
                    normalized += match[2].str();
                }
            } catch (const std::exception&) {
                normalized += match[2].str();
            }
            normalized += match[3].str();
            remaining = match.suffix().str();
        }
        normalized += remaining;
        m_model_str.swap(normalized);
    }
    restoreVarName(m_smt2);
    m_restored = true;
}

void tool::Solver::restoreVarName(std::string& str)
{
    string ret;
    smatch m;
    regex e1("([a-zA-Z_][a-zA-Z_0-9]*)@([0-9]+)"),
        e2("%av@([0-9]+)");
    while (true)
    {
        if (regex_search(str, m, e2)) {
            ret += m.prefix().str();
            int addr = str2int(m[1]);
            if (m_using_sparse_array) {
                auto vard = ctx.getAvDecl();
                auto e = mapping[vard].contents[addr].front();
                addr = (int)m_model.eval(getRValue(e)).as_int64();
            }
            ret += ctx.getOriginalExprOfAvAddress(addr);
            m.suffix().str().swap(str);
        }
        else if (regex_search(str, m, e1)) {
            ret += m.prefix().str();
            string name = m[1], offset = m[2];
            if (auto vard = dynamic_cast<VarDecl*>(ctx.getDecl(name))) {
                // TODO: 只适用一维数组
                if (vard->getType().isArray()) {
                    if (m_using_sparse_array) {
                        int addr = str2int(offset);
                        auto e = mapping[dynamic_cast<VarDecl*>(vard)].contents[addr].front();
                        addr = (int)m_model.eval(getRValue(e)).as_int64();
                        offset = to_string(addr);
                    }
                    name += "[" + offset + "]";
                }
            }
            ret += name;
            m.suffix().str().swap(str);
        }
        else {
            ret += str;
            break;
        }
    }
    str.swap(ret);
}

void tool::Solver::printTables(std::ostream& os)
{
    if (!_debug) return;
    for (auto const t : tables) {
        cout << "--------" << t->index << "--------";
        t->print();
    }
    cout << "=================" << std::endl << std::endl;
}

tool::Solver::Solver(Context& ctx)
    : ctx(ctx), z3_context(), z3_solver(z3_context),
    empty(z3_context.int_const("%empty")), m_model(z3_context)
{
}

tool::Solver::~Solver()
{
    for (auto t : tables | views::reverse)
        delete t;
}

z3::context& tool::Solver::getZ3Context()
{
    return z3_context;
}

z3::solver& tool::Solver::getZ3Solver()
{
    return z3_solver;
}

constexpr bool tool::Solver::usingSparseArray() const
{
    return m_using_sparse_array;
}

void tool::Solver::visit(Node* n)
{
    if (!n or isVisited(n))
        return;
    push(n);
    n->visit(*this);
    pop();
}

bool tool::Solver::isVisited(Node* n)
{
    if (!(tables.size() && tables.back()))
        return false;
    return tables.back()->isVisited(n);
}

void tool::Solver::push(Node* n)
{
    if (!(tables.size() && tables.back()))
        throw BUG("push节点时符号表为空");
    tables.back()->visiting.push(n);
}

void tool::Solver::pop()
{
    if (!(tables.size() && tables.back()))
        throw BUG("pop节点时符号表为空");
    auto v = getVisiting();
    tables.back()->visiting.pop();
    tables.back()->visited.insert(v);
}

Node* tool::Solver::getVisiting()
{
    if (!(tables.size() && tables.back() && tables.back()->visiting.size())) {
        debug << "没有正在访问的节点" << tool::endL;
        return nullptr;
    }
    return tables.back()->visiting.top();
}

void tool::Solver::setBacktrackingPoint(ArraySubscriptExpr* AE)
{
    auto BS = AE->getBase(), SS = AE->getSubscript();
    auto [vard, off] = getLValue(BS);
    const auto& qt = BS->getType();
    int len = qt.getLenth(), size = qt.getElementSize();
    // 先确定是否已经回溯过
    auto it = tables.rbegin(), et = tables.rend(); // 反向找
    for (; it != et; ++it)
        if ((*it)->node == AE)  // 找到
            break;
    if (it == tables.rbegin())  // 如果在表头（反向），取下个值
        (*it)->step();
    else if (it == et) {        // 新的回溯点，根据m_using_sparse_array表现不同
        visit(SS);              // 访问下标，其他情况已经访问过，所以不需要
        auto [index, need_backtrack] = mapExpr(vard, SS);
        if (!need_backtrack) {
            debug << "无需回溯的节点：" << AE->getCode() << tool::endL;
            setLValue(AE, { vard, off + size * index });
            return;
        }
        debug << "插入新的回溯节点：" << AE->getCode() << tool::endL;
        tables.back()->setBacktrackingPoint(AE, index, len);
    }
    else
        return;                 // 否则什么也不做
    const auto& prev = *tables.back();
    tables.emplace_back(new Table(prev, *this));
    auto& contents = mapping[vard].contents;
    int index = prev.getPos();
    auto front_expr = contents[index].front();
    auto SS_rv = getRValue(SS);
    if (front_expr == SS)
        addCond(0 <= SS_rv && SS_rv < len);
    else
        addCond(getRValue(front_expr) == SS_rv);
    setLValue(AE, { vard, off + size * index});
    // printTables(cout);
}

int tool::Solver::getBacktrackPointValue(Expr* e)
{
    for (auto const t : tables)
        if (t->node == e)
            return t->now;
    cout << "找不到回溯点\"" << *e << "\"!" << endl;
    return -1;
}

void tool::Solver::addCond(const z3::expr& cond)
{
    tables.back()->addCond(cond);
}

void tool::Solver::alloc(VarDecl* vard, Expr* init)
{
    tables.back()->alloc(vard, init);
}

void tool::Solver::extend(VarDecl* vard, bool isConstant)
{
    // 稀疏数组专属
    if (!m_using_sparse_array)
        return;
    tables.back()->extend(vard);
}

void tool::Solver::assign(const lvalue& lv, const rvalue& rv)
{
    // TODO: 现版本没有实现分段写入
    if (tables.empty()) {
        cout << "写入时表项空" << endl;
        return;
    }
    tables.back()->assign(lv, rv);
}

Solver::rvalue tool::Solver::getMemory(const lvalue& lv)
{
    for (auto const t : tables | views::reverse) {
        const auto& ret = t->getMemory(lv);
        if (ret.id() != empty.id())
            return ret;
    }
    return empty;
}

void tool::Solver::setLValue(Expr* e, const lvalue& lv)
{
    tables.back()->setLValue(e, lv);
    // printTables(cout);
}

void tool::Solver::setRValue(Expr* e, const rvalue& rv)
{
    tables.back()->setRValue(e, rv);
    // printTables(cout);
}

Solver::lvalue tool::Solver::getLValue(Expr* e)
{
    for (auto const t : tables | views::reverse) {
        const auto& tmp = t->getLValue(e);
        if (tmp.vard)
            return tmp;
    }
    return { nullptr, 0 };
}

Solver::rvalue tool::Solver::getRValue(Expr* e)
{
    if (e->isLvExpr())
        return getMemory(getLValue(e));
    for (auto const t : tables | views::reverse) {
        const auto& ret = t->getRValue(e);
        if (ret.id() != empty.id())
            return ret;
    }
    return empty;
}

int tool::Solver::getMem() const
{
    return ctx.getAST()->getMem();
}

const std::string& tool::Solver::getSMT2()
{
    restoreVarName();
    return m_smt2;
}

const std::string& tool::Solver::getModel()
{
    restoreVarName();
    return m_model_str;
}

result tool::Solver::feasible()
{
    m_restored = false;
    // 首先判断路径类型：C0 C1 C2 ？
    int path_type = ctx.getPathType();
    if (path_type == 0) { // C0
        cout << "开始分析路径，路径为C0，";
        cout << "分析中..." << std::endl;
    }
    //else if (path_type == 1) { // C1
    //	cout << "分析时间可能较长..." << std::endl;
    //}
    else if (path_type == 2 || path_type == 1) { // C2，但是称为C1
        cout << "开始分析路径，路径为C1，";
        cout << "正在转化路径..." << std::endl;
        ctx.cast2C1();
        if (_debug1) {
            cout << "树：" << std::endl;
            ctx.getAST()->print(cout);
            cout << "代码：" << std::endl;
            ctx.getAST()->printCode(cout);
        }
        cout << "分析中..." << std::endl;
        // return result::infeasible;
    }
    else { // default
        cout << "意外的路径类型，分析中..." << std::endl;
    }
    // cout << "进入solver::feasible" << std::endl;
    // m_model = m_smt2 = "";
    tables.emplace_back(new Table(*this));
    push(ctx.getAST());
    while (auto v = getVisiting())
    {
        try {
            v->visit(*this);
            pop();
        }
        catch (const feasibility_exception& fe) {
            auto r = fe.get_result();
            if (r == result::infeasible) {
                if (tables.size()) {
                    delete tables.back();
                    tables.pop_back();
                }
                if (tables.empty())
                    return result::infeasible;
            }
            else if (r == result::feasible)
                return result::feasible;
            else
                return result::unknown;
        }
        catch (const base_expception& be) {
            cout << be.what() << endl;
            return result::unknown;
        }
        catch (const std::exception& e) {
            cout << endl << "====================" << endl;
            cout << "错误发生了 :(" << endl;
            cout << e.what() << endl;
            return result::unknown;
        }
    }
    return result::feasible;
}
