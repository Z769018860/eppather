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



#include "SyntaxNamePrinter.h"



#include <algorithm>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <limits>
#include <optional>
#include <stdlib.h>
#include <string>
#include <unordered_map>


#include "lp_lib.h"
#include "SyntaxNode.h"
#include "volce/volce_api.h"

//#include "stmt.h"

//#include "driver.h"

#include <string>


using namespace std;

using namespace psy;

using namespace C;

namespace {
constexpr int kVolceLowerBound = -8;
constexpr int kVolceUpperBound = 8;

struct VolceResult {
    std::string output;
    std::optional<std::string> count;
};

std::optional<std::uint64_t> parseVolceCount(const std::optional<VolceResult>& result) {
    if (!result || !result->count) {
        return std::nullopt;
    }
    const std::string& text = *result->count;
    if (text.empty()) {
        return std::nullopt;
    }
    std::uint64_t value = 0;
    for (char ch : text) {
        if (ch < '0' || ch > '9') {
            return std::nullopt;
        }
        const std::uint64_t digit = static_cast<std::uint64_t>(ch - '0');
        if (value > (std::numeric_limits<std::uint64_t>::max() - digit) / 10) {
            return std::nullopt;
        }
        value = value * 10 + digit;
    }
    return value;
}

std::optional<VolceResult> runVolce(const std::string& smt2, int lowerBound, int upperBound) {
    if (smt2.empty()) {
        return std::nullopt;
    }

    const volce::Range range{lowerBound, upperBound};
    const auto countResult = volce::countModelsFromSmt2(smt2, {}, range);
    if (!countResult) {
        return std::nullopt;
    }

    VolceResult result;
    result.output = std::to_string(countResult->count);
    result.count = result.output;
    return result;
}
}  // namespace



//using namespace tool;

//using namespace epat;



namespace {



int CUR_LEVEL;



std::string formatSnippet(std::string& snippet, bool maxLimit = true) {

    std::replace_if(

        snippet.begin(), snippet.end(), [](char c) { return c == '\n' || c == '\t'; }, ' ');



    while (true) {

        auto pos = snippet.find("  ");

        if (pos == std::string::npos) break;

        snippet = snippet.replace(pos, 2, " ");

    }



    if (maxLimit) {

        static const auto MAX_LEN = 200;

        if (snippet.length() > MAX_LEN) {

            snippet = snippet.substr(0, MAX_LEN);

            snippet += "...";

        }

    }



    return snippet;

}



}  // namespace



void SyntaxNamePrinter::print(const SyntaxNode* node, Style style) { print(node, style, std::cout); }



void SyntaxNamePrinter::print(const SyntaxNode* node, Style style, std::ostream& os) {

    CUR_LEVEL = 0;



    nonterminal(node);



    auto source = node->syntaxTree()->text().rawText();



    os << std::endl;

    for (auto i = 0U; i < dump_.size(); ++i) {

        auto node = std::get<0>(dump_[i]);

        auto nodeLevel = std::get<1>(dump_[i]);



        if (style == Style::Plain) {

            os << std::string(nodeLevel * 4, ' ');

            os << to_string(node->kind()) << std::endl;

            continue;

        }



        auto levelCnt = 0;

        while (nodeLevel > levelCnt) {

            if (nodeLevel == levelCnt + 1) {

                os << '|';

                os << std::string(2, '-');

            } else {

                int nextLevelBelow;

                for (auto j = i + 1; j < dump_.size(); ++j) {

                    nextLevelBelow = std::get<1>(dump_[j]);

                    if (nextLevelBelow <= levelCnt + 1) break;

                }

                if (nextLevelBelow == levelCnt + 1)

                    os << '|';

                else

                    os << ' ';

                os << std::string(2, ' ');

            }

            ++levelCnt;

        }



        os << to_string(node->kind()) << " [" << nodeLevel << "]  ";



        if (node->kind() == TranslationUnit) {

            os << std::endl;

            continue;

        }



        os << " <";

        auto firstTk = node->firstToken();

        auto lastTk = node->lastToken();

        if (firstTk.isValid()) os << firstTk.location().lineSpan().span().start();

        os << "..";

        if (lastTk.isValid()) os << lastTk.location().lineSpan().span().end();

        os << "> ";



        if (firstTk.isValid() && lastTk.isValid()) {

            auto firstTkStart = source.c_str() + firstTk.span().start();

            auto lastTkEnd = source.c_str() + lastTk.span().end();

            std::string snippet(firstTkStart, lastTkEnd - firstTkStart);

            os << " `" << formatSnippet(snippet) << "`";

        }



        os << std::endl;

    }

}



void SyntaxNamePrinter::nonterminal(const SyntaxNode* node) {

    if (!node) return;



    dump_.push_back(std::make_tuple(node, CUR_LEVEL));



    ++CUR_LEVEL;

    visit(node);

    --CUR_LEVEL;

}



// CFGNode related

// 获取第一个括号相匹配的内容

std::string getMatchContent(std::string input) {

    int index = input.find("(");

    int count;

    count = (index == -1) ? 0 : 1;

    index++;

    while (count > 0 && index < (int)input.size()) {

        if (input[index] == '(') count += 1;

        if (input[index] == ')') count -= 1;

        index++;

    }

    if (count == 0) return input.substr(0, index);

    return "";

}



void CFGNode::setCode(std::string codeSnippet) {

    // compound -> simple

    if (isCondition) {

        cfgCode_ = getMatchContent(codeSnippet);

        if (cfgCode_.empty()) {

            std::cout << "Invalid Conditional Statement" << std::endl;

        }

    } else

        cfgCode_ = codeSnippet;

}

std::string CFGNode::getCode() {

    if (cfgCode_.empty() && kind_==SyntaxKind::UnknownSyntax)

        return "Code has not been set yet";

    else

        return cfgCode_;

}

int CFGNode::getMem(const std::string& vartemp) {
    if (setmem) return memUsage;

    EpatRunner runner(vartemp);
    std::vector<PathDecision> decisions;

    if (isFor) {
        decisions.push_back(PathDecision{this, PathDecisionKind::LoopInit});
        decisions.push_back(PathDecision{this, PathDecisionKind::TrueBranch});
        decisions.push_back(PathDecision{this, PathDecisionKind::LoopUpdate});
    } else if (isIf || isWhile) {
        decisions.push_back(PathDecision{this, PathDecisionKind::TrueBranch});
    } else if (!isFuncDef) {
        decisions.push_back(PathDecision{this, PathDecisionKind::Code});
    }

    auto eval = runner.solve(decisions);
    memUsage = eval.mem;
    setmem = true;
    return memUsage;
}



std::string CFGNode::ExpressionToString2(ExpressionSyntax* node) {

    if (!node) return "";



    // 获取语法树的原始文本

    auto sourceText = node->syntaxTree()->text().rawText();



    // 定位表达式在源代码中的位置

    auto firstTk = node->firstToken();

    auto lastTk = node->lastToken();

    

    if (!firstTk.isValid() || !lastTk.isValid()) return "";



    auto firstTkStart = firstTk.span().start();

    auto lastTkEnd = lastTk.span().end();



    // 提取表达式文本

    std::string expressionText = sourceText.substr(firstTkStart, lastTkEnd - firstTkStart);



    // 格式化表达式文本

    return formatSnippet(expressionText);

}



std::string CFGNode::StatementToString2(StatementSyntax* node) {

    if (!node) return "";



    // 获取语法树的原始文本

    auto sourceText = node->syntaxTree()->text().rawText();



    // 定位语句在源代码中的位置

    auto firstTk = node->firstToken();

    auto lastTk = node->lastToken();

    

    if (!firstTk.isValid() || !lastTk.isValid()) return "";



    auto firstTkStart = firstTk.span().start();

    auto lastTkEnd = lastTk.span().end();



    // 提取语句文本

    std::string statementText = sourceText.substr(firstTkStart, lastTkEnd - firstTkStart);



    // 格式化语句文本

    return formatSnippet(statementText);

}



std::string CFGNode::ExpressionToString(const ExpressionSyntax* node) {

    if (!node) return "";



    // 获取语法树的原始文本

    auto sourceText = node->syntaxTree()->text().rawText();



    // 定位表达式在源代码中的位置

    auto firstTk = node->firstToken();

    auto lastTk = node->lastToken();

    

    if (!firstTk.isValid() || !lastTk.isValid()) return "";



    auto firstTkStart = firstTk.span().start();

    auto lastTkEnd = lastTk.span().end();



    // 提取表达式文本

    std::string expressionText = sourceText.substr(firstTkStart, lastTkEnd - firstTkStart);



    // 格式化表达式文本

    return formatSnippet(expressionText);

}



std::string CFGNode::StatementToString(const StatementSyntax* node) {

    if (!node) return "";



    // 获取语法树的原始文本

    auto sourceText = node->syntaxTree()->text().rawText();



    // 定位语句在源代码中的位置

    auto firstTk = node->firstToken();

    auto lastTk = node->lastToken();

    

    if (!firstTk.isValid() || !lastTk.isValid()) return "";



    auto firstTkStart = firstTk.span().start();

    auto lastTkEnd = lastTk.span().end();



    // 提取语句文本

    std::string statementText = sourceText.substr(firstTkStart, lastTkEnd - firstTkStart);



    // 格式化语句文本

    return formatSnippet(statementText);

}



void CFGNode::setNextNode(std::shared_ptr<CFGNode> nextNode) { nextNode_ = nextNode; }

std::shared_ptr<CFGNode> CFGNode::getNextNode() { return nextNode_; }



void CFGNode::setNextFalseNode(std::shared_ptr<CFGNode> nextFalseNode) { nextFalseNode_ = nextFalseNode; }

std::shared_ptr<CFGNode> CFGNode::getNextFalseNode() { return nextFalseNode_; }



void CFGNode::setSyntaxNode(const SyntaxNode* syntaxNode) { syntaxNode_ = syntaxNode; }

const SyntaxNode* CFGNode::getSyntaxNode() { return syntaxNode_; }


