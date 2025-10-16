// instrumenter.cpp 
//
// 编译（以 clang++ 为例）：
//   clang++ -std=c++17 instrumenter.cpp $(llvm-config-20 --cxxflags --ldflags --system-libs)  -I/usr/lib/llvm-20/include /usr/lib/x86_64-linux-gnu/libclang-cpp.so.20.0  -lLLVM-20 -o instrumenter -Wl,-rpath=/usr/lib/llvm-20/lib
//
// 使用方法：
//   ./instrumenter example.c
// 插桩后会生成 “example.c_pass.c”

#include "clang/AST/AST.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Lex/Lexer.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <cstdio>
#include <cstdlib>

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;

// 命令行选项
static llvm::cl::OptionCategory MyToolCategory("instrumenter options");

// 全局变量声明辅助
struct GlobalVarInfo {
    std::string printedDecl;
};
static std::vector<GlobalVarInfo> CollectedGlobalVars;

std::string getFullArrayDecl(const QualType &QT, const std::string &varName) {
    const Type *T = QT.getTypePtr();
    std::vector<std::string> dims;
    while (const ConstantArrayType *CAT = dyn_cast<ConstantArrayType>(T)) {
         llvm::APInt sizeAP = CAT->getSize();
         llvm::SmallVector<char, 16> buf;
         sizeAP.toString(buf, 10, false, false);
         dims.push_back(std::string(buf.begin(), buf.end()));
         T = CAT->getElementType().getTypePtr();
    }
    std::string baseType = QualType(T, 0).getAsString();
    std::string result = baseType + " " + varName;
    for (const auto &dim : dims) {
         result += "[" + dim + "]";
    }
    return result;
}

int countArraySubscripts(const Expr *E) {
    class ArrayCounter : public RecursiveASTVisitor<ArrayCounter> {
      public:
        int count = 0;
        bool inArraySubscript = false;
        bool TraverseArraySubscriptExpr(ArraySubscriptExpr *ase) {
            bool wasIn = inArraySubscript;
            if (!wasIn) {
                count++;
            }
            inArraySubscript = true;
            RecursiveASTVisitor<ArrayCounter>::TraverseArraySubscriptExpr(ase);
            inArraySubscript = wasIn;
            return true;
        }
    };
    ArrayCounter counter;
    counter.TraverseStmt(const_cast<Expr*>(E));
    return counter.count;
}

// 全局变量识别
class GlobalVarInstrumentCallback : public MatchFinder::MatchCallback {
public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const VarDecl *vd = Result.Nodes.getNodeAs<VarDecl>("globalVar")) {
      if (!vd->hasGlobalStorage()) return;
      std::string nameStr = vd->getNameAsString();
      if (nameStr == "path_len" || nameStr == "mems" || nameStr == "cond_count"
          || nameStr == "start" || nameStr == "end" || nameStr == "time_taken")
          return;
      std::string printedDecl;
      if (vd->getType()->isConstantArrayType())
          printedDecl = getFullArrayDecl(vd->getType(), nameStr);
      else
          printedDecl = vd->getType().getAsString() + " " + nameStr;
      CollectedGlobalVars.push_back({ printedDecl });
    }
  }
};

