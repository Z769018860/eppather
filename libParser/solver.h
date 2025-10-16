#ifndef TOOL_SOLVER_H
#define TOOL_SOLVER_H

#include <vector>
#include <map>
#include <set>
#include <string>
#include <stack>
#include <unordered_map>
#include <unordered_set>

#include <z3++.h>

namespace tool {

    class Context;
    class VarDecl;
    class Node;
    class Expr;
    class ArraySubscriptExpr;

    enum class result {
        feasible, infeasible, unknown
    };

    class Solver {
    public:
        struct lvalue {
            VarDecl* vard;
            int pos;
        };
        using rvalue = z3::expr;
    protected:
        using array = std::vector<rvalue>;
        struct Table {
            Solver& parent;			// 懂的都懂
            z3::context& ctx;		// 父对象z3上下文的引用
            rvalue& empty;		    // 备用的z3表达式，正常情况下不应被使用
            z3::solver& solver;		// 构造时新建的求解器
            int index = 0;          // 在parent中的序号
            // 回溯相关
            ArraySubscriptExpr* node = nullptr;	// 回溯点
            int left, right, now;	// 前闭后开
            std::stack<Node*> visiting;
            std::unordered_set<Node*> visited;
            // 内存
            std::unordered_map<VarDecl*, array> memory;
            // 左值和右值
            std::unordered_map<Expr*, lvalue> lvs;
            std::unordered_map<Expr*, rvalue> rvs;

            Table(Solver& parent);
            Table(const Table& table, Solver& parent);
            ~Table();
            bool operator==(const Table& other) const;
            void check();
            void print(std::ostream& os = std::cout);

            bool isVisited(Node* n);
            void setBacktrackingPoint(ArraySubscriptExpr* e, int l, int r);
            int getPos() const;
            void step();
            void addCond(const z3::expr& cond);

            void alloc(VarDecl* vard, Expr* init);
            void extend(VarDecl* vard);
            void assign(const lvalue& lv, const rvalue& rv);
            rvalue getMemory(const lvalue& lv) const;
            void setLValue(Expr* e, const lvalue& lv);
            void setRValue(Expr* e, const rvalue& rv);
            lvalue getLValue(Expr* e) const;
            rvalue getRValue(Expr* e) const;
            void copyFromPrev(VarDecl* vard);
        };
        struct mapping_table {
            // 将Expr*映射到int
            std::map<int, int> cache; // 缓存已有定值的序号
            std::vector<vector<Expr*>> contents; // 存相应序号值对应的表达式
            std::set<int> constants;
        };

        Context& ctx;
        z3::context z3_context;
        z3::solver z3_solver;
        rvalue empty;
        std::vector<Table*> tables;
        std::map<VarDecl*, mapping_table> mapping;
        // int mapContant(VarDecl* vard, Expr* constant);
        std::pair<int, bool> mapExpr(VarDecl* vard, Expr* e); // int表示序号值，bool为false表示不要回溯该点
        //void unmapExpr(VarDecl* vard, Expr* e, int now);
        void extendMappingTableTo(VarDecl* vard, int size);
        std::pair<int, bool> stepExpr(VarDecl* vard, Expr* e, int now);

        std::string m_smt2 = "没有SMT2。是否已经执行feasible方法？";
        std::string m_model_str = "没有model。是否已经执行feasible方法？";
        z3::model m_model;
        mutable int m_mem = 0, m_restored = false;
        bool m_using_sparse_array = true;
        void restoreVarName();
        void restoreVarName(std::string& str);
        void printTables(std::ostream& os);

    public:
        Solver(Context& ctx);
        ~Solver();
        z3::context& getZ3Context();
        z3::solver& getZ3Solver();
        constexpr bool usingSparseArray() const;

        // visit
        void visit(Node* n);
        bool isVisited(Node* n);
        void push(Node* n);
        void pop();
        Node* getVisiting();

        // table
        void setBacktrackingPoint(ArraySubscriptExpr* AE);
        int getBacktrackPointValue(Expr* e);
        void addCond(const z3::expr& cond);

        void alloc(VarDecl* vard, Expr* init);
        void extend(VarDecl* vard, bool isConstant = false);
        void assign(const lvalue& lv, const rvalue& rv);
        rvalue getMemory(const lvalue& lv);
        void setLValue(Expr* e, const lvalue& lv);
        void setRValue(Expr* e, const rvalue& rv);
        lvalue getLValue(Expr* e);
        rvalue getRValue(Expr* e);

        // api
        int getMem() const;
        const std::string& getSMT2();
        const std::string& getModel();
        result feasible();
    };

}

#endif // !TOOL_SOLVER_H