void SyntaxNamePrinter::getCFG(const SyntaxNode* root) {
    CUR_LEVEL = 0;
    nonterminal(root);

    CFGNode cfgnode;
    auto source = root->syntaxTree()->text().rawText();

    funcDefStack_.clear();
    globalVarDefs.clear();
    VarDefStack_.clear();
    vartemp.clear();

    bool callExprFlag = false;
    int  depth_count  = 0;

    // 获取语句块第一条“可执行语句”，空块返回 nullptr
    auto firstExecutable = [](const StatementSyntax* s) -> const StatementSyntax* {
        if (!s) return nullptr;
        if (s->kind() == SyntaxKind::CompoundStatement) {
            auto comp = s->asCompoundStatement();
            auto list = comp->statements();
            return list ? list->value : nullptr;
        }
        return s;
    };

    struct IfFrame {
        std::shared_ptr<CFGNode> cond;
        const StatementSyntax*   thenFirst;
        const StatementSyntax*   elseFirst;
        std::shared_ptr<CFGNode> join;
        int                      level;
        bool                     inElse;
    };
    std::vector<IfFrame> ifStack;

    struct LoopFrame {
        std::shared_ptr<CFGNode> cond;
        std::shared_ptr<CFGNode> bodyEnd;
        std::shared_ptr<CFGNode> join;
        int                      level;
        std::vector<std::shared_ptr<CFGNode>> breaks;
        std::shared_ptr<CFGNode> lastInBody;
        bool                     isFor;
    };
    std::vector<LoopFrame> loopStack;

    struct PendingEdge { std::shared_ptr<CFGNode> from; const SyntaxNode* toSyn; bool isFalse; };
    std::unordered_map<const SyntaxNode*, std::vector<PendingEdge>> pendingEdges;

    std::unordered_map<const StatementSyntax*, std::shared_ptr<CFGNode>> forInitToCond;
    std::unordered_map<const SyntaxNode*, std::shared_ptr<CFGNode>> syn2cfg;

    edgeCoverageMatrix.clear();
    edgeCoverageMatrix.resize(dump_.size(), std::vector<bool>(dump_.size(), false));

    for (size_t i = 0; i < dump_.size(); ++i) {
        auto* syn       = std::get<0>(dump_[i]);
        auto  nodeLevel = std::get<1>(dump_[i]);

        auto firstTk = syn->firstToken();
        auto lastTk  = syn->lastToken();
        if (!firstTk.isValid() || !lastTk.isValid())
            continue;

        auto firstTkStart = source.c_str() + firstTk.span().start();
        auto lastTkEnd    = source.c_str() + lastTk.span().end();
        std::string snippet(firstTkStart, lastTkEnd - firstTkStart);

        // 全局变量（层级=1 的 VariableAndOrFunctionDeclaration）
        if (nodeLevel == 1 && syn->kind() == SyntaxKind::VariableAndOrFunctionDeclaration) {
            auto g = std::make_shared<CFGNode>();
            g->isVarDef = true;
            g->setSyntaxNode(syn);
            g->setCode(snippet);
            globalVarDefs.push_back(g);
        }

        // 函数定义
        if (syn->kind() == SyntaxKind::FunctionDefinition) {
            auto f = std::make_shared<CFGNode>();
            f->isFuncDef = true;
            f->depth = depth_count++;
            f->setSyntaxNode(syn);
            f->nodeLevel = nodeLevel;
            f->memUsage = 0;

            const DeclaratorSyntax* declarator = syn->asFunctionDefinition()->declarator();
            auto fstart = source.c_str() + firstTk.span().start();
            std::string signature;
            if (declarator) {
                auto dend = source.c_str() + declarator->lastToken().span().end();
                signature = std::string(fstart, dend - fstart);
            } else {
                signature = std::string(fstart, source.c_str() + lastTk.span().end() - fstart);
            }
            f->setCode(formatSnippet(signature, false));
            funcDefStack_.push_back(f);

            // 形参收集
            FunctionParameterExtractor extractor(syn->syntaxTree());
            syn->acceptVisitor(&extractor);
            for (const auto& p : extractor.parameters) {
                auto v = std::make_shared<CFGNode>();
                v->isVarDef = true;
                v->setSyntaxNode(p);
                auto pf = p->firstToken(), pl = p->lastToken();
                auto ps = source.c_str() + pf.span().start();
                auto pe = source.c_str() + pl.span().end();
                std::string sn(ps, pe - ps);
                v->setCode(formatSnippet(sn, false));
                VarDefStack_.push_back(v);
            }
        }

        // 仅为“非 CompoundStatement”建 CFG 结点
        if (syn->kind() > SyntaxKind::CompoundStatement && syn->kind() < SyntaxKind::TypeName) {

            // A) 进入某 if 的 else 首句：阻断 then→else 落入，并把 then 尾接到 join
            bool enteringElse = false;
            int  enteringElseIdx = -1;
            for (int k = (int)ifStack.size() - 1; k >= 0; --k) {
                auto& fr = ifStack[k];
                if (fr.elseFirst && syn == fr.elseFirst && !fr.inElse) {
                    enteringElse    = true;
                    enteringElseIdx = k;
                    break;
                }
            }
            if (enteringElse) {
                auto& fr = ifStack[enteringElseIdx];
                if (lastNode && lastNode != fr.join) {
                    lastNode->setNextNode(fr.join);
                }
                fr.inElse = true;
            }

            // B) 创建当前结点前：收束“已结束的 if/loop”
            bool closedSomething = false;

            // 这些 join 要在“当前结点 n 创建之后”再连出去
            std::vector<std::shared_ptr<CFGNode>> pendingIfJoinsToOutside;
            std::vector<std::shared_ptr<CFGNode>> pendingLoopJoinsToOutside;

            // B1) 收束 if：遇到 nodeLevel <= if.level 表示离开该 if
            while (!ifStack.empty() && nodeLevel <= ifStack.back().level) {
                auto fr = ifStack.back();

                // 把 then/else 的尾（当前 lastNode）并到 if.join
                if (lastNode && lastNode != fr.join) {
                    lastNode->setNextNode(fr.join);
                }

                // ★ 修正点：是否把 if.join 直接接到 bodyEnd？
                // 只有当“正在离开循环体”（nodeLevel <= loop.level）时，才 join→bodyEnd；
                // 如果下一条语句与该 if 同级（nodeLevel == if.level）或仍在循环体内更深层，
                // 则应该让 join→当前即将创建的语句 n（pending 方式回填）。
                bool joinToBodyEnd = false;
                if (!loopStack.empty()) {
                    auto& L = loopStack.back();
                    // 只有“离开循环体”才指向 bodyEnd
                    joinToBodyEnd = (nodeLevel <= L.level);
                }

                if (joinToBodyEnd) {
                    auto& L = loopStack.back();
                    fr.join->setNextNode(L.bodyEnd);
                    // 更新路径尾为 bodyEnd，避免顺序边误连
                    lastNode = L.bodyEnd;
                } else {
                    pendingIfJoinsToOutside.push_back(fr.join);
                    lastNode = fr.join;
                }

                ifStack.pop_back();
                closedSomething = true;
            }

            // B2) 收束 loop：遇到 nodeLevel <= loop.level 表示离开该循环
            while (!loopStack.empty() && nodeLevel <= loopStack.back().level) {
                auto lf = loopStack.back();

                if (lf.lastInBody && lf.lastInBody->nodeLevel > lf.level && lf.lastInBody != lf.bodyEnd)
                    lf.lastInBody->setNextNode(lf.bodyEnd);
                if (lastNode && lastNode->nodeLevel > lf.level && lastNode != lf.bodyEnd)
                    lastNode->setNextNode(lf.bodyEnd);

                // bodyEnd → cond（统一回环）
                lf.bodyEnd->setNextNode(lf.cond);

                // break → join
                for (auto& br : lf.breaks) br->setNextNode(lf.join);

                // join 的外部后继延迟到“当前结点 n 创建后”回填
                pendingLoopJoinsToOutside.push_back(lf.join);

                loopStack.pop_back();
                closedSomething = true;

                // 离开循环后断开顺序边
                lastNode = nullptr;
            }

            // C) 创建当前 CFG 结点 n
            auto n = std::make_shared<CFGNode>();
            n->setSyntaxNode(syn);
            n->nodeLevel = nodeLevel;
            n->depth = depth_count++;

            // 声明语句：保留原保护，不再“吞并下一条语句”
            if (syn->kind() == SyntaxKind::DeclarationStatement) {
                n->isVarDef = true;
                n->setCode(formatSnippet(snippet, false));
                if (n->nodeLevel == 3) VarDefStack_.push_back(n);
            } else {
                n->setCode(formatSnippet(snippet, false));
            }
            syn2cfg[syn] = n;

            // 回填 if.join / loop.join → n
            for (auto& jn : pendingIfJoinsToOutside)  jn->setNextNode(n);
            for (auto& jn : pendingLoopJoinsToOutside) jn->setNextNode(n);

            // 默认顺序边（未收束且未进入 else 首句时才连接）
            if (callExprFlag && lastNode) { lastNode->hasCallExpr = true; callExprFlag = false; }
            if (!funcDefStack_.empty()) {
                auto head = funcDefStack_.back();
                if (head && !head->getNextNode()) {
                    head->setNextNode(n);
                } else if (!closedSomething && !enteringElse && lastNode &&
                           lastNode->getSyntaxNode() &&
                           lastNode->getSyntaxNode()->kind() != SyntaxKind::ReturnStatement &&
                           lastNode->getSyntaxNode()->kind() != SyntaxKind::ContinueStatement) {
                    lastNode->setNextNode(n);
                }
            }

            // D) 识别 If / For / While
            if (syn->kind() == SyntaxKind::IfStatement) {
                n->isCondition = true; n->isIf = true;
                n->cond_    = syn->asIfStatement()->condition();
                n->cond_str = cfgnode.ExpressionToString(n->cond_);

                const IfStatementSyntax* ifSyn = syn->asIfStatement();
                const StatementSyntax* thenFirst = firstExecutable(ifSyn->statement());
                const StatementSyntax* elseFirst = firstExecutable(ifSyn->elseStatement());

                auto join = createEndNode();
                join->nodeLevel = nodeLevel;

                if (thenFirst) pendingEdges[thenFirst].push_back({ n, thenFirst, false });
                else           n->setNextNode(join);

                if (elseFirst) pendingEdges[elseFirst].push_back({ n, elseFirst, true });
                else           n->setNextFalseNode(join);

                ifStack.push_back(IfFrame{ n, thenFirst, elseFirst, join, nodeLevel, false });
            }
            else if (syn->kind() == SyntaxKind::ForStatement) {
                n->isCondition = true; n->isFor = true; n->isLoop = true; n->loopCount = 0;

                n->initstmt_    = syn->asForStatement()->initializer();
                n->initstmt_str = cfgnode.StatementToString(n->initstmt_);
                n->cond_        = syn->asForStatement()->condition();
                n->cond_str     = cfgnode.ExpressionToString(n->cond_);
                n->expr_        = syn->asForStatement()->expression();
                n->expr_str     = cfgnode.ExpressionToString(n->expr_);

                const StatementSyntax* initFirst = firstExecutable(n->initstmt_);
                const StatementSyntax* bodyFirst = firstExecutable(syn->asForStatement()->statement());

                auto join    = createEndNode(); join->nodeLevel    = nodeLevel;
                auto bodyEnd = createEndNode(); bodyEnd->nodeLevel = nodeLevel + 1;

                // false → join（跳出循环）
                n->setNextFalseNode(join);

                // true → body 首句；体空则 true → bodyEnd
                if (bodyFirst) pendingEdges[bodyFirst].push_back({ n, bodyFirst, false });
                else           n->setNextNode(bodyEnd);

                // 体末端统一回到 cond
                bodyEnd->setNextNode(n);

                if (initFirst) forInitToCond[initFirst] = n;

                loopStack.push_back(LoopFrame{ n, bodyEnd, join, nodeLevel, {}, nullptr, /*isFor*/true });
            }
            else if (syn->kind() == SyntaxKind::WhileStatement) {
                n->isCondition = true; n->isWhile = true; n->isLoop = true; n->loopCount = 0;

                n->cond_    = syn->asWhileStatement()->condition();
                n->cond_str = cfgnode.ExpressionToString(n->cond_);

                const StatementSyntax* bodyFirst = firstExecutable(syn->asWhileStatement()->statement());

                auto join    = createEndNode(); join->nodeLevel    = nodeLevel;
                auto bodyEnd = createEndNode(); bodyEnd->nodeLevel = nodeLevel + 1;

                n->setNextFalseNode(join);
                if (bodyFirst) pendingEdges[bodyFirst].push_back({ n, bodyFirst, false });
                else           n->setNextNode(bodyEnd);

                bodyEnd->setNextNode(n);

                loopStack.push_back(LoopFrame{ n, bodyEnd, join, nodeLevel, {}, nullptr, /*isFor*/false });
            }

            // 回填 True/False 延迟边
            if (auto it = pendingEdges.find(syn); it != pendingEdges.end()) {
                for (const auto& pe : it->second) {
                    if (pe.isFalse) pe.from->setNextFalseNode(n);
                    else            pe.from->setNextNode(n);
                }
                pendingEdges.erase(it);
            }

            // 回填 for init → cond
            if (auto it2 = forInitToCond.find(static_cast<const StatementSyntax*>(syn)); it2 != forInitToCond.end()) {
                n->setNextNode(it2->second);
                forInitToCond.erase(it2);
            }

            // break / continue
            if (syn->kind() == SyntaxKind::BreakStatement) {
                if (!loopStack.empty()) loopStack.back().breaks.push_back(n);
            }
            if (syn->kind() == SyntaxKind::ContinueStatement) {
                if (!loopStack.empty()) {
                    auto& L = loopStack.back();
                    if (L.isFor) n->setNextNode(L.bodyEnd); // for: continue → bodyEnd（再 bodyEnd→cond）
                    else         n->setNextNode(L.cond);    // while: continue → cond
                }
            }

            // 更新“体内最后观测到的结点”（凡是比循环层级更深的都算体内）
            for (auto& L : loopStack) {
                if (n->nodeLevel > L.level) L.lastInBody = n;
            }

            if (syn->kind() == SyntaxKind::ReturnStatement) n->isReturn = true;

            lastNode = n;
        }

        if (syn->kind() == SyntaxKind::CallExpression) callExprFlag = true;
    }

    // 文件尾兜底：收束未关闭的 if / loop
    while (!ifStack.empty()) {
        auto fr = ifStack.back();
        if (!loopStack.empty()) {
            auto& L = loopStack.back();
            if (lastNode && lastNode != L.bodyEnd) lastNode->setNextNode(L.bodyEnd);
            fr.join->setNextNode(L.bodyEnd);
            lastNode = L.bodyEnd;
        } else {
            if (lastNode && lastNode != fr.join) lastNode->setNextNode(fr.join);
            lastNode = fr.join;
        }
        ifStack.pop_back();
    }

    while (!loopStack.empty()) {
        auto lf = loopStack.back();
        if (lf.lastInBody && lf.lastInBody->nodeLevel > lf.level && lf.lastInBody != lf.bodyEnd)
            lf.lastInBody->setNextNode(lf.bodyEnd);
        if (lastNode && lastNode->nodeLevel > lf.level && lastNode != lf.bodyEnd)
            lastNode->setNextNode(lf.bodyEnd);
        lf.bodyEnd->setNextNode(lf.cond);
        for (auto& br : lf.breaks) br->setNextNode(lf.join);
        loopStack.pop_back();
        lastNode = lf.join;
    }

    maxdepth = depth_count;

    // 变量文本输出
    for (auto& n : globalVarDefs) {
        std::string code = n->getCode();
        if (!code.empty() && code.back() != ';') code += ";";
        vartemp += code + "\n";
    }
    for (auto& n : VarDefStack_) {
        std::string code = n->getCode();
        if (!code.empty() && code.back() != ';') code += ";";
        vartemp += code + "\n";
    }
}