// 函数插桩
class FunctionInstrumentCallback : public MatchFinder::MatchCallback {
public:
  FunctionInstrumentCallback(Rewriter &R) : TheRewriter(R) {}

  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const FunctionDecl *f = Result.Nodes.getNodeAs<FunctionDecl>("funcDecl")) {
      if (f->getNameAsString() == "main") return;
      if (f->hasBody()) {
        if (const CompoundStmt *CS = dyn_cast<CompoundStmt>(f->getBody())) {
          SourceLocation insertLoc = CS->getLBracLoc().getLocWithOffset(1);
          SourceManager &SM = *Result.SourceManager;
          LangOptions LangOpts = Result.Context->getLangOpts();

          std::string defCode = "printf(\"Path: \\n\");\n";
          for (unsigned i = 0; i < f->getNumParams(); ++i) {
              const ParmVarDecl *p = f->getParamDecl(i);
              std::string paramText = Lexer::getSourceText(
                  CharSourceRange::getTokenRange(p->getSourceRange()), SM, LangOpts).str();
              defCode += "printf(\"" + paramText + ";\\n\");\n";
          }
          for (const Stmt *s : CS->body()) {
            if (const DeclStmt *ds = dyn_cast<DeclStmt>(s)) {
                for (const Decl *d : ds->decls()) {
                    if (const VarDecl *vd = dyn_cast<VarDecl>(d)) {
                        std::string varName = vd->getNameAsString();
                        if (varName == "path_len" || varName == "mems" ||
                            varName == "cond_count" || varName == "start" || varName == "end")
                            continue;
                        if (vd->getType()->isConstantArrayType()) {
                            std::string declStr = getFullArrayDecl(vd->getType(), varName);
                            defCode += "printf(\"" + declStr + ";\\n\");\n";
                        } else {
                            defCode += "printf(\"" + vd->getType().getAsString() + " " + varName + ";\\n\");\n";
                        }
                    }
                }
            }
          }
          for (auto &gv : CollectedGlobalVars) {
              defCode += "printf(\"" + gv.printedDecl + ";\\n\");\n";
          }

          // 加入 cond_count 的声明
          std::string initCode = "\nint path_len = 0;\nint mems = 0;\nint cond_count = 0;\n"
                                 "clock_t start, end;\nstart = clock();\n";
          std::string finalCode = initCode + defCode;
          TheRewriter.InsertText(insertLoc, finalCode, true, true);
        }
      }
    }
  }
private:
  Rewriter &TheRewriter;
};

// if 语句插桩
class IfInstrumentCallback : public MatchFinder::MatchCallback {
public:
  IfInstrumentCallback(Rewriter &R) : TheRewriter(R) {}

  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const IfStmt *ifstmt = Result.Nodes.getNodeAs<IfStmt>("ifStmt")) {
      const Expr *cond = ifstmt->getCond();
      if (!cond) return;
      SourceManager &SM = *Result.SourceManager;
      LangOptions LangOpts;
      std::string condText = Lexer::getSourceText(
          CharSourceRange::getTokenRange(cond->getSourceRange()), SM, LangOpts).str();

      int memCount = countArraySubscripts(cond);

      // 增加cond_count插桩
      std::string code = "\ncond_count = cond_count + 1;\nprintf(\"@(" + condText + ")\\n\");\npath_len = path_len + 1;\n";
      if (memCount > 0)
         code += "mems = mems + " + std::to_string(memCount) + ";\n";

      if (const Stmt *thenStmt = ifstmt->getThen()) {
        SourceLocation thenLoc = thenStmt->getBeginLoc().getLocWithOffset(1);
        TheRewriter.InsertText(thenLoc, code, true, true);
      }
      if (const Stmt *elseStmt = ifstmt->getElse()) {
        SourceLocation elseLoc = elseStmt->getBeginLoc().getLocWithOffset(1);
        std::string elseCode = "\ncond_count = cond_count + 1;\nprintf(\"@(!(" + condText + "))\\n\");\npath_len = path_len + 1;\n";
        if (memCount > 0)
           elseCode += "mems = mems + " + std::to_string(memCount) + ";\n";
        TheRewriter.InsertText(elseLoc, elseCode, true, true);
      }
      if (!isa<CompoundStmt>(ifstmt->getThen())) {
        SourceLocation start = ifstmt->getThen()->getBeginLoc();
        SourceLocation end = ifstmt->getThen()->getEndLoc();
        TheRewriter.InsertText(start, "{\n");
        TheRewriter.InsertTextAfterToken(end, "\n}");
      }
      if (ifstmt->getElse() && !isa<CompoundStmt>(ifstmt->getElse())) {
        SourceLocation start = ifstmt->getElse()->getBeginLoc();
        SourceLocation end = ifstmt->getElse()->getEndLoc();
        TheRewriter.InsertText(start, "{\n");
        TheRewriter.InsertTextAfterToken(end, "\n}");
      }
    }
  }
private:
  Rewriter &TheRewriter;
};

// for 语句插桩
class ForInstrumentCallback : public MatchFinder::MatchCallback {
  public:
    ForInstrumentCallback(Rewriter &R) : TheRewriter(R), uniqueId(0) {}

