// Copyright (c) 2020/21/22 Leandro T. C. Melo <ltcmelo@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef PSYCHE_C_SYNTAX_NAME_PRINTER_H__
#define PSYCHE_C_SYNTAX_NAME_PRINTER_H__

#include <ostream>
#include <tuple>
#include <vector>
#include <limits>
#include <chrono>
#include <iomanip>
#include <optional>
#include <cstdint>

#include "API.h"
#include "SyntaxDumper.h"
//#include "driver.h"
#include "debug.h"
#include "reader.h"
#include "solver.h"
#include <set>
#include <queue>
#include <sstream>
#include <stack>
#include <tuple>
#include <functional>
#include "EpatRunner.h"

//using namespace tool;


// tuple hash for dpMemo
namespace std {
    template<typename T>
    inline void hash_combine(std::size_t& seed, const T& v) {
        seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template<typename... TT>
    struct hash<std::tuple<TT...>> {
        std::size_t operator()(const std::tuple<TT...>& tt) const {
            std::size_t seed = 0;
            apply([&seed](const auto&... args) {
                (hash_combine(seed, args), ...);
            }, tt);
            return seed;
        }
    };
}

using namespace epat;

namespace psy {
namespace C {

// 路径信息结构体

// ========== DP 结果结构 ==========
struct PathInfo {
    int mems;          // 累计最大 MEMS
    std::string path;  // 对应路径串
    bool feasible;     // 是否可行
    PathInfo(): mems(0), feasible(false) {}
    PathInfo(int m, std::string p, bool f): mems(m), path(std::move(p)), feasible(f) {}
};

// 全局可行性缓存
extern std::unordered_map<std::string, bool> feasCache;


class FunctionParameterExtractor : public SyntaxVisitor {
public:
    FunctionParameterExtractor(const SyntaxTree* tree) : SyntaxVisitor(tree) {}
    std::vector<const SyntaxNode*> parameters;
    virtual Action visitParameterDeclaration(const ParameterDeclarationSyntax* node) override {
        parameters.push_back(node);
        return Action::Skip;
    }
};

class CFGNode {
public:
    bool isCondition;
    bool isWhile;
    bool isLoop;
    bool isFor;
    bool isIf;
    bool isReturn;
    bool isFuncDef;
    bool isVarDef;
    bool hasCallExpr;
    std::vector<std::string> calleeNames;
    std::string functionName;
    bool isCovered;
    bool setmem;
    int depth;
    int nodeLevel;
    int loopCount;
    int memUsage;
    const ExpressionSyntax* cond_;
    const StatementSyntax* initstmt_;
    const ExpressionSyntax* expr_;
    std::string cond_str;
    std::string initstmt_str;
    std::string expr_str;
    SyntaxKind kind_;

    CFGNode()
        : isCondition(false),
          isWhile(false),
          isLoop(false),
          isFor(false),
          isIf(false),
          isReturn(false),
          isFuncDef(false),
          isVarDef(false),
          hasCallExpr(false),
          calleeNames(),
          functionName(),
          isCovered(false),
          setmem(false),
          depth(0),
          nodeLevel(-1),
          loopCount(0),
          memUsage(0),
          cond_(nullptr),
          initstmt_(nullptr),
          expr_(nullptr),
          cond_str(),
          initstmt_str(),
          expr_str(),
          kind_(SyntaxKind::UnknownSyntax),
          cfgCode_(),
          nextNode_(nullptr),
          nextFalseNode_(nullptr),
          syntaxNode_(nullptr) {}

    void setKind(SyntaxKind kind) { kind_ = kind; }
    SyntaxKind getKind() const { return kind_; }

    void setCode(std::string codeSnippet);
    std::string getCode();

    void setNextNode(std::shared_ptr<CFGNode> nextNode);
    std::shared_ptr<CFGNode> getNextNode();

    void setNextFalseNode(std::shared_ptr<CFGNode> nextFalseNode);
    std::shared_ptr<CFGNode> getNextFalseNode();

    void setSyntaxNode(const SyntaxNode* syntaxNode);
    const SyntaxNode* getSyntaxNode();