void SyntaxNamePrinter::printCFG() {
    using std::cout;
    using std::endl;

    auto getKindName = [&](const std::shared_ptr<CFGNode>& n) -> std::string {
        if (!n) return "null";
        if (n->getKind() != SyntaxKind::UnknownSyntax) return to_string(n->getKind());
        if (n->getSyntaxNode()) return to_string(n->getSyntaxNode()->kind());
        return "UnknownSyntax";
    };

    auto sanitize = [&](std::string s, size_t maxlen = 80) -> std::string {
        for (char& c : s) {
            if (c == '\n' || c == '\r' || c == '\t') c = ' ';
        }
        while (!s.empty() && (s.back() == ' ')) s.pop_back();
        if (s.size() > maxlen) s = s.substr(0, maxlen - 3) + "...";
        return s;
    };

    auto nodeLabel = [&](const std::shared_ptr<CFGNode>& n) -> std::string {
        if (!n) return "";
        std::string base = sanitize(n->getCode());
        if (n->isIf)    base = "if(" + sanitize(n->cond_str, 40) + ")";
        if (n->isWhile) base = "while(" + sanitize(n->cond_str, 40) + ")";
        if (n->isFor)   base = "for(" + sanitize(n->initstmt_str, 20) + "; " + sanitize(n->cond_str, 20) + "; " + sanitize(n->expr_str, 20) + ")";
        if (base.empty()) base = getKindName(n);
        return base;
    };

    auto shapeOf = [&](const std::shared_ptr<CFGNode>& n) -> const char* {
        if (!n) return "box";
        if (n->isIf || n->isWhile || n->isFor) return "diamond";
        if (n->getKind() == SyntaxKind::UnknownSyntax && !n->getSyntaxNode()) return "circle"; // end/empty node
        return "box";
    };

    for (size_t fi = 0; fi < funcDefStack_.size(); ++fi) {
        std::shared_ptr<CFGNode> entry = funcDefStack_[fi];
        if (!entry) continue;

        // 1) Collect reachable nodes (true/next and false edges), assign stable ids
        std::unordered_map<CFGNode*, int> id;
        std::vector<std::shared_ptr<CFGNode>> ordered;
        std::deque<std::shared_ptr<CFGNode>> q;

        auto enqueue = [&](const std::shared_ptr<CFGNode>& n) {
            if (!n) return;
            CFGNode* key = n.get();
            if (id.find(key) == id.end()) {
                int nid = static_cast<int>(ordered.size());
                id[key] = nid;
                ordered.push_back(n);
                q.push_back(n);
            }
        };

        enqueue(entry);
        while (!q.empty()) {
            auto cur = q.front(); q.pop_front();
            auto t = cur->getNextNode();
            auto f = cur->getNextFalseNode();
            if (t) enqueue(t);
            if (f) enqueue(f);
        }

        // 2) Print human-readable table (adjacency with labels)
        cout << "======== CFG TABLE: FunctionDefinition #" << fi << " ========" << endl;
        cout << "Total nodes: " << ordered.size() << endl;
        cout << "Idx | Level | Kind                | Flags        | Next  | False | Code/Label" << endl;
        cout << "----+-------+---------------------+--------------+-------+-------+----------------------------------------" << endl;

        for (size_t idx = 0; idx < ordered.size(); ++idx) {
            auto n = ordered[idx];
            auto t = n->getNextNode();
            auto f = n->getNextFalseNode();
            int tid = (t ? id[t.get()] : -1);
            int fid = (f ? id[f.get()] : -1);

            std::string flags;
            if (n->isFuncDef) flags += "F";
            if (n->isVarDef)  { if (!flags.empty()) flags += ","; flags += "V"; }
            if (n->isIf)      { if (!flags.empty()) flags += ","; flags += "IF"; }
            if (n->isWhile)   { if (!flags.empty()) flags += ","; flags += "WH"; }
            if (n->isFor)     { if (!flags.empty()) flags += ","; flags += "FOR"; }
            if (n->isLoop)    { if (!flags.empty()) flags += ","; flags += "LOOP"; }
            if (n->hasCallExpr){ if (!flags.empty()) flags += ","; flags += "CALL"; }
            if (flags.empty()) flags = "-";

            std::string kind = getKindName(n);
            if (kind.size() > 21) kind = kind.substr(0, 21) + "...";

            cout << std::setw(3) << idx << " | "
                 << std::setw(5) << n->nodeLevel << " | "
                 << std::setw(21) << kind << " | "
                 << std::setw(12) << flags << " | "
                 << std::setw(5) << tid << " | "
                 << std::setw(5) << fid << " | "
                 << sanitize(nodeLabel(n), 60)
                 << endl;
        }
        cout << endl;

        // 3) Also emit Graphviz DOT so you can render a real graph
        std::ostringstream dot;
        dot << "digraph CFG_" << fi << " {\n";
        dot << "  rankdir=LR;\n";
        dot << "  node [fontname=\"Helvetica\"];\n";

        for (size_t idx = 0; idx < ordered.size(); ++idx) {
            auto n = ordered[idx];
            std::string label = std::to_string(idx) + ": " + nodeLabel(n);
            // escape quotes
            for (char& c : label) if (c == '\"') c = '\'';
            dot << "  " << idx << " [shape=" << shapeOf(n) << ", label=\"" << label << "\"];\n";
        }
        for (size_t idx = 0; idx < ordered.size(); ++idx) {
            auto n = ordered[idx];
            auto t = n->getNextNode();
            auto f = n->getNextFalseNode();
            if (t) {
                int tid = id[t.get()];
                dot << "  " << idx << " -> " << tid << " [label=\"next\"];\n";
            }
            if (f) {
                int fid = id[f.get()];
                dot << "  " << idx << " -> " << fid << " [style=dashed, label=\"false\"];\n";
            }
        }
        dot << "}\n";

        // 4) Print DOT to stdout and also save to file
        cout << "======== CFG DOT (Function #" << fi << ") ========" << endl;
        cout << dot.str() << endl;

        char filename[256];
        std::snprintf(filename, sizeof(filename), "cfg_func_%zu.dot", fi);
        std::ofstream ofs(filename, std::ios::out | std::ios::trunc);
        if (ofs.is_open()) {
            ofs << dot.str();
            ofs.close();
            cout << "[INFO] DOT written to: " << filename << endl;
            cout << "       Render with: dot -Tpng " << filename << " -o cfg_func_" << fi << ".png" << endl;
        } else {
            cout << "[WARN] Unable to open file for DOT output: " << filename << endl;
        }

        cout << endl;
    }
}