    virtual void run(const MatchFinder::MatchResult &Result) {
      if (const ForStmt *forstmt = Result.Nodes.getNodeAs<ForStmt>("forStmt")) {
        SourceManager &SM = *Result.SourceManager;
        LangOptions LangOpts;

        std::string initText;
        if (const Stmt *init = forstmt->getInit()) {
            initText = Lexer::getSourceText(
                CharSourceRange::getTokenRange(init->getSourceRange()), SM, LangOpts).str();
        }

        std::string condText;
        if (const Expr *cond = forstmt->getCond()) {
            condText = Lexer::getSourceText(
                CharSourceRange::getTokenRange(cond->getSourceRange()), SM, LangOpts).str();
        } else {
            condText = "true";
        }

        std::string incText;
        if (const Expr *inc = forstmt->getInc()) {
            incText = Lexer::getSourceText(
                CharSourceRange::getTokenRange(inc->getSourceRange()), SM, LangOpts).str();
        }

        std::string flagVar = "__first_iter_flag_" + std::to_string(uniqueId++);

        SourceLocation forStart = forstmt->getForLoc();
        std::string flagDecl = "{\n  int " + flagVar + " = 1;\n";
        TheRewriter.InsertText(forStart, flagDecl, true, true);

        SourceLocation forEnd = forstmt->getEndLoc().getLocWithOffset(1);
        TheRewriter.InsertTextAfterToken(forEnd, "\n}\n");

        if (const Stmt *body = forstmt->getBody()) {
            SourceLocation bodyStart = body->getBeginLoc().getLocWithOffset(1);
            std::string initInstr;
            if (!initText.empty()) {
                initInstr = "\nif(" + flagVar + ") { \nprintf(\"" + initText + ";\\n\"); \n" + flagVar + " = 0; \n}\n";
            }
            int memCount = 0;
            if (const Expr *cond = forstmt->getCond())
                memCount = countArraySubscripts(cond);
            // cond_count插桩
            std::string condInstr = "cond_count = cond_count + 1;\nprintf(\"@(" + condText + ")\\n\");\npath_len = path_len + 1;\n";
            if (memCount > 0)
                condInstr += "mems = mems + " + std::to_string(memCount) + ";\n";
            TheRewriter.InsertText(bodyStart, initInstr + condInstr, true, true);

            if (!incText.empty()) {
                if (const CompoundStmt *CS = dyn_cast<CompoundStmt>(body)) {
                    SourceLocation bodyEnd = CS->getRBracLoc();
                    std::string incInstr = "printf(\"" + incText + ";\\n\");\n";
                    TheRewriter.InsertTextBefore(bodyEnd, incInstr);
                } else {
                    SourceLocation bodyEnd = body->getEndLoc();
                    std::string incInstr = "{\nprintf(\"inc: " + incText + "\\n\");\n}\n";
                    TheRewriter.InsertTextAfterToken(bodyEnd, incInstr);
                }
            }
        }
      }
    }
  private:
    Rewriter &TheRewriter;
    unsigned uniqueId;
};

// while 语句插桩
class WhileInstrumentCallback : public MatchFinder::MatchCallback {
public:
  WhileInstrumentCallback(Rewriter &R) : TheRewriter(R) {}

  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const WhileStmt *wstmt = Result.Nodes.getNodeAs<WhileStmt>("whileStmt")) {
      const Expr *cond = wstmt->getCond();
      if (!cond) return;
      SourceManager &SM = *Result.SourceManager;
      LangOptions LangOpts;
      std::string condText = Lexer::getSourceText(
          CharSourceRange::getTokenRange(cond->getSourceRange()), SM, LangOpts).str();

      int memCount = countArraySubscripts(cond);

      if (const Stmt *body = wstmt->getBody()) {
        SourceLocation bodyLoc = body->getBeginLoc().getLocWithOffset(1);
        // cond_count插桩
        std::string code = "\ncond_count = cond_count + 1;\nprintf(\"@(" + condText + ")\\n\");\npath_len = path_len + 1;\n";
        if (memCount > 0)
          code += "mems = mems + " + std::to_string(memCount) + ";\n";
        TheRewriter.InsertText(bodyLoc, code, true, true);

        if (!isa<CompoundStmt>(body)) {
          SourceLocation bodyEndLoc = body->getEndLoc();
          TheRewriter.InsertTextBefore(bodyLoc, "{\n");
          TheRewriter.InsertTextAfterToken(bodyEndLoc, "\n}");
        }
      }
    }
  }
