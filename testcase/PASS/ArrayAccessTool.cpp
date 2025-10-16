#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Lex/Lexer.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;

class InstrumentationVisitor : public RecursiveASTVisitor<InstrumentationVisitor> {
public:
    InstrumentationVisitor(std::string &buffer, const SourceManager &SM, const LangOptions &Options)
        : OutputBuffer(buffer), SrcMgr(SM), LangOpts(Options) {}

    bool VisitStmt(Stmt *s) {
        if (isa<Expr>(s)) {
            Expr *e = cast<Expr>(s);
            SourceRange range = e->getSourceRange();
            if (range.getBegin().isValid() && range.getEnd().isValid()) {
                std::string exprText = Lexer::getSourceText(CharSourceRange::getTokenRange(range), SrcMgr, LangOpts);
                std::string printStmt = "printf(\"Executing statement: " + exprText + "\\n\");\n";
                unsigned startOffset = SrcMgr.getFileOffset(range.getBegin());
                if (startOffset <= OutputBuffer.size()) {
                    OutputBuffer.insert(startOffset, printStmt);
                }
            }
        }
        return true;
    }

private:
    std::string &OutputBuffer;
    const SourceManager &SrcMgr;
    const LangOptions &LangOpts;
};

class MyASTConsumer : public ASTConsumer {
public:
    MyASTConsumer(const SourceManager &SM, const LangOptions &Options)
        : SrcMgr(SM), LangOpts(Options) {
        const FileEntry *File = SrcMgr.getFileEntryForID(SrcMgr.getMainFileID());
        llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> Buffer = llvm::MemoryBuffer::getFile(File->getName());
        if (Buffer) {
            OutputBuffer = Buffer.get()->getBuffer().str();
        }
        llvm::errs() << "Initialized MyASTConsumer\n";
    }

    void HandleTranslationUnit(ASTContext &Context) override {
        llvm::errs() << "Handling translation unit\n";
        Visitor = std::make_unique<InstrumentationVisitor>(OutputBuffer, SrcMgr, LangOpts);
        Visitor->TraverseDecl(Context.getTranslationUnitDecl());
        llvm::errs() << "Translation unit processed\n";

        std::error_code EC;
        llvm::raw_fd_ostream outFile("instrumented_output.cpp", EC, llvm::sys::fs::F_Text);
        if (!EC) {
            outFile << OutputBuffer;
            outFile.close();
            llvm::errs() << "Output written to instrumented_output.cpp\n";
        } else {
            llvm::errs() << "Failed to write output file: " << EC.message() << "\n";
        }
    }

private:
    std::unique_ptr<InstrumentationVisitor> Visitor;
    std::string OutputBuffer;
    const SourceManager &SrcMgr;
    const LangOptions &LangOpts;
};

class MyFrontendAction : public ASTFrontendAction {
public:
    std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) override {
        llvm::errs() << "Creating AST Consumer\n";
        return std::make_unique<MyASTConsumer>(CI.getSourceManager(), CI.getLangOpts());
    }
};

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

int main(int argc, const char **argv) {
    CommonOptionsParser op(argc, argv, MyToolCategory);
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());
    llvm::errs() << "Running tool\n";
    int result = Tool.run(newFrontendActionFactory<MyFrontendAction>().get());
    llvm::errs() << "Tool run completed with result: " << result << "\n";
    return result;
}