void printMatrixFileContent(const std::string& filename) {

    std::ifstream file(filename);

    if (file.is_open()) {

        std::string line;

        while (std::getline(file, line)) {

            std::cout << line << std::endl;

        }

        file.close();

    } else {

        std::cerr << "无法打开文件：" << filename << std::endl;

    }

}



void SyntaxNamePrinter::printCFG_DFS(int maxloop, int maxpaths) {
    int pathCount = 0;
    std::string matrixFileName = "matrix.txt";   

    loopCount.clear();
    loopCount.resize(maxdepth, 0);

    for (auto& funcNode : funcDefStack_) {
        std::vector<bool> pathCoverage(maxdepth, false);
        std::vector<PathDecision> decisions;

        std::ofstream ofs(matrixFileName, std::ios::out | std::ios::trunc);
        ofs.close();

        int maxMems = -1;
        int minMems = std::numeric_limits<int>::max();

        auto start = std::chrono::high_resolution_clock::now();

        DFS(funcNode, pathCoverage, decisions, 0, pathCount, maxloop, maxpaths, maxMems, minMems);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "[DFS TIME COST]: " << diff.count() << " seconds" << std::endl;

        std::cout << "[MATRIX]:" << std::endl;
        printMatrixFileContent(matrixFileName);

        std::cout << "[DFS MAX MEMS]: " << maxMems << std::endl;
        std::cout << "[DFS MIN MEMS]: " << (minMems == std::numeric_limits<int>::max() ? 0 : minMems) << std::endl;

        auto coverageMatrix = ReadCoverageMatrix(matrixFileName);
        SolveLinearProgram(coverageMatrix);
    }
}
// ===== printCFG_DFS2：可按需把 pathCount 挪到函数内重置 =====
void SyntaxNamePrinter::printCFG_DFS2(int maxloop, int maxpaths, bool enableVolce) {
    std::string matrixFileName = "matrix2.txt";

    for (auto& funcNode : funcDefStack_) {
        int pathCount = 0; // 建议每个函数单独计数，避免跨函数累加
        loopCount.clear();
        loopCount.resize(maxdepth, 0);

        std::vector<bool> pathCoverage(maxdepth, false);
        std::vector<PathDecision> decisions;

        std::ofstream ofs(matrixFileName, std::ios::out | std::ios::trunc);
        ofs.close();

        feasiblePaths_.clear();
        totalVolceCount_ = 0;
        feasCache.clear();

        maxmem = -1;
        minmem = std::numeric_limits<int>::max();

        auto start = std::chrono::high_resolution_clock::now();
        DFS2(funcNode, pathCoverage, decisions, 0, pathCount, maxloop, maxpaths, enableVolce);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;

        std::cout << "[DFS TIME COST]: " << diff.count() << " seconds" << std::endl;
        printFeasiblePathSummary(enableVolce);
        std::cout << "[MATRIX]:" << std::endl;
        printMatrixFileContent(matrixFileName);
        std::cout << "[DFS MAX MEMS]: " << maxmem << std::endl;
        std::cout << "[DFS MIN MEMS]: "
                  << (minmem == std::numeric_limits<int>::max() ? 0 : minmem) << std::endl;

        auto coverageMatrix = ReadCoverageMatrix(matrixFileName);
        SolveLinearProgram(coverageMatrix);
    }
}

void SyntaxNamePrinter::recordFeasiblePath(int pathIndex,
                                           int mem,
                                           const std::string& path,
                                           const std::optional<std::uint64_t>& volceCount) {
    feasiblePaths_.push_back(FeasiblePathSummary{pathIndex, mem, path, volceCount});
    if (volceCount) {
        totalVolceCount_ += *volceCount;
    }
}

void SyntaxNamePrinter::printFeasiblePathSummary(bool enableVolce) const {
    std::cout << "[FEASIBLE PATHS]:" << std::endl;
    std::ofstream csvFile;
    if (enableVolce) {
        csvFile.open("volce_paths.csv", std::ios::out | std::ios::trunc);
        if (csvFile.is_open()) {
            csvFile << "path_index,mems,volce,probability\n";
        }
    }

    if (feasiblePaths_.empty()) {
        std::cout << "  (none)" << std::endl;
        return;
    }

    double weightedMemSum = 0.0;
    double probSum = 0.0;
    double probWeightedByMemSum = 0.0;
    double memSumForProb = 0.0;

    for (const auto& info : feasiblePaths_) {
        std::cout << "  [path " << info.pathIndex << "] mem=" << info.mem;
        std::optional<double> prob;
        if (enableVolce) {
            if (info.volceCount) {
                const double probValue = totalVolceCount_ > 0
                                             ? static_cast<double>(*info.volceCount)
                                                   / static_cast<double>(totalVolceCount_)
                                             : 0.0;
                prob = probValue;
                std::cout << " volce=" << *info.volceCount << " prob=" << probValue;
                weightedMemSum += static_cast<double>(info.mem) * probValue;
                probSum += probValue;
                probWeightedByMemSum += probValue * static_cast<double>(info.mem);
                memSumForProb += static_cast<double>(info.mem);
            } else {
                std::cout << " volce=N/A prob=N/A";
            }
        }
        std::cout << std::endl;
        std::cout << "    path=" << info.path << std::endl;

        if (enableVolce && csvFile.is_open()) {
            csvFile << info.pathIndex << "," << info.mem << ",";
            if (info.volceCount) {
                csvFile << *info.volceCount;
            }
            csvFile << ",";
            if (prob) {
                csvFile << *prob;
            }
            csvFile << "\n";
        }
    }

    if (enableVolce && totalVolceCount_ > 0) {
        if (probSum > 0.0) {
            const double avgMemWeightedByProb = weightedMemSum / probSum;
            std::cout << "[WEIGHTED AVG MEMS BY PROB]: " << avgMemWeightedByProb << std::endl;
        } else {
            std::cout << "[WEIGHTED AVG MEMS BY PROB]: N/A" << std::endl;
        }
        if (memSumForProb > 0.0) {
            const double avgProbWeightedByMem = probWeightedByMemSum / memSumForProb;
            std::cout << "[WEIGHTED AVG PROB BY MEMS]: " << avgProbWeightedByMem << std::endl;
        } else {
            std::cout << "[WEIGHTED AVG PROB BY MEMS]: N/A" << std::endl;
        }
    } else if (enableVolce) {
        std::cout << "[WEIGHTED AVG MEMS BY PROB]: N/A" << std::endl;
        std::cout << "[WEIGHTED AVG PROB BY MEMS]: N/A" << std::endl;
    }
}


void SyntaxNamePrinter::DFS(
    std::shared_ptr<CFGNode> node,
    std::vector<bool>& pathCoverage,
    std::vector<PathDecision>& decisions,
    int depth,
    int& pathCount,
    int maxloop,
    int maxpaths,
    int& maxMems,
    int& minMems
) {
    if (maxpaths > 0 && pathCount >= maxpaths) return;
    if (!node) return;

    // 标记当前节点已访问
    if (node->depth >= 0)
        pathCoverage[node->depth] = true;

    auto appendAndEvalLeaf = [&](bool includeCode) {
        bool pushed = false;
        if (includeCode && !node->isLoop && !node->isIf &&
            !node->isFuncDef && !(node->isVarDef && node->nodeLevel == 3)) {
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::Code});
            pushed = true;
        }

        EpatRunner runner(vartemp);
        auto eval = runner.solve(decisions);
        const bool feasible = eval.status == result::feasible;
        if (feasible) {
            if (eval.mem > maxMems) maxMems = eval.mem;
            if (eval.mem < minMems) minMems = eval.mem;
        }

        auto script = runner.render(decisions);
        processPathResult(eval, script, pathCoverage, pathCount, depth);
        ++pathCount;

        if (pushed) decisions.pop_back();
    };

    // 叶子节点处理
    if (node->isReturn || !node->getNextNode()) {
        appendAndEvalLeaf(true);
        return;
    }

    if (node->isLoop) {
        if (node->isFor) {
            // False分支（循环终止）
            if (loopCount[node->depth] >= maxloop) {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
                loopCount[node->depth] = 0;
                DFS(node->getNextFalseNode()->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
                decisions.pop_back();
                return;
            }
            // 第一次进入时补初始化
            bool pushedInit = false;
            if (loopCount[node->depth] == 0 && node->initstmt_str != ";") {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopInit});
                pushedInit = true;
            }

            // True分支（进入循环体）
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopUpdate});
            loopCount[node->depth]++;
            DFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
            decisions.pop_back();
            decisions.pop_back();
            if (pushedInit) decisions.pop_back();

        }

        if (node->isWhile) {
            // False分支（循环终止）
            if (loopCount[node->depth] >= maxloop) {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
                loopCount[node->depth] = 0;
                DFS(node->getNextFalseNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
                decisions.pop_back();
                return;
            }
            // True分支（进入循环体）
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
            loopCount[node->depth]++;
            DFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
            decisions.pop_back();
        }
    }

    if (node->isIf) {
        // True分支

        temp_loopCount[depth]=loopCount;
        auto temp_pathcoverage = pathCoverage;
        decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
        DFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
        decisions.pop_back();

        // False分支
        for (int i=node->depth+1;i<maxdepth;i++)
            pathCoverage[i]=false;//对于之前下面的覆盖率清零；

        pathCoverage = temp_pathcoverage;
        loopCount=temp_loopCount[depth];
        decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
        DFS(node->getNextFalseNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
        decisions.pop_back();
        return;
    }

    if (node->isFuncDef || (node->isVarDef && node->nodeLevel == 3)) {
        DFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
        return;
    }

    decisions.push_back(PathDecision{node.get(), PathDecisionKind::Code});
    DFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, maxMems, minMems);
    decisions.pop_back();
}