private:
  Rewriter &TheRewriter;
};

// return 插桩
class ReturnInstrumentCallback : public MatchFinder::MatchCallback {
  public:
    ReturnInstrumentCallback(Rewriter &R) : TheRewriter(R) {}

    virtual void run(const MatchFinder::MatchResult &Result) {
      if (const ReturnStmt *ret = Result.Nodes.getNodeAs<ReturnStmt>("retStmt")) {
        SourceManager &SM = *Result.SourceManager;
        LangOptions LangOpts = Result.Context->getLangOpts();
        // print cond_count
        std::string retCode =
            "printf(\"\\nEND\\nTotal path length: %d\\n\", path_len);\n"
            "printf(\"Total memory accesses: %d\\n\", mems);\n"
            "printf(\"Total conditional statements: %d\\n\", cond_count);\n"
            "end = clock();\n"
            "double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;\n"
            "printf(\"Execution time: %f seconds\\n\", time_taken);\n";
        SourceLocation retLoc = ret->getBeginLoc();
        TheRewriter.InsertText(retLoc, retCode, true, true);
      }
    }
  private:
    Rewriter &TheRewriter;
};

// 赋值语句插桩
class AssignmentInstrumentCallback : public MatchFinder::MatchCallback {
  public:
    AssignmentInstrumentCallback(Rewriter &R) : TheRewriter(R) {}

    virtual void run(const MatchFinder::MatchResult &Result) {
      if (const BinaryOperator *outerBO = Result.Nodes.getNodeAs<BinaryOperator>("assignStmt")) {
        if (!outerBO->isAssignmentOp())
          return;

        SourceManager &SM = *Result.SourceManager;
        LangOptions LangOpts = Result.Context->getLangOpts();

        bool isChain = false;
        {
          Expr *rhs = outerBO->getRHS()->IgnoreImpCasts();
          if (const BinaryOperator *innerBO = dyn_cast<BinaryOperator>(rhs)) {
            if (innerBO->isAssignmentOp())
              isChain = true;
          }
        }
        if (isChain) {
          SourceLocation startLoc = outerBO->getBeginLoc();
          SourceLocation endLoc = Lexer::getLocForEndOfToken(outerBO->getEndLoc(), 0, SM, LangOpts);
          std::string fullStmtText = Lexer::getSourceText(
              CharSourceRange::getTokenRange(startLoc, endLoc), SM, LangOpts).str();

          class ArrayCounter : public RecursiveASTVisitor<ArrayCounter> {
          public:
            int count = 0;
            bool VisitArraySubscriptExpr(ArraySubscriptExpr *ase) {
              count++;
              return true;
            }
          };
          ArrayCounter counter;
          counter.TraverseStmt(const_cast<BinaryOperator*>(outerBO));
          int memCount = counter.count;

          std::string newCode;
          newCode += "printf(\"" + fullStmtText + ";\\n\");\n";
          newCode += fullStmtText + "\n";
          if (memCount > 0)
            newCode += "mems = mems + " + std::to_string(memCount) + ";\n";

          SourceRange totalRange(startLoc, endLoc);
          TheRewriter.ReplaceText(totalRange, newCode);
          return;
        }

        std::string stmtText = Lexer::getSourceText(
            CharSourceRange::getTokenRange(outerBO->getSourceRange()), SM, LangOpts).str();

        class ArrayCounter : public RecursiveASTVisitor<ArrayCounter> {
        public:
          int count = 0;
          bool VisitArraySubscriptExpr(ArraySubscriptExpr *ase) {
            count++;
            return true;
          }
        };
        ArrayCounter counter;
        counter.TraverseStmt(const_cast<BinaryOperator*>(outerBO));
        int memCount = counter.count;

        std::string beforeCode = "printf(\"" + stmtText + ";\\n\");\n";
        std::string afterCode;
        if (memCount > 0)
           afterCode = "mems = mems + " + std::to_string(memCount) + ";\n";

        SourceLocation exprEnd = outerBO->getEndLoc();
        SourceLocation afterExpr = Lexer::getLocForEndOfToken(exprEnd, 0, SM, LangOpts);
        Token tok;
        bool foundSemi = false;
        if (!Lexer::getRawToken(afterExpr, tok, SM, LangOpts, true)) {
            if (tok.is(tok::semi))
                foundSemi = true;
        }
        SourceLocation endToken;
        if (foundSemi)
           endToken = Lexer::getLocForEndOfToken(tok.getLocation(), 0, SM, LangOpts);
        else
           endToken = afterExpr;

        TheRewriter.InsertText(outerBO->getBeginLoc(), beforeCode, true, true);
        TheRewriter.InsertText(endToken, "\n" + afterCode, true, true);
      }
    }
  private:
    Rewriter &TheRewriter;
};