    std::string ExpressionToString(const ExpressionSyntax* node);
    std::string StatementToString(const StatementSyntax* node);

    std::string ExpressionToString2(ExpressionSyntax* node);
    std::string StatementToString2(StatementSyntax* node);

    int getMem(const std::string& vartemp);

private:
    std::string cfgCode_;
    std::shared_ptr<CFGNode> nextNode_;
    std::shared_ptr<CFGNode> nextFalseNode_;
    const SyntaxNode* syntaxNode_;
};

class PSY_C_API SyntaxNamePrinter final : public SyntaxDumper {
public:
    int maxdepth;
    int maxmem;
    int minmem;
    using SyntaxDumper::SyntaxDumper;
    std::string vartemp = "";
    int temp_loopcount;


    // 动态规划记忆表，tuple key 需要 hash 支持
    mutable std::unordered_map<
        std::tuple<CFGNode*, std::string, std::string>, PathInfo
    > dpMemo;

    enum class Style : char { Plain, Decorated };

    void print(const SyntaxNode* node, Style style);
    void print(const SyntaxNode* node, Style style, std::ostream& os);
    void getCFG(const SyntaxNode* node);
    void printCFG();
    void printCFG_DFS(int maxloop, int maxpaths);
    void printCFG_DFS2(int maxloop, int maxpaths, bool enableVolce, int volceLower, int volceUpper);
    void printCFG_greedyDFS(int maxloop, int maxpaths, bool enableVolce);
    void DFS(std::shared_ptr<CFGNode> node,
        std::vector<bool>& pathCoverage,
        std::vector<PathDecision>& decisions,
        int depth,
        int& pathCount,
        int maxloop,
        int maxpaths,
        int& maxMems,
        int& minMems
    );
    void DFS2(std::shared_ptr<CFGNode> node,
              std::vector<bool>& pathCoverage,
              std::vector<PathDecision>& decisions,
              int depth,
              int& pathCount,
              int maxloop,
              int maxpaths,
              bool enableVolce,
              int volceLower,
              int volceUpper,
              const std::string& functionTag);
    void GreedyDFS(std::shared_ptr<CFGNode> node,
        std::vector<bool>& pathCoverage,
        std::vector<PathDecision> decisions,
        int depth,
        int& pathCount,
        int maxloop,
        int maxpaths,
        int currentMem,
        std::string& bestPath,
        int& bestMem);
    int EvaluateBranchMem(std::shared_ptr<CFGNode> node, int maxloop, int nodelevel);

    std::unordered_map<const CFGNode*, PathInfo> memo;
    PathInfo MaxMemsDP(
        const std::shared_ptr<CFGNode>& entry,
        int maxloop,
        std::string pathPrefix,  // raw path 前缀（不含 vartemp）
        int depth,
        std::unordered_map<CFGNode*, int>& loopUnrollMap,
        std::vector<PathDecision> decisions
    );
    //std::string LoopMapKey(const std::unordered_map<CFGNode*, int>& mp);

    void printCFG_BFS();
    void BFS(std::shared_ptr<CFGNode> startNode, std::vector<bool>& pathCoverage, std::vector<PathDecision> decisions, int& pathCount);
    void processPathResult(const EpatResult& eval,
                           const std::string& path,
                           std::vector<bool>& pathCoverage,
                           int pathCount,
                           int depth);
    void processPathResult2(const EpatResult& eval,
                            const std::string& path,
                            std::vector<bool>& pathCoverage,
                            int pathCount,
                            int depth,
                            const std::string& functionTag,
                            bool enableVolce,
                            int volceLower,
                            int volceUpper,
                            const std::vector<std::string>& callees);
    void collectGlobalVariables(const SyntaxNode* rootNode);
    void startBranchMatrix();
    void pushBranchRow(const std::vector<bool>& row);
    void printBranchMatrix();

    struct FeasiblePathSummary {
        int pathIndex{0};
        int mem{0};
        std::string path;
        std::vector<std::string> callees;
        std::optional<std::uint64_t> volceCount;
    };