#include <iomanip>  // 注意：用于 setw 对齐

// 开始前清空矩阵
void SyntaxNamePrinter::startBranchMatrix() {
    branchCovMatrix_.clear();
}

// 在 DFS 叶子时把一条路径写入矩阵（自动填充到 2*maxdepth 列）
void SyntaxNamePrinter::pushBranchRow(const std::vector<bool>& row) {
    const int COLS = std::max(0, 2 * maxdepth);   // 每个 depth 两列：T/F
    std::vector<int> r(COLS, 0);
    const int n = std::min<int>(COLS, row.size());
    for (int i = 0; i < n; ++i) r[i] = row[i] ? 1 : 0;
    branchCovMatrix_.push_back(std::move(r));
}

// 统一对齐打印矩阵
void SyntaxNamePrinter::printBranchMatrix() {
    const int COLS = std::max(0, 2 * maxdepth);
    std::cout << "[MATRIX]:\n";
    for (const auto& r : branchCovMatrix_) {
        for (int c = 0; c < COLS; ++c) {
            std::cout << std::setw(2) << r[c] << ' ';
        }
        std::cout << '\n';
    }
}
void SyntaxNamePrinter::DFS2(std::shared_ptr<CFGNode> node,
                             std::vector<bool>& pathCoverage,
                             std::vector<PathDecision>& decisions,
                             int depth,
                             int& pathCount,
                             int maxloop,
                             int maxpaths,
                             bool enableVolce)
{
    if (maxpaths > 0 && pathCount >= maxpaths) return;
    if (!node) return;

    // 原有：按当前 pathCoverage 扩容
    auto ensure_cov = [&](int d){
        int need = 2 * d + 2;
        if ((int)pathCoverage.size() < need) pathCoverage.resize(need, false);
    };
    // 新增：对任意向量 vec 扩容（关键修复点：用于 cov_t/cov_f 等分支副本）
    auto ensure_cov_vec = [&](std::vector<bool>& vec, int d){
        int need = 2 * d + 2;
        if ((int)vec.size() < need) vec.resize(need, false);
    };
    // 原有：循环计数扩容
    auto ensure_loop = [&](int d){
        if (d < 0) return;
        if ((int)loopCount.size() <= d) loopCount.resize(d + 1, 0);
    };
    // 新增：叶子统一对齐（把该行补到 2*maxdepth 列）
    auto pad_to_full_cols = [&](std::vector<bool>& vec){
        int want = 2 * std::max(0, maxdepth);
        if ((int)vec.size() < want) vec.resize(want, false);
    };
    // 非条件普通语句：同时打 T/F 覆盖位
    if (node->depth >= 0 && !node->isCondition) {
        ensure_cov(node->depth);
        pathCoverage[2 * node->depth]     = true;
        pathCoverage[2 * node->depth + 1] = true;
    }

    // 叶子：return 或 无后继（将当前节点代码补入，再判可行）
    if (node->isReturn || !node->getNextNode()) {
        bool pushed = false;
        if (!node->isLoop && !node->isIf && !node->isFuncDef && !(node->isVarDef && node->nodeLevel == 3)) {
            const std::string code = node->getCode();
            if (!code.empty()) {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::Code});
                pushed = true;
            }
        }
        EpatRunner runner(vartemp);
        auto eval = runner.solve(decisions);
        if (eval.status == result::feasible) {
            if (eval.mem > maxmem) maxmem = eval.mem;
            if (eval.mem < minmem) minmem = eval.mem;
        }

        // 关键修复：叶子处将覆盖向量统一补齐到 2*maxdepth 列，保证输出矩阵行对齐
        pad_to_full_cols(pathCoverage);

        auto script = runner.render(decisions);
        processPathResult2(eval, script, pathCoverage, pathCount, depth, enableVolce);
        ++pathCount;
        if (pushed) decisions.pop_back();
        return;
    }

    // ===================== FOR =====================
    if (node->isLoop && node->isFor) {
        const int d = node->depth;
        ensure_loop(d);

        // 清理更深层的展开计数，避免跨层污染
        if (!loopCount.empty()) {
            for (int k = d + 1, sz = (int)loopCount.size(); k < sz; ++k) loopCount[k] = 0;
        }

        // 为 T/F 分支分别保存快照
        const std::vector<bool>  snap_cov  = pathCoverage;
        const std::vector<int>   snap_lc   = loopCount;

        // True：@(cond) → 体（顺着 CFG 的 next 走）
        if (loopCount[d] < maxloop) {
            auto        cov_t = snap_cov;
            auto        lc_t  = snap_lc;

            // 关键修复：对 cov_t 本身扩容后再写位
            ensure_cov_vec(cov_t, d);
            cov_t[2 * d] = true;

            // 本层展开+1，只影响 True 这条路径
            if ((int)lc_t.size() <= d) lc_t.resize(d + 1, 0);
            lc_t[d] += 1;

            // 下钻（用 True 的 loop 计数）
            auto saved = loopCount;
            loopCount  = lc_t;
            if (loopCount[d] == 1 && !node->initstmt_str.empty() && node->initstmt_str != ";") {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopInit});
            }
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopUpdate});
            DFS2(node->getNextNode(), cov_t, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce);
            decisions.pop_back();
            decisions.pop_back();
            if (loopCount[d] == 1 && !node->initstmt_str.empty() && node->initstmt_str != ";") {
                decisions.pop_back();
            }
            loopCount = saved;
        }

        // False：@(!(cond)) → 走 CFG 的 false 边（join/end）
        {
            auto        cov_f = snap_cov;
            ensure_cov_vec(cov_f, d);
            cov_f[2 * d + 1] = true;

            decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
            DFS2(node->getNextFalseNode(), cov_f, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce);
            decisions.pop_back();
        }
        return;
    }

    // ===================== WHILE =====================
    if (node->isLoop && node->isWhile) {
        const int d = node->depth;
        ensure_loop(d);

        // 清理更深层展开计数
        if (!loopCount.empty()) {
            for (int k = d + 1, sz = (int)loopCount.size(); k < sz; ++k) loopCount[k] = 0;
        }

        // 为 T/F 分支保存快照
        const std::vector<bool>  snap_cov  = pathCoverage;
        const std::vector<int>   snap_lc   = loopCount;

        // True：@(cond) → 体（顺着 CFG 的 next 走）
        if (loopCount[d] < maxloop) {
            auto        cov_t = snap_cov;
            auto        lc_t  = snap_lc;

            ensure_cov_vec(cov_t, d);
            cov_t[2 * d] = true;

            if ((int)lc_t.size() <= d) lc_t.resize(d + 1, 0);
            lc_t[d] += 1;

            auto saved = loopCount;
            loopCount  = lc_t;
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
            DFS2(node->getNextNode(), cov_t, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce);
            decisions.pop_back();
            loopCount = saved;
        }

        // False：@(!(cond)) → 走 CFG 的 false 边（join/end）
        {
            auto        cov_f = snap_cov;
            ensure_cov_vec(cov_f, d);
            cov_f[2 * d + 1] = true;

            decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
            DFS2(node->getNextFalseNode(), cov_f, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce);
            decisions.pop_back();
        }
        return;
    }

    // ===================== IF =====================
    if (node->isIf) {
        const int d   = node->depth;
        const int idx = (d < 1000 ? d : 999); // 兼容你已有的固定槽位

        // 保存快照到固定数组槽位
        temp_pathCoverage[idx] = pathCoverage;
        temp_loopCount[idx]    = loopCount;

        // True
        {
            auto        cov_t = pathCoverage;
            ensure_cov_vec(cov_t, d);
            cov_t[2 * d] = true;

            decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
            DFS2(node->getNextNode(), cov_t, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce);
            decisions.pop_back();
        }

        // False（恢复快照再走）
        {
            pathCoverage = temp_pathCoverage[idx];
            loopCount    = temp_loopCount[idx];

            auto        cov_f = pathCoverage;
            ensure_cov_vec(cov_f, d);
            cov_f[2 * d + 1] = true;

            decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
            DFS2(node->getNextFalseNode(), cov_f, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce);
            decisions.pop_back();
        }
        return;
    }

    // ===================== 其它顺序节点 =====================
    if (node->isFuncDef || (node->isVarDef && node->nodeLevel == 3)) {
        DFS2(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce);
        return;
    }

    decisions.push_back(PathDecision{node.get(), PathDecisionKind::Code});
    DFS2(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, enableVolce);
    decisions.pop_back();
}


// Helper: LoopMap简化key
// ========== 辅助：循环计数序列化（与 DFS2 统一用“按节点指针计数”） ==========
static std::string LoopMapKey(const std::unordered_map<CFGNode*, int>& mp) {
    std::vector<std::pair<uintptr_t,int>> v;
    v.reserve(mp.size());
    for (const auto& kv : mp) v.push_back({reinterpret_cast<uintptr_t>(kv.first), kv.second});
    std::sort(v.begin(), v.end());
    std::string res;
    for (auto &p : v) {
        res += std::to_string(p.first);
        res += ":";
        res += std::to_string(p.second);
        res += "|";
    }
    return res;
}