class InstrumentASTConsumer : public ASTConsumer {
    public:
      InstrumentASTConsumer(Rewriter &R)
        : FuncHandler(R), IfHandler(R), ForHandler(R), WhileHandler(R), 
          AssignHandler(R), ReturnHandler(R), GlobalVarHandler() {
        Matcher.addMatcher(functionDecl(isDefinition(), unless(hasName("main"))).bind("funcDecl"), &FuncHandler);
        Matcher.addMatcher(ifStmt(unless(hasAncestor(functionDecl(hasName("main"))))).bind("ifStmt"), &IfHandler);
        Matcher.addMatcher(forStmt(unless(hasAncestor(functionDecl(hasName("main"))))).bind("forStmt"), &ForHandler);
        Matcher.addMatcher(whileStmt(unless(hasAncestor(functionDecl(hasName("main"))))).bind("whileStmt"), &WhileHandler);
        Matcher.addMatcher(
          binaryOperator(hasOperatorName("="),
              unless(anyOf(
                  hasAncestor(functionDecl(hasName("main"))),
                  hasParent(forStmt()),
                  hasAncestor(binaryOperator(hasOperatorName("=")))
              ))
          ).bind("assignStmt"),
          &AssignHandler);
        Matcher.addMatcher(
          returnStmt(unless(hasAncestor(functionDecl(hasName("main"))))).bind("retStmt"),
          &ReturnHandler);
        Matcher.addMatcher(varDecl(hasGlobalStorage(), unless(isExpansionInSystemHeader())).bind("globalVar"), &GlobalVarHandler);
      }
      void HandleTranslationUnit(ASTContext &Context) override {
        Matcher.matchAST(Context);
      }
    private:
      FunctionInstrumentCallback FuncHandler;
      IfInstrumentCallback IfHandler;
      ForInstrumentCallback ForHandler;
      WhileInstrumentCallback WhileHandler;
      AssignmentInstrumentCallback AssignHandler;
      ReturnInstrumentCallback ReturnHandler;
      GlobalVarInstrumentCallback GlobalVarHandler;
      MatchFinder Matcher;
};

#include <cstdio>

class InstrumentFrontendAction : public ASTFrontendAction {
public:
  InstrumentFrontendAction() {}
  void EndSourceFileAction() override {
    SourceManager &SM = TheRewriter.getSourceMgr();
    FileID MainFileID = SM.getMainFileID();
    SourceLocation Loc = SM.getLocForStartOfFile(MainFileID);
    if (Loc.isValid()) {
      StringRef FileName = SM.getFilename(Loc);
      std::string OutName = FileName.str() + "_pass.c";
      std::remove(OutName.c_str());
      std::error_code EC;
      llvm::raw_fd_ostream outFile(OutName, EC, llvm::sys::fs::OF_None);
      TheRewriter.getEditBuffer(MainFileID).write(outFile);
      outFile.close();
      llvm::outs() << "Instrumented file generated: " << OutName << "\n";
    }
  }
  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) override {
    TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
    return std::make_unique<InstrumentASTConsumer>(TheRewriter);
  }
private:
  Rewriter TheRewriter;
};

int main(int argc, const char **argv) {
  auto OptionsParserOrError = CommonOptionsParser::create(argc, argv, MyToolCategory);
  if (!OptionsParserOrError) {
    llvm::errs() << "Error creating CommonOptionsParser\n";
    return 1;
  }
  CommonOptionsParser &OptionsParser = *OptionsParserOrError;
  ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
  return Tool.run(newFrontendActionFactory<InstrumentFrontendAction>().get());
}