    struct SummaryCase {
        size_t guardHash{0};
        int mems{0};
        int composedMems{0};
        std::vector<std::string> callees;
        std::optional<double> prob;
    };

    struct FunctionSummary {
        std::string name;
        std::string signature;
        std::vector<SummaryCase> cases;
        int worstMems{-1};
        double avgMems{-1.0};
    };

    void dumpFunctionSummaries(int maxloop, int maxpaths, bool enableVolce, int volceLower, int volceUpper);

    bool isPathFeasible(const std::vector<PathDecision>& decisions, const std::string& pathExpr) {
        auto cacheKey = vartemp + pathExpr;
        auto it       = feasCache.find(cacheKey);
        if (it != feasCache.end()) return it->second;

        EpatRunner runner(vartemp);
        bool ok = runner.solve(decisions).status == result::feasible;
        feasCache.emplace(std::move(cacheKey), ok);
        return ok;
    }

    // 兼容仅有路径串的判定需求
    bool isPathFeasible(const std::string& pathExpr) {
        std::vector<PathDecision> emptyDecisions;
        return isPathFeasible(emptyDecisions, pathExpr);
    }
    std::shared_ptr<CFGNode> createEndNode() {
        auto endNode = std::make_shared<CFGNode>();
        endNode->setKind(SyntaxKind::ExpressionStatement);
        endNode->depth = -1;
        return endNode;
    }

private:
    virtual void nonterminal(const SyntaxNode* node) override;
    void recordFeasiblePath(int pathIndex,
                            int mem,
                            const std::string& path,
                            const std::vector<std::string>& callees,
                            const std::optional<std::uint64_t>& volceCount);
    void printFeasiblePathSummary(bool enableVolce, int volceLower, int volceUpper) const;
    std::vector<std::vector<int>> ReadCoverageMatrix(const std::string& filename);
    void SolveLinearProgram(const std::vector<std::vector<int>>& coverageMatrix);

    std::vector<std::tuple<const SyntaxNode*, int>> dump_;
    std::vector<std::shared_ptr<CFGNode>> funcDefStack_;
    std::vector<std::shared_ptr<CFGNode>> VarDefStack_;
    std::vector<std::shared_ptr<CFGNode>> globalVarDefs;
    std::vector<std::pair<std::shared_ptr<CFGNode>, int>> ifPairStack_;
    std::vector<std::shared_ptr<CFGNode>> ifEndStmtStack_;
    std::vector<std::shared_ptr<CFGNode>> elseNodes;
    std::vector<std::pair<std::shared_ptr<CFGNode>, bool>> loopPairStack_;
    std::vector<std::vector<std::shared_ptr<CFGNode>>> breakStmtsStack_;

    std::vector<FeasiblePathSummary> feasiblePaths_;
    std::uint64_t totalVolceCount_{0};

    std::vector<int> loopCount;
    std::vector<int> temp_depth;
    std::vector<int> temp_loopCount[1000];
    std::vector<bool> temp_pathCoverage[1000];
    std::vector<std::string> currentPathCallees_;

    std::shared_ptr<CFGNode> lastNode = std::make_shared<CFGNode>();
    std::vector<std::vector<bool>> allPathsCoverage;
    std::vector<std::vector<bool>> edgeCoverageMatrix;
    std::vector<std::vector<int>> branchCovMatrix_;  // 每条路径一行，统一 2*maxdepth 列
};


// 你的成员：std::unordered_map<DPKey, PathInfo, DPKeyHasher> dpMemo;
// 这里重定义 Key：只依赖 (node, loopMapKey)
struct DPKey {
    CFGNode* node;
    std::string loopKey;
    bool operator==(const DPKey& o) const {
        return node == o.node && loopKey == o.loopKey;
    }
};
struct DPKeyHasher {
    size_t operator()(const DPKey& k) const noexcept {
        size_t h1 = std::hash<void*>{}(k.node);
        size_t h2 = std::hash<std::string>{}(k.loopKey);
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1<<6) + (h1>>2));
    }
};

}  // namespace C
}  // namespace psy

#endif