// ========== 可行性缓存，避免重复求解 ==========
namespace psy {
namespace C {
std::unordered_map<std::string, bool> feasCache;

// 仅在可行性判定时拼接 vartemp；其他地方一律使用 raw path
inline bool feasibleWithVartemp(
    SyntaxNamePrinter* self,
    const std::vector<PathDecision>& decisions,
    const std::string& rawPath) {
    return self->isPathFeasible(decisions, rawPath);
}

inline bool isPathFeasibleCached(
    SyntaxNamePrinter* self,
    const std::vector<PathDecision>& decisions,
    const std::string& fullExpr) {
    auto it = feasCache.find(fullExpr);
    if (it != feasCache.end()) return it->second;

    bool ok = feasibleWithVartemp(self, decisions, fullExpr.substr(self->vartemp.size()));
    feasCache.emplace(fullExpr, ok);
    return ok;
}
}  // namespace C
}  // namespace psy

// ========== 核心：与新 CFG 对齐的 DP ==========
// 说明：依赖以下已存在成员/类型：
// - struct PathInfo { int mems; std::string path; bool feasible; ... };
// - std::unordered_map<std::tuple<CFGNode*, std::string, std::string>, PathInfo> dpMemo;
// - std::string LoopMapKey(const std::unordered_map<CFGNode*, int>&);
// - bool feasibleWithVartemp(SyntaxNamePrinter*, const std::string&);
// - bool isPathFeasible(const std::string&);
// - std::string vartemp;
// - CFGNode 的接口：isFuncDef/isVarDef/isIf/isLoop/isWhile/isFor/isReturn/cond_str/initstmt_str/expr_str
//                    getCode()/getMem(vartemp)/getNextNode()/getNextFalseNode()

PathInfo SyntaxNamePrinter::MaxMemsDP(
    const std::shared_ptr<CFGNode>& entry,
    int maxloop,
    std::string pathPrefix,  // raw path 前缀（不含 vartemp）
    int depth,
    std::unordered_map<CFGNode*, int>& loopUnrollMap,
    std::vector<PathDecision> decisions
) {
    auto makeKey = [&](CFGNode* node) {
        // 你的 .h 里 dpMemo 的类型是 unordered_map<tuple<CFGNode*,string,string>, PathInfo>
        // 第三个字段传空串，等效于 (node, LoopMapKey)
        return std::make_tuple(node, LoopMapKey(loopUnrollMap), std::string());
    };

    if (depth > 1000) return PathInfo(0, pathPrefix, false);
    if (!entry)        return PathInfo(0, pathPrefix, true);

    // 1) 命中缓存（缓存的是“后缀”，此处回放成完整结果）
    {
        auto key = makeKey(entry.get());
        auto it  = dpMemo.find(key);
        if (it != dpMemo.end()) {
            const PathInfo& cachedSuffix = it->second; // cachedSuffix.path 是 raw 的“后缀”
            PathInfo out;
            out.feasible = cachedSuffix.feasible;
            out.mems     = cachedSuffix.mems + entry->getMem(vartemp); // 加上当前节点 mem
            out.path     = pathPrefix + cachedSuffix.path;             // 前缀 + 后缀
            return out;
        }
    }

    const int curMem = entry->getMem(vartemp);

    // 工具：将完整 child 结果写回“后缀缓存”（移除 pathPrefix，并去掉当前节点 mem）
    auto writeSuffixMemo = [&](const PathInfo& fullRes) {
        PathInfo suffix = fullRes;
        if (suffix.path.size() >= pathPrefix.size() &&
            suffix.path.compare(0, pathPrefix.size(), pathPrefix) == 0) {
            suffix.path.erase(0, pathPrefix.size());
        }
        // 缓存中 mems 不含当前节点 mem
        int suffixMemsNoCur = std::max(0, suffix.mems - curMem);
        dpMemo[makeKey(entry.get())] = PathInfo(suffixMemsNoCur, suffix.path, suffix.feasible);
    };

    // 工具：普通顺序节点 的处理
    auto appendNormalThenNext = [&](const std::string& code,
                                    std::shared_ptr<CFGNode> next,
                                    std::vector<PathDecision> nextDecisions) {
        std::string curPath = pathPrefix;
        if (!code.empty()) {
            curPath += code;
            curPath += "\n";
            nextDecisions.push_back(PathDecision{entry.get(), PathDecisionKind::Code});
        }

        const std::string fullExpr = vartemp + curPath;
        if (!isPathFeasibleCached(this, nextDecisions, fullExpr)) {
            dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
            return PathInfo(0, curPath, false);
        }
        PathInfo child = MaxMemsDP(next, maxloop, curPath, depth + 1, loopUnrollMap, nextDecisions);
        if (!child.feasible) {
            dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
            return PathInfo(0, curPath, false);
        }
        child.mems += curMem;
        writeSuffixMemo(child);
        return child;
    };

    // 2) 终止：return 或 无后继（注意无后继也属于一个可能的终止点）
    if (entry->isReturn || !(entry->getNextNode())) {
        std::string curPath = pathPrefix;
        auto curDecisions   = decisions;
        // 与原行为一致：对 loop/if/funcDef/局部定义(3级)不重复追加代码
        if (!entry->isLoop && !entry->isIf && !entry->isFuncDef && !(entry->isVarDef && entry->nodeLevel == 3)) {
            std::string code = entry->getCode();
            if (!code.empty()) {
                curPath += code;
                curPath += "\n";
                curDecisions.push_back(PathDecision{entry.get(), PathDecisionKind::Code});
            }
        }
        if (!isPathFeasibleCached(this, curDecisions, vartemp + curPath)) {
            dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
            return PathInfo(0, curPath, false);
        }
        // 终止时：后缀 = (curPath - pathPrefix)，mems(后缀) = 0
        std::string suffixPath;
        if (curPath.size() >= pathPrefix.size() &&
            curPath.compare(0, pathPrefix.size(), pathPrefix) == 0) {
            suffixPath = curPath.substr(pathPrefix.size());
        }
        dpMemo[makeKey(entry.get())] = PathInfo(0, suffixPath, true);
        return PathInfo(curMem, curPath, true);
    }

    // 3) 跳过定义节点（函数定义、局部变量定义在 3 层）
    if (entry->isFuncDef || (entry->isVarDef && entry->nodeLevel == 3)) {
        PathInfo child = MaxMemsDP(entry->getNextNode(), maxloop, pathPrefix, depth + 1, loopUnrollMap, decisions);
        if (!child.feasible) {
            dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
            return child;
        }
        child.mems += curMem;
        writeSuffixMemo(child);
        return child;
    }

    // 4) 条件分支 —— 严格用 CFG 的 true/false 边
    if (entry->isIf) {
        std::string curPath = pathPrefix;

        // True 分支：entry->getNextNode()
        std::string tPath = curPath + "@(" + entry->cond_str + ");\n";
        auto tDecisions   = decisions;
        tDecisions.push_back(PathDecision{entry.get(), PathDecisionKind::TrueBranch});
        PathInfo tInfo(0, tPath, false);
        if (isPathFeasibleCached(this, tDecisions, vartemp + tPath) && entry->getNextNode()) {
            tInfo = MaxMemsDP(entry->getNextNode(), maxloop, tPath, depth + 1, loopUnrollMap, tDecisions);
            if (tInfo.feasible) tInfo.mems += curMem;
        }

        // False 分支：entry->getNextFalseNode()
        std::string fPath = curPath + "@(!(" + entry->cond_str + "));\n";
        auto fDecisions   = decisions;
        fDecisions.push_back(PathDecision{entry.get(), PathDecisionKind::FalseBranch});
        PathInfo fInfo(0, fPath, false);
        if (isPathFeasibleCached(this, fDecisions, vartemp + fPath) && entry->getNextFalseNode()) {
            fInfo = MaxMemsDP(entry->getNextFalseNode(), maxloop, fPath, depth + 1, loopUnrollMap, fDecisions);
            if (fInfo.feasible) fInfo.mems += curMem;
        }

        if (!tInfo.feasible && !fInfo.feasible) {
            dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
            return PathInfo(0, curPath, false);
        }
        PathInfo best = (tInfo.feasible && (!fInfo.feasible || tInfo.mems >= fInfo.mems)) ? tInfo : fInfo;
        writeSuffixMemo(best);
        return best;
    }

    // 5) 循环 —— 与新 CFG 对齐：
    //     while 的 False 直接走 getNextFalseNode()（end/join），True 走体首 getNextNode()
    //     for   的 False 直接走 getNextFalseNode()（end/join），True 走体首 getNextNode()，每轮末尾追加 expr_str
    if (entry->isLoop) {
        auto& unroll = loopUnrollMap[entry.get()];
        std::string curPath = pathPrefix;
        auto curDecisions   = decisions;

        // 5.1) for 循环
        if (entry->isFor) {
            // 首入 for：追加 initstmt
            if (unroll == 0 && !entry->initstmt_str.empty() && entry->initstmt_str != ";") {
                curPath += entry->initstmt_str;
                curPath += "\n";
                curDecisions.push_back(PathDecision{entry.get(), PathDecisionKind::LoopInit});
                if (!isPathFeasibleCached(this, curDecisions, vartemp + curPath)) {
                    dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
                    return PathInfo(0, curPath, false);
                }
            }

            // 达到展开上限：走 false → end/join
            if (unroll >= maxloop) {
                std::string fPath = curPath + "@(!(" + entry->cond_str + "));\n";
                auto fDecisions   = curDecisions;
                fDecisions.push_back(PathDecision{entry.get(), PathDecisionKind::FalseBranch});
                if (!isPathFeasibleCached(this, fDecisions, vartemp + fPath) || !entry->getNextFalseNode()) {
                    dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
                    return PathInfo(0, fPath, false);
                }
                PathInfo child = MaxMemsDP(entry->getNextFalseNode(), maxloop, fPath, depth + 1, loopUnrollMap, fDecisions);
                if (!child.feasible) {
                    dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
                    return PathInfo(0, fPath, false);
                }
                child.mems += curMem;
                writeSuffixMemo(child);
                return child;
            }

            // True：一轮迭代（cond 成立 → 体首），迭代末尾追加 expr_str
            {
                std::string tPath = curPath + "@(" + entry->cond_str + ");\n";
                auto tDecisions   = curDecisions;
                tDecisions.push_back(PathDecision{entry.get(), PathDecisionKind::TrueBranch});
                if (isPathFeasibleCached(this, tDecisions, vartemp + tPath) && entry->getNextNode()) {
                    unroll++;
                    PathInfo tChild = MaxMemsDP(entry->getNextNode(), maxloop, tPath, depth + 1, loopUnrollMap, tDecisions);
                    unroll--;
                    if (tChild.feasible) {
                        if (!entry->expr_str.empty()) {
                            tChild.path += entry->expr_str + ";\n";
                            auto updateDecisions = tDecisions;
                            updateDecisions.push_back(PathDecision{entry.get(), PathDecisionKind::LoopUpdate});
                            if (!isPathFeasibleCached(this, updateDecisions, vartemp + tChild.path)) {
                                dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
                                return PathInfo(0, tChild.path, false);
                            }
                            tDecisions.swap(updateDecisions);
                        }
                        tChild.mems += curMem;
                        writeSuffixMemo(tChild);
                        return tChild;
                    }
                }
            }
            // False：退出 → end/join
            {
                std::string fPath = curPath + "@(!(" + entry->cond_str + "));\n";
                auto fDecisions   = curDecisions;
                fDecisions.push_back(PathDecision{entry.get(), PathDecisionKind::FalseBranch});
                if (!isPathFeasibleCached(this, fDecisions, vartemp + fPath) || !entry->getNextFalseNode()) {
                    dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
                    return PathInfo(0, fPath, false);
                }
                PathInfo child = MaxMemsDP(entry->getNextFalseNode(), maxloop, fPath, depth + 1, loopUnrollMap, fDecisions);
                if (!child.feasible) {
                    dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
                    return PathInfo(0, fPath, false);
                }
                child.mems += curMem;
                writeSuffixMemo(child);
                return child;
            }
        }

        // 5.2) while 循环
        if (entry->isWhile) {
            if (unroll >= maxloop) {
                // 直接走 false → end/join
                std::string fPath = curPath + "@(!(" + entry->cond_str + "));\n";
                auto fDecisions   = curDecisions;
                fDecisions.push_back(PathDecision{entry.get(), PathDecisionKind::FalseBranch});
                if (!isPathFeasibleCached(this, fDecisions, vartemp + fPath) || !entry->getNextFalseNode()) {
                    dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
                    return PathInfo(0, fPath, false);
                }
                PathInfo child = MaxMemsDP(entry->getNextFalseNode(), maxloop, fPath, depth + 1, loopUnrollMap, fDecisions);
                if (!child.feasible) {
                    dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
                    return PathInfo(0, fPath, false);
                }
                child.mems += curMem;
                writeSuffixMemo(child);
                return child;
            }

            // True：进入体首（CFG true 边=Next）
            {
                std::string tPath = curPath + "@(" + entry->cond_str + ");\n";
                auto tDecisions   = curDecisions;
                tDecisions.push_back(PathDecision{entry.get(), PathDecisionKind::TrueBranch});
                if (isPathFeasibleCached(this, tDecisions, vartemp + tPath) && entry->getNextNode()) {
                    unroll++;
                    PathInfo tChild = MaxMemsDP(entry->getNextNode(), maxloop, tPath, depth + 1, loopUnrollMap, tDecisions);
                    unroll--;
                    if (tChild.feasible) {
                        tChild.mems += curMem;
                        writeSuffixMemo(tChild);
                        return tChild;
                    }
                }
            }
            // False：退出 → end/join
            {
                std::string fPath = curPath + "@(!(" + entry->cond_str + "));\n";
                auto fDecisions   = curDecisions;
                fDecisions.push_back(PathDecision{entry.get(), PathDecisionKind::FalseBranch});
                if (!isPathFeasibleCached(this, fDecisions, vartemp + fPath) || !entry->getNextFalseNode()) {
                    dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
                    return PathInfo(0, fPath, false);
                }
                PathInfo child = MaxMemsDP(entry->getNextFalseNode(), maxloop, fPath, depth + 1, loopUnrollMap, fDecisions);
                if (!child.feasible) {
                    dpMemo[makeKey(entry.get())] = PathInfo(0, std::string(), false);
                    return PathInfo(0, fPath, false);
                }
                child.mems += curMem;
                writeSuffixMemo(child);
                return child;
            }
        }
    }

    // 6) 普通顺序节点
    {
        std::string code = entry->getCode();
        return appendNormalThenNext(code, entry->getNextNode(), decisions);
    }
}


// ========== 驱动：与 DFS2 保持同样的 maxloop 和输出 ==========
// 改动：无可行路径时输出 "MEMS: -1"
void SyntaxNamePrinter::printCFG_greedyDFS(int maxloop, int maxpaths, bool enableVolce) {
    for (const auto& funcNode : funcDefStack_) {
        dpMemo.clear();  // 每个函数入口前清空 memo

        std::unordered_map<CFGNode*, int> loopUnrollMap;

        auto start = std::chrono::high_resolution_clock::now();
        PathInfo result = MaxMemsDP(funcNode, maxloop, "", 0, loopUnrollMap, {}); // raw path
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;

        std::cout << "[MAX MEMS PATH]:\n";
        const std::string fullPath = vartemp + result.path; // 只在这里拼接一次
        if (!result.feasible || !isPathFeasible(result.path)) {
            // 按要求：没有可行路径也输出 MEMS=-1
            // 如需查看组合出的路径，可取消下一行注释
            // std::cout << fullPath << "\n";
            std::cout << "MEMS: -1" << std::endl;
            std::cout << "[VolCE] N/A" << std::endl;
        } else {
            std::cout << fullPath << std::endl;
            std::cout << "MEMS: " << result.mems << std::endl;
            if (enableVolce) {
                const auto eval = EpatRunner("").solveScript(fullPath);
                const auto volceResult = runVolce(eval.smt, kVolceLowerBound, kVolceUpperBound);
                if (volceResult) {
                    std::cout << "[VolCE]" << std::endl;
                    std::cout << volceResult->output << std::endl;
                } else {
                    std::cout << "[VolCE] N/A" << std::endl;
                }
            } else {
                std::cout << "[VolCE] N/A" << std::endl;
            }
        }
        std::cout << "[DP TIME COST]: " << diff.count() << " seconds" << std::endl;
    }
}




// 贪心+剪枝 DFS（只走可行路径，分支贪心选mems最大，循环最大展开）
void SyntaxNamePrinter::GreedyDFS(
    std::shared_ptr<CFGNode> node,
    std::vector<bool>& pathCoverage,
    std::vector<PathDecision> decisions,
    int depth,
    int& pathCount,
    int maxloop,
    int maxpaths,
    int currentMem,
    std::string& bestPath,
    int& bestMem)
{
    if (!node || (maxpaths > 0 && pathCount >= maxpaths)) return;
    if (node->depth >= 0) pathCoverage[node->depth] = true;
    currentMem += node->getMem(vartemp);

    auto leafEval = [&](bool includeCode) {
        bool pushed = false;
        if (includeCode && !node->isLoop && !node->isIf && !node->isFuncDef && !(node->isVarDef && node->nodeLevel == 3)) {
            decisions.push_back(PathDecision{node.get(), PathDecisionKind::Code});
            pushed = true;
        }
        EpatRunner runner(vartemp);
        auto eval = runner.solve(decisions);
        if (eval.status == result::feasible && currentMem > bestMem) {
            bestMem = currentMem;
            bestPath = runner.render(decisions);
            processPathResult(eval, bestPath, pathCoverage, pathCount, depth);
        }
        ++pathCount;
        if (pushed) decisions.pop_back();
    };

    // 终结节点
    if (node->isReturn || !node->getNextNode()) {
        leafEval(true);
        return;
    }

    // If分支
    if (node->isIf) {
        auto temp_pathcoverage = pathCoverage;
        temp_loopCount[depth] = loopCount;

        decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
        GreedyDFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
        decisions.pop_back();

        for (int i = node->depth + 1; i < maxdepth; i++)
            pathCoverage[i] = false;
        pathCoverage = temp_pathcoverage;
        loopCount = temp_loopCount[depth];
        decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
        GreedyDFS(node->getNextFalseNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
        decisions.pop_back();
        return;
    }

    // Loop循环
    else if (node->isLoop) {
        if (node->isFor) {
            pathCoverage[node->depth + 1] = true;
            if (loopCount[node->depth] >= maxloop) {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
                loopCount[node->depth] = 0;
                GreedyDFS(node->getNextFalseNode()->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
                decisions.pop_back();
            } else {
                if (loopCount[node->depth] == 0 && node->initstmt_str != ";") {
                    decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopInit});
                }
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
                if (!node->expr_str.empty()) decisions.push_back(PathDecision{node.get(), PathDecisionKind::LoopUpdate});
                auto epatDecisions = decisions;
                loopCount[node->depth]++;
                GreedyDFS(node->getNextNode()->getNextNode(), pathCoverage, epatDecisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
                if (!node->expr_str.empty()) decisions.pop_back();
                decisions.pop_back();
                if (loopCount[node->depth] == 1 && node->initstmt_str != ";") decisions.pop_back();
            }
            return;
        } else if (node->isWhile) {
            if (loopCount[node->depth] >= maxloop) {
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::FalseBranch});
                loopCount[node->depth] = 0;
                GreedyDFS(node->getNextFalseNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
                decisions.pop_back();
            } else {
                loopCount[node->depth]++;
                decisions.push_back(PathDecision{node.get(), PathDecisionKind::TrueBranch});
                GreedyDFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
                decisions.pop_back();
            }
            return;
        }
    }

    // 变量定义/函数定义节点：只递归，不加内容到path
    else if (node->isFuncDef || (node->isVarDef && node->nodeLevel == 3)) {
        GreedyDFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
        return;
    }

    // 其它普通节点：把内容加入path
    else {
        decisions.push_back(PathDecision{node.get(), PathDecisionKind::Code});
        GreedyDFS(node->getNextNode(), pathCoverage, decisions, depth + 1, pathCount, maxloop, maxpaths, currentMem, bestPath, bestMem);
        decisions.pop_back();
        return;
    }
}

// 估算指定分支或循环下最大mems（仅贪心用，不检查可行性！）
int SyntaxNamePrinter::EvaluateBranchMem(std::shared_ptr<CFGNode> node, int maxloop, int nodelevel) {
    if (!node) return 0;
    if (node->isReturn || node->nodeLevel < nodelevel) return 0;
    int mem = node->getMem(vartemp);
    if (node->isLoop) {
        std::shared_ptr<CFGNode> loopBody = node->getNextNode();
        if (loopBody) {
            int loopBodyMem = EvaluateBranchMem(loopBody, maxloop, loopBody->nodeLevel);
            mem += loopBodyMem * maxloop;
        }
        std::shared_ptr<CFGNode> afterLoop = node->getNextFalseNode();
        if (afterLoop) {
            mem += EvaluateBranchMem(afterLoop, maxloop, afterLoop->nodeLevel);
        }
    } else if (node->isIf) {
        int trueMem = EvaluateBranchMem(node->getNextNode(), maxloop, node->getNextNode()->nodeLevel);
        int falseMem = EvaluateBranchMem(node->getNextFalseNode(), maxloop, node->getNextFalseNode()->nodeLevel);
        mem += std::max(trueMem, falseMem);
    } else {
        std::shared_ptr<CFGNode> nextNode = node->getNextNode();
        if (nextNode) {
            mem += EvaluateBranchMem(nextNode, maxloop, nodelevel);
        }
    }
    return mem;
}


//包含剪枝的宽度优先搜索

void SyntaxNamePrinter::printCFG_BFS() {
    std::cout << "[INFO] BFS traversal is temporarily disabled for node-based epat integration." << std::endl;
}

void SyntaxNamePrinter::BFS(std::shared_ptr<CFGNode> /*startNode*/,
                            std::vector<bool>& /*pathCoverage*/,
                            std::vector<PathDecision> /*decisions*/,
                            int& /*pathCount*/) {
    // Intentionally left blank.
}

//输出结果用的函数

void SyntaxNamePrinter::processPathResult(const EpatResult& eval,
                                          const std::string& path,
                                          std::vector<bool>& pathCoverage,
                                          int pathCount,
                                          int depth) {

    std::string pathFileName = "path" + std::to_string(pathCount) + ".txt";
    std::string resultFileName = "result" + std::to_string(pathCount) + ".txt";
    std::string smtFileName = "smt" + std::to_string(pathCount) + ".txt";
    std::string matrixFileName = "matrix.txt";

    std::ofstream pathFile(pathFileName);
    std::ofstream resultFile(resultFileName);
    std::ofstream smtFile(smtFileName);
    std::ofstream matrixFile(matrixFileName, std::ios::app);

    // 写入路径
    pathFile << path;
    cout<<"Path:"<<path<<endl;

    const bool feasible = eval.status == result::feasible;
    resultFile << (feasible ? "feasible" : (eval.status == result::infeasible ? "infeasible" : "unknown")) << "\n";

    if (!feasible) {
        std::fill(pathCoverage.begin(), pathCoverage.end(), false);  // 将路径覆盖矩阵元素全部置为0
    }
    resultFile << (feasible ? "feasible" : "infeasible") << "\n";

    // 写入 SMT 表达式和内存使用情况
    const std::string& smt2 = eval.smt;
    const int mem = eval.mem;

    if (feasible)
    {
        cout<<"feasible!!!"<<endl;
        const std::string& model= eval.model;
        std::optional<std::uint64_t> volceCount;

        smtFile << smt2 << "\n";
        resultFile << "[testcase]:" << "\n" << model << "\n"
                   << "[mem]:" << mem << "\n";

        cout<<"[mem]:"<<mem<<endl;
        cout<<"[averagemem]:"<<mem/depth<<endl;
        cout<<"[testcase]:"<<endl<<model<<endl;

        // 写入覆盖矩阵
        for (bool covered : pathCoverage) {
            matrixFile << (covered ? "1" : "0") << " ";
        }
        matrixFile << "\n";

        // 关闭文件
        pathFile.close();
        resultFile.close();
        smtFile.close();
        matrixFile.close();

        // 将路径覆盖信息添加到总覆盖矩阵中
        allPathsCoverage.push_back(pathCoverage);        

    }
    else
    {
        cout<<"infeasible!!!"<<endl;

        smtFile << smt2 << "\n";
        resultFile <<"\n"<<"[mem]:" << mem << "\n";
        cout<<"[mem]:"<<mem<<endl;
        cout<<"[averagemem]:"<<mem/depth<<endl;

        // 写入覆盖矩阵
        for (bool covered : pathCoverage) {
            matrixFile <<"0"<< " ";
        }
        matrixFile << "\n";

    }


}

void SyntaxNamePrinter::processPathResult2(const EpatResult& eval,
                                          const std::string& path,
                                          std::vector<bool>& pathCoverage,
                                          int pathCount,
                                          int depth,
                                          bool enableVolce) {

    std::string pathFileName = "path" + std::to_string(pathCount) + ".txt";
    std::string resultFileName = "result" + std::to_string(pathCount) + ".txt";
    std::string smtFileName = "smt" + std::to_string(pathCount) + ".txt";
    std::string matrixFileName = "matrix2.txt";

    std::ofstream pathFile(pathFileName);
    std::ofstream resultFile(resultFileName);
    std::ofstream smtFile(smtFileName);
    std::ofstream matrixFile(matrixFileName, std::ios::app);

    // 写入路径
    pathFile << path;
    cout<<"Path:"<<path<<endl;

    const bool feasible = eval.status == result::feasible;
    resultFile << (feasible ? "feasible" : (eval.status == result::infeasible ? "infeasible" : "unknown")) << "\n";

    if (!feasible)
    {
         std::fill(pathCoverage.begin(), pathCoverage.end(), false);  // 将路径覆盖矩阵元素全部置为0
    }
    resultFile << (feasible ? "feasible" : "infeasible") << "\n";

    // 写入 SMT 表达式和内存使用情况
    const std::string& smt2 = eval.smt;
    const int mem = eval.mem;

    if (feasible)
    {
        cout<<"feasible!!!"<<endl;
        const std::string& model= eval.model;
        std::optional<std::uint64_t> volceCount;

        smtFile << smt2 << "\n";
        resultFile << "[testcase]:" << "\n" << model << "\n"
                   << "[mem]:" << mem << "\n";

        cout<<"[mem]:"<<mem<<endl;
        cout<<"[averagemem]:"<<mem/depth<<endl;
        cout<<"[testcase]:"<<endl<<model<<endl;
        if (enableVolce) {
            const auto volceResult = runVolce(smt2, kVolceLowerBound, kVolceUpperBound);
            if (volceResult) {
                volceCount = parseVolceCount(volceResult);
                resultFile << "[volce]:" << volceResult->output << "\n";
                cout << "[VolCE]" << endl;
                cout << volceResult->output << endl;
            } else {
                resultFile << "[volce]: N/A\n";
                cout << "[VolCE] N/A" << endl;
            }
        }
        recordFeasiblePath(pathCount, mem, path, volceCount);

        // 写入覆盖矩阵
        for (bool covered : pathCoverage) {
            matrixFile << (covered ? "1" : "0") << " ";
        }
        matrixFile << "\n";

        // 关闭文件
        pathFile.close();
        resultFile.close();
        smtFile.close();
        matrixFile.close();

        // 将路径覆盖信息添加到总覆盖矩阵中
        allPathsCoverage.push_back(pathCoverage);        

    }

    else

    {
        cout<<"infeasible!!!"<<endl;

        smtFile << smt2 << "\n";
        resultFile <<"\n"<<"[mem]:" << mem << "\n";
        cout<<"[mem]:"<<mem<<endl;
        cout<<"[averagemem]:"<<mem/depth<<endl;

        // 写入覆盖矩阵
        for (bool covered : pathCoverage) {
            matrixFile <<"0"<< " ";
        }
        matrixFile << "\n";

    }


}

std::vector<std::vector<int>> SyntaxNamePrinter::ReadCoverageMatrix(const std::string& filename) {

    std::vector<std::vector<int>> coverageMatrix;

    std::ifstream file(filename);

    std::string line;

    while (std::getline(file, line)) {

        std::istringstream iss(line);

        std::vector<int> row;

        int value;

        while (iss >> value) {

            row.push_back(value);

        }

        coverageMatrix.push_back(row);

    }
    cout<<"[matrix_before]:"<<endl;
    for (const auto& row : coverageMatrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    return coverageMatrix;

}



//这个部分改成了贪心算法，可以得出结果

void SyntaxNamePrinter::SolveLinearProgram(const std::vector<std::vector<int>>& coverageMatrix) {
    int numStatements = coverageMatrix[0].size();
    int numPaths = coverageMatrix.size();
    std::vector<bool> isStatementCovered(numStatements, false);

    std::ofstream outputFile("final.txt");  // 创建文件输出流
    for (int i = 0; i < numPaths; ++i) {
        for (int j = 0; j < numStatements; ++j) {
            if (coverageMatrix[i][j] == 1) {
                isStatementCovered[j] = true;
            }
        }
    }

    std::vector<int> validStatements;
    for (int i = 0; i < numStatements; ++i) {
        if (isStatementCovered[i]) {
            validStatements.push_back(i);
        }
    }

    std::vector<bool> pathSelected(numPaths, false);
    std::set<int> uncoveredStatements(validStatements.begin(), validStatements.end());
    int pathCount = 0;

    while (!uncoveredStatements.empty()) {
        int maxCover = 0;
        int bestPath = -1;

        for (int i = 0; i < numPaths; ++i) {
            if (!pathSelected[i]) {
                int cover = 0;
                for (int j : uncoveredStatements) {
                    if (coverageMatrix[i][j] == 1) {
                        cover++;
                    }
                }
                if (cover > maxCover) {
                    maxCover = cover;
                    bestPath = i;
                }
            }
        }

        if (bestPath != -1) {
            pathSelected[bestPath] = true;
            pathCount++;
            for (int j = 0; j < numStatements; ++j) {
                if (coverageMatrix[bestPath][j] == 1) {
                    uncoveredStatements.erase(j);
                }
            }

            //std::cout << "Path " << bestPath + 1 << " selected." << std::endl;
            outputFile << "Path " << bestPath + 1 << " selected." << std::endl;

            // Read and display the corresponding result file content
            std::string resultFileName = "result" + std::to_string(pathCount-1) + ".txt";
            std::ifstream resultFile(resultFileName);
            if (resultFile.is_open()) {
                std::stringstream buffer;
                buffer << resultFile.rdbuf();
                //std::cout << "Contents of " << resultFileName << ":" << std::endl;
                outputFile<< "Contents of " << resultFileName << ":" << std::endl;
                //std::cout << buffer.str() << std::endl;
                outputFile<< buffer.str() << std::endl;
                resultFile.close();
            } else {
                //std::cout << "Failed to open " << resultFileName << std::endl;
                outputFile << "Failed to open " << resultFileName << std::endl;
            }
        }
    }
    outputFile.close();  // 关闭文件流
}
