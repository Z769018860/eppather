
// Generated from c://Projects//epat++//epat-protocol//grammar//C.g4 by ANTLR 4.13.1


#include "CVisitor.h"

#include "CParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CParserStaticData final {
  CParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CParserStaticData(const CParserStaticData&) = delete;
  CParserStaticData(CParserStaticData&&) = delete;
  CParserStaticData& operator=(const CParserStaticData&) = delete;
  CParserStaticData& operator=(CParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag cParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CParserStaticData *cParserStaticData = nullptr;

void cParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (cParserStaticData != nullptr) {
    return;
  }
#else
  assert(cParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CParserStaticData>(
    std::vector<std::string>{
      "compilationUnit", "translationUnit", "expression", "constantExpression", 
      "primaryExpression", "constant", "stringLiteral", "argumentExpressionList", 
      "commaExpression", "declaration", "declarationSpecifiers", "initDeclaratorList", 
      "initDeclarator", "storageClassSpecifier", "typeSpecifier", "structOrUnionSpecifier", 
      "structOrUnion", "structDeclarationList", "structDeclaration", "specifierQualifierList", 
      "structDeclaratorList", "structDeclarator", "enumSpecifier", "enumeratorList", 
      "enumerator", "enumerationConstant", "atomicTypeSpecifier", "typeQualifier", 
      "functionSpecifier", "alignmentSpecifier", "declarator", "directDeclarator", 
      "pointer", "typeQualifierList", "parameterTypeList", "parameterList", 
      "parameterDeclaration", "identifierList", "typeName", "abstractDeclarator", 
      "directAbstractDeclarator", "typedefName", "initializer", "initializerList", 
      "designation", "designatorList", "designator", "staticAssertDeclaration", 
      "statement", "labeledStatement", "compoundStatement", "blockItemList", 
      "blockItem", "expressionStatement", "selectionStatement", "iterationStatement", 
      "forCondition", "jumpStatement", "externalDeclaration", "functionDefinition", 
      "declarationList"
    },
    std::vector<std::string>{
      "", "'\"'", "'auto'", "'break'", "'case'", "'char'", "'const'", "'continue'", 
      "'default'", "'do'", "'double'", "'else'", "'enum'", "'extern'", "'float'", 
      "'for'", "'goto'", "'if'", "'inline'", "'int'", "'long'", "'register'", 
      "'restrict'", "'return'", "'short'", "'signed'", "'sizeof'", "'static'", 
      "'struct'", "'switch'", "'typedef'", "'union'", "'unsigned'", "'void'", 
      "'volatile'", "'while'", "'_Alignas'", "'_Alignof'", "'_Atomic'", 
      "'_Bool'", "'_Complex'", "'_Generic'", "'_Imaginary'", "'_Noreturn'", 
      "'_Static_assert'", "'_Thread_local'", "'('", "')'", "'['", "']'", 
      "'{'", "'}'", "'<'", "'<='", "'>'", "'>='", "'<<'", "'>>'", "'+'", 
      "'++'", "'-'", "'--'", "'*'", "'/'", "'%'", "'&'", "'|'", "'&&'", 
      "'||'", "'^'", "'!'", "'~'", "'\\u003F'", "':'", "';'", "','", "'='", 
      "'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", "'>>='", "'&='", 
      "'^='", "'|='", "'=='", "'!='", "'->'", "'.'", "'...'"
    },
    std::vector<std::string>{
      "", "", "Auto", "Break", "Case", "Char", "Const", "Continue", "Default", 
      "Do", "Double", "Else", "Enum", "Extern", "Float", "For", "Goto", 
      "If", "Inline", "Int", "Long", "Register", "Restrict", "Return", "Short", 
      "Signed", "Sizeof", "Static", "Struct", "Switch", "Typedef", "Union", 
      "Unsigned", "Void", "Volatile", "While", "Alignas", "Alignof", "Atomic", 
      "Bool", "Complex", "Generic", "Imaginary", "Noreturn", "StaticAssert", 
      "ThreadLocal", "LeftParen", "RightParen", "LeftBracket", "RightBracket", 
      "LeftBrace", "RightBrace", "Less", "LessEqual", "Greater", "GreaterEqual", 
      "LeftShift", "RightShift", "Plus", "PlusPlus", "Minus", "MinusMinus", 
      "Star", "Div", "Mod", "And", "Or", "AndAnd", "OrOr", "Caret", "Not", 
      "Tilde", "Question", "Colon", "Semi", "Comma", "Assign", "StarAssign", 
      "DivAssign", "ModAssign", "PlusAssign", "MinusAssign", "LeftShiftAssign", 
      "RightShiftAssign", "AndAssign", "XorAssign", "OrAssign", "Equal", 
      "NotEqual", "Arrow", "Dot", "Ellipsis", "Identifier", "IntegerConstant", 
      "FloatingConstant", "DigitSequence", "CharacterConstant", "EncodingPrefix", 
      "SCharSequence", "MultiLineMacro", "Directive", "AsmBlock", "Whitespace", 
      "Newline", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,105,771,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,1,0,3,0,124,8,0,1,0,1,0,1,
  	1,1,1,1,1,4,1,131,8,1,11,1,12,1,132,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,150,8,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,158,
  	8,2,3,2,160,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,208,8,
  	2,1,2,1,2,1,2,1,2,1,2,3,2,215,8,2,5,2,217,8,2,10,2,12,2,220,9,2,1,3,1,
  	3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,231,8,4,1,5,1,5,1,6,3,6,236,8,6,1,6,
  	1,6,3,6,240,8,6,1,6,1,6,1,7,1,7,1,7,5,7,247,8,7,10,7,12,7,250,9,7,1,8,
  	1,8,1,8,1,8,1,8,1,8,5,8,258,8,8,10,8,12,8,261,9,8,1,9,1,9,3,9,265,8,9,
  	1,9,1,9,1,9,3,9,270,8,9,1,10,1,10,1,10,1,10,1,10,4,10,277,8,10,11,10,
  	12,10,278,1,11,1,11,1,11,5,11,284,8,11,10,11,12,11,287,9,11,1,12,1,12,
  	1,12,3,12,292,8,12,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,3,14,311,8,14,1,15,1,15,3,15,315,8,
  	15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,324,8,15,1,16,1,16,1,17,4,
  	17,329,8,17,11,17,12,17,330,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,
  	18,341,8,18,1,19,1,19,4,19,345,8,19,11,19,12,19,346,1,20,1,20,1,20,5,
  	20,352,8,20,10,20,12,20,355,9,20,1,21,1,21,3,21,359,8,21,1,21,1,21,3,
  	21,363,8,21,1,22,1,22,3,22,367,8,22,1,22,1,22,1,22,3,22,372,8,22,1,22,
  	1,22,1,22,1,22,3,22,378,8,22,1,23,1,23,1,23,5,23,383,8,23,10,23,12,23,
  	386,9,23,1,24,1,24,1,24,3,24,391,8,24,1,25,1,25,1,26,1,26,1,26,1,26,1,
  	26,1,27,1,27,1,28,1,28,1,29,1,29,1,29,1,29,3,29,408,8,29,1,29,1,29,1,
  	30,3,30,413,8,30,1,30,1,30,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,
  	31,3,31,426,8,31,1,31,1,31,1,31,3,31,431,8,31,1,31,3,31,434,8,31,1,31,
  	1,31,1,31,1,31,1,31,3,31,441,8,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,
  	1,31,1,31,1,31,1,31,1,31,1,31,3,31,456,8,31,1,31,1,31,1,31,1,31,1,31,
  	1,31,1,31,1,31,1,31,1,31,3,31,468,8,31,1,31,5,31,471,8,31,10,31,12,31,
  	474,9,31,1,32,1,32,3,32,478,8,32,1,32,3,32,481,8,32,1,33,4,33,484,8,33,
  	11,33,12,33,485,1,34,1,34,1,34,3,34,491,8,34,1,35,1,35,1,35,5,35,496,
  	8,35,10,35,12,35,499,9,35,1,36,1,36,1,36,3,36,504,8,36,3,36,506,8,36,
  	1,37,1,37,1,37,5,37,511,8,37,10,37,12,37,514,9,37,1,38,1,38,3,38,518,
  	8,38,1,39,1,39,3,39,522,8,39,1,39,3,39,525,8,39,1,40,1,40,1,40,1,40,1,
  	40,1,40,1,40,3,40,534,8,40,1,40,3,40,537,8,40,1,40,1,40,1,40,1,40,3,40,
  	543,8,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,
  	1,40,1,40,3,40,559,8,40,1,40,3,40,562,8,40,1,40,1,40,1,40,3,40,567,8,
  	40,1,40,3,40,570,8,40,1,40,1,40,1,40,1,40,1,40,3,40,577,8,40,1,40,1,40,
  	1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,
  	1,40,3,40,596,8,40,1,40,5,40,599,8,40,10,40,12,40,602,9,40,1,41,1,41,
  	1,42,1,42,1,42,1,42,3,42,610,8,42,1,42,1,42,3,42,614,8,42,1,43,3,43,617,
  	8,43,1,43,4,43,620,8,43,11,43,12,43,621,1,44,1,44,1,44,1,45,4,45,628,
  	8,45,11,45,12,45,629,1,46,1,46,1,46,1,46,1,46,1,46,3,46,638,8,46,1,47,
  	1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,48,1,48,1,48,1,48,1,48,1,48,3,48,
  	654,8,48,1,49,1,49,1,49,1,49,1,49,1,49,1,49,1,49,1,49,1,49,1,49,3,49,
  	667,8,49,1,50,1,50,3,50,671,8,50,1,50,1,50,1,51,4,51,676,8,51,11,51,12,
  	51,677,1,52,1,52,3,52,682,8,52,1,53,3,53,685,8,53,1,53,1,53,1,54,1,54,
  	1,54,1,54,1,54,1,54,1,54,3,54,696,8,54,1,54,1,54,1,54,1,54,1,54,1,54,
  	3,54,704,8,54,1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,
  	1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,3,55,726,8,55,1,56,3,56,
  	729,8,56,1,56,1,56,3,56,733,8,56,1,56,3,56,736,8,56,1,56,1,56,3,56,740,
  	8,56,1,57,1,57,1,57,1,57,1,57,1,57,3,57,748,8,57,3,57,750,8,57,1,57,1,
  	57,1,58,1,58,1,58,3,58,757,8,58,1,59,1,59,1,59,3,59,762,8,59,1,59,1,59,
  	1,60,4,60,767,8,60,11,60,12,60,768,1,60,0,4,4,16,62,80,61,0,2,4,6,8,10,
  	12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,
  	58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,
  	104,106,108,110,112,114,116,118,120,0,13,2,0,26,26,37,37,1,0,62,64,2,
  	0,58,58,60,60,1,0,56,57,1,0,52,55,1,0,87,88,1,0,76,86,1,0,89,90,2,0,93,
  	94,96,96,6,0,2,2,13,13,21,21,27,27,30,30,45,45,2,0,28,28,31,31,4,0,6,
  	6,22,22,34,34,38,38,2,0,18,18,43,43,864,0,123,1,0,0,0,2,130,1,0,0,0,4,
  	159,1,0,0,0,6,221,1,0,0,0,8,230,1,0,0,0,10,232,1,0,0,0,12,235,1,0,0,0,
  	14,243,1,0,0,0,16,251,1,0,0,0,18,269,1,0,0,0,20,276,1,0,0,0,22,280,1,
  	0,0,0,24,288,1,0,0,0,26,293,1,0,0,0,28,310,1,0,0,0,30,323,1,0,0,0,32,
  	325,1,0,0,0,34,328,1,0,0,0,36,340,1,0,0,0,38,344,1,0,0,0,40,348,1,0,0,
  	0,42,362,1,0,0,0,44,377,1,0,0,0,46,379,1,0,0,0,48,387,1,0,0,0,50,392,
  	1,0,0,0,52,394,1,0,0,0,54,399,1,0,0,0,56,401,1,0,0,0,58,403,1,0,0,0,60,
  	412,1,0,0,0,62,425,1,0,0,0,64,475,1,0,0,0,66,483,1,0,0,0,68,487,1,0,0,
  	0,70,492,1,0,0,0,72,500,1,0,0,0,74,507,1,0,0,0,76,515,1,0,0,0,78,524,
  	1,0,0,0,80,561,1,0,0,0,82,603,1,0,0,0,84,613,1,0,0,0,86,619,1,0,0,0,88,
  	623,1,0,0,0,90,627,1,0,0,0,92,637,1,0,0,0,94,639,1,0,0,0,96,653,1,0,0,
  	0,98,666,1,0,0,0,100,668,1,0,0,0,102,675,1,0,0,0,104,681,1,0,0,0,106,
  	684,1,0,0,0,108,703,1,0,0,0,110,725,1,0,0,0,112,732,1,0,0,0,114,749,1,
  	0,0,0,116,756,1,0,0,0,118,758,1,0,0,0,120,766,1,0,0,0,122,124,3,2,1,0,
  	123,122,1,0,0,0,123,124,1,0,0,0,124,125,1,0,0,0,125,126,5,0,0,1,126,1,
  	1,0,0,0,127,131,3,18,9,0,128,131,3,118,59,0,129,131,3,96,48,0,130,127,
  	1,0,0,0,130,128,1,0,0,0,130,129,1,0,0,0,131,132,1,0,0,0,132,130,1,0,0,
  	0,132,133,1,0,0,0,133,3,1,0,0,0,134,135,6,2,-1,0,135,160,3,8,4,0,136,
  	150,5,59,0,0,137,150,5,61,0,0,138,150,5,58,0,0,139,150,5,60,0,0,140,150,
  	5,70,0,0,141,150,5,71,0,0,142,143,5,46,0,0,143,144,3,76,38,0,144,145,
  	5,47,0,0,145,150,1,0,0,0,146,150,5,62,0,0,147,150,5,65,0,0,148,150,5,
  	26,0,0,149,136,1,0,0,0,149,137,1,0,0,0,149,138,1,0,0,0,149,139,1,0,0,
  	0,149,140,1,0,0,0,149,141,1,0,0,0,149,142,1,0,0,0,149,146,1,0,0,0,149,
  	147,1,0,0,0,149,148,1,0,0,0,150,151,1,0,0,0,151,158,3,4,2,0,152,153,7,
  	0,0,0,153,154,5,46,0,0,154,155,3,76,38,0,155,156,5,47,0,0,156,158,1,0,
  	0,0,157,149,1,0,0,0,157,152,1,0,0,0,158,160,1,0,0,0,159,134,1,0,0,0,159,
  	157,1,0,0,0,160,218,1,0,0,0,161,162,10,12,0,0,162,163,7,1,0,0,163,217,
  	3,4,2,13,164,165,10,11,0,0,165,166,7,2,0,0,166,217,3,4,2,12,167,168,10,
  	10,0,0,168,169,7,3,0,0,169,217,3,4,2,11,170,171,10,9,0,0,171,172,7,4,
  	0,0,172,217,3,4,2,10,173,174,10,8,0,0,174,175,7,5,0,0,175,217,3,4,2,9,
  	176,177,10,7,0,0,177,178,5,65,0,0,178,217,3,4,2,8,179,180,10,6,0,0,180,
  	181,5,69,0,0,181,217,3,4,2,7,182,183,10,5,0,0,183,184,5,66,0,0,184,217,
  	3,4,2,6,185,186,10,4,0,0,186,187,5,67,0,0,187,217,3,4,2,5,188,189,10,
  	3,0,0,189,190,5,68,0,0,190,217,3,4,2,4,191,192,10,2,0,0,192,193,5,72,
  	0,0,193,194,3,4,2,0,194,195,5,73,0,0,195,196,3,4,2,3,196,217,1,0,0,0,
  	197,198,10,1,0,0,198,199,7,6,0,0,199,217,3,4,2,1,200,214,10,14,0,0,201,
  	202,5,48,0,0,202,203,3,4,2,0,203,204,5,49,0,0,204,215,1,0,0,0,205,207,
  	5,46,0,0,206,208,3,14,7,0,207,206,1,0,0,0,207,208,1,0,0,0,208,209,1,0,
  	0,0,209,215,5,47,0,0,210,211,7,7,0,0,211,215,5,92,0,0,212,215,5,59,0,
  	0,213,215,5,61,0,0,214,201,1,0,0,0,214,205,1,0,0,0,214,210,1,0,0,0,214,
  	212,1,0,0,0,214,213,1,0,0,0,215,217,1,0,0,0,216,161,1,0,0,0,216,164,1,
  	0,0,0,216,167,1,0,0,0,216,170,1,0,0,0,216,173,1,0,0,0,216,176,1,0,0,0,
  	216,179,1,0,0,0,216,182,1,0,0,0,216,185,1,0,0,0,216,188,1,0,0,0,216,191,
  	1,0,0,0,216,197,1,0,0,0,216,200,1,0,0,0,217,220,1,0,0,0,218,216,1,0,0,
  	0,218,219,1,0,0,0,219,5,1,0,0,0,220,218,1,0,0,0,221,222,3,4,2,0,222,7,
  	1,0,0,0,223,231,5,92,0,0,224,231,3,10,5,0,225,231,3,12,6,0,226,227,5,
  	46,0,0,227,228,3,16,8,0,228,229,5,47,0,0,229,231,1,0,0,0,230,223,1,0,
  	0,0,230,224,1,0,0,0,230,225,1,0,0,0,230,226,1,0,0,0,231,9,1,0,0,0,232,
  	233,7,8,0,0,233,11,1,0,0,0,234,236,5,97,0,0,235,234,1,0,0,0,235,236,1,
  	0,0,0,236,237,1,0,0,0,237,239,5,1,0,0,238,240,5,98,0,0,239,238,1,0,0,
  	0,239,240,1,0,0,0,240,241,1,0,0,0,241,242,5,1,0,0,242,13,1,0,0,0,243,
  	248,3,4,2,0,244,245,5,75,0,0,245,247,3,4,2,0,246,244,1,0,0,0,247,250,
  	1,0,0,0,248,246,1,0,0,0,248,249,1,0,0,0,249,15,1,0,0,0,250,248,1,0,0,
  	0,251,252,6,8,-1,0,252,253,3,4,2,0,253,259,1,0,0,0,254,255,10,1,0,0,255,
  	256,5,75,0,0,256,258,3,4,2,0,257,254,1,0,0,0,258,261,1,0,0,0,259,257,
  	1,0,0,0,259,260,1,0,0,0,260,17,1,0,0,0,261,259,1,0,0,0,262,264,3,20,10,
  	0,263,265,3,22,11,0,264,263,1,0,0,0,264,265,1,0,0,0,265,266,1,0,0,0,266,
  	267,5,74,0,0,267,270,1,0,0,0,268,270,3,94,47,0,269,262,1,0,0,0,269,268,
  	1,0,0,0,270,19,1,0,0,0,271,277,3,26,13,0,272,277,3,28,14,0,273,277,3,
  	54,27,0,274,277,3,56,28,0,275,277,3,58,29,0,276,271,1,0,0,0,276,272,1,
  	0,0,0,276,273,1,0,0,0,276,274,1,0,0,0,276,275,1,0,0,0,277,278,1,0,0,0,
  	278,276,1,0,0,0,278,279,1,0,0,0,279,21,1,0,0,0,280,285,3,24,12,0,281,
  	282,5,75,0,0,282,284,3,24,12,0,283,281,1,0,0,0,284,287,1,0,0,0,285,283,
  	1,0,0,0,285,286,1,0,0,0,286,23,1,0,0,0,287,285,1,0,0,0,288,291,3,60,30,
  	0,289,290,5,76,0,0,290,292,3,84,42,0,291,289,1,0,0,0,291,292,1,0,0,0,
  	292,25,1,0,0,0,293,294,7,9,0,0,294,27,1,0,0,0,295,311,5,33,0,0,296,311,
  	5,5,0,0,297,311,5,24,0,0,298,311,5,19,0,0,299,311,5,20,0,0,300,311,5,
  	14,0,0,301,311,5,10,0,0,302,311,5,25,0,0,303,311,5,32,0,0,304,311,5,39,
  	0,0,305,311,5,40,0,0,306,311,3,52,26,0,307,311,3,30,15,0,308,311,3,44,
  	22,0,309,311,3,82,41,0,310,295,1,0,0,0,310,296,1,0,0,0,310,297,1,0,0,
  	0,310,298,1,0,0,0,310,299,1,0,0,0,310,300,1,0,0,0,310,301,1,0,0,0,310,
  	302,1,0,0,0,310,303,1,0,0,0,310,304,1,0,0,0,310,305,1,0,0,0,310,306,1,
  	0,0,0,310,307,1,0,0,0,310,308,1,0,0,0,310,309,1,0,0,0,311,29,1,0,0,0,
  	312,314,3,32,16,0,313,315,5,92,0,0,314,313,1,0,0,0,314,315,1,0,0,0,315,
  	316,1,0,0,0,316,317,5,50,0,0,317,318,3,34,17,0,318,319,5,51,0,0,319,324,
  	1,0,0,0,320,321,3,32,16,0,321,322,5,92,0,0,322,324,1,0,0,0,323,312,1,
  	0,0,0,323,320,1,0,0,0,324,31,1,0,0,0,325,326,7,10,0,0,326,33,1,0,0,0,
  	327,329,3,36,18,0,328,327,1,0,0,0,329,330,1,0,0,0,330,328,1,0,0,0,330,
  	331,1,0,0,0,331,35,1,0,0,0,332,333,3,38,19,0,333,334,3,40,20,0,334,335,
  	5,74,0,0,335,341,1,0,0,0,336,337,3,38,19,0,337,338,5,74,0,0,338,341,1,
  	0,0,0,339,341,3,94,47,0,340,332,1,0,0,0,340,336,1,0,0,0,340,339,1,0,0,
  	0,341,37,1,0,0,0,342,345,3,28,14,0,343,345,3,54,27,0,344,342,1,0,0,0,
  	344,343,1,0,0,0,345,346,1,0,0,0,346,344,1,0,0,0,346,347,1,0,0,0,347,39,
  	1,0,0,0,348,353,3,42,21,0,349,350,5,75,0,0,350,352,3,42,21,0,351,349,
  	1,0,0,0,352,355,1,0,0,0,353,351,1,0,0,0,353,354,1,0,0,0,354,41,1,0,0,
  	0,355,353,1,0,0,0,356,363,3,60,30,0,357,359,3,60,30,0,358,357,1,0,0,0,
  	358,359,1,0,0,0,359,360,1,0,0,0,360,361,5,73,0,0,361,363,3,6,3,0,362,
  	356,1,0,0,0,362,358,1,0,0,0,363,43,1,0,0,0,364,366,5,12,0,0,365,367,5,
  	92,0,0,366,365,1,0,0,0,366,367,1,0,0,0,367,368,1,0,0,0,368,369,5,50,0,
  	0,369,371,3,46,23,0,370,372,5,75,0,0,371,370,1,0,0,0,371,372,1,0,0,0,
  	372,373,1,0,0,0,373,374,5,51,0,0,374,378,1,0,0,0,375,376,5,12,0,0,376,
  	378,5,92,0,0,377,364,1,0,0,0,377,375,1,0,0,0,378,45,1,0,0,0,379,384,3,
  	48,24,0,380,381,5,75,0,0,381,383,3,48,24,0,382,380,1,0,0,0,383,386,1,
  	0,0,0,384,382,1,0,0,0,384,385,1,0,0,0,385,47,1,0,0,0,386,384,1,0,0,0,
  	387,390,3,50,25,0,388,389,5,76,0,0,389,391,3,6,3,0,390,388,1,0,0,0,390,
  	391,1,0,0,0,391,49,1,0,0,0,392,393,5,92,0,0,393,51,1,0,0,0,394,395,5,
  	38,0,0,395,396,5,46,0,0,396,397,3,76,38,0,397,398,5,47,0,0,398,53,1,0,
  	0,0,399,400,7,11,0,0,400,55,1,0,0,0,401,402,7,12,0,0,402,57,1,0,0,0,403,
  	404,5,36,0,0,404,407,5,46,0,0,405,408,3,76,38,0,406,408,3,6,3,0,407,405,
  	1,0,0,0,407,406,1,0,0,0,408,409,1,0,0,0,409,410,5,47,0,0,410,59,1,0,0,
  	0,411,413,3,64,32,0,412,411,1,0,0,0,412,413,1,0,0,0,413,414,1,0,0,0,414,
  	415,3,62,31,0,415,61,1,0,0,0,416,417,6,31,-1,0,417,426,5,92,0,0,418,419,
  	5,46,0,0,419,420,3,60,30,0,420,421,5,47,0,0,421,426,1,0,0,0,422,423,5,
  	92,0,0,423,424,5,73,0,0,424,426,5,95,0,0,425,416,1,0,0,0,425,418,1,0,
  	0,0,425,422,1,0,0,0,426,472,1,0,0,0,427,428,10,7,0,0,428,430,5,48,0,0,
  	429,431,3,66,33,0,430,429,1,0,0,0,430,431,1,0,0,0,431,433,1,0,0,0,432,
  	434,3,4,2,0,433,432,1,0,0,0,433,434,1,0,0,0,434,435,1,0,0,0,435,471,5,
  	49,0,0,436,437,10,6,0,0,437,438,5,48,0,0,438,440,5,27,0,0,439,441,3,66,
  	33,0,440,439,1,0,0,0,440,441,1,0,0,0,441,442,1,0,0,0,442,443,3,4,2,0,
  	443,444,5,49,0,0,444,471,1,0,0,0,445,446,10,5,0,0,446,447,5,48,0,0,447,
  	448,3,66,33,0,448,449,5,27,0,0,449,450,3,4,2,0,450,451,5,49,0,0,451,471,
  	1,0,0,0,452,453,10,4,0,0,453,455,5,48,0,0,454,456,3,66,33,0,455,454,1,
  	0,0,0,455,456,1,0,0,0,456,457,1,0,0,0,457,458,5,62,0,0,458,471,5,49,0,
  	0,459,460,10,3,0,0,460,461,5,46,0,0,461,462,3,68,34,0,462,463,5,47,0,
  	0,463,471,1,0,0,0,464,465,10,2,0,0,465,467,5,46,0,0,466,468,3,74,37,0,
  	467,466,1,0,0,0,467,468,1,0,0,0,468,469,1,0,0,0,469,471,5,47,0,0,470,
  	427,1,0,0,0,470,436,1,0,0,0,470,445,1,0,0,0,470,452,1,0,0,0,470,459,1,
  	0,0,0,470,464,1,0,0,0,471,474,1,0,0,0,472,470,1,0,0,0,472,473,1,0,0,0,
  	473,63,1,0,0,0,474,472,1,0,0,0,475,477,5,62,0,0,476,478,3,66,33,0,477,
  	476,1,0,0,0,477,478,1,0,0,0,478,480,1,0,0,0,479,481,3,64,32,0,480,479,
  	1,0,0,0,480,481,1,0,0,0,481,65,1,0,0,0,482,484,3,54,27,0,483,482,1,0,
  	0,0,484,485,1,0,0,0,485,483,1,0,0,0,485,486,1,0,0,0,486,67,1,0,0,0,487,
  	490,3,70,35,0,488,489,5,75,0,0,489,491,5,91,0,0,490,488,1,0,0,0,490,491,
  	1,0,0,0,491,69,1,0,0,0,492,497,3,72,36,0,493,494,5,75,0,0,494,496,3,72,
  	36,0,495,493,1,0,0,0,496,499,1,0,0,0,497,495,1,0,0,0,497,498,1,0,0,0,
  	498,71,1,0,0,0,499,497,1,0,0,0,500,505,3,20,10,0,501,506,3,60,30,0,502,
  	504,3,78,39,0,503,502,1,0,0,0,503,504,1,0,0,0,504,506,1,0,0,0,505,501,
  	1,0,0,0,505,503,1,0,0,0,506,73,1,0,0,0,507,512,5,92,0,0,508,509,5,75,
  	0,0,509,511,5,92,0,0,510,508,1,0,0,0,511,514,1,0,0,0,512,510,1,0,0,0,
  	512,513,1,0,0,0,513,75,1,0,0,0,514,512,1,0,0,0,515,517,3,38,19,0,516,
  	518,3,78,39,0,517,516,1,0,0,0,517,518,1,0,0,0,518,77,1,0,0,0,519,525,
  	3,64,32,0,520,522,3,64,32,0,521,520,1,0,0,0,521,522,1,0,0,0,522,523,1,
  	0,0,0,523,525,3,80,40,0,524,519,1,0,0,0,524,521,1,0,0,0,525,79,1,0,0,
  	0,526,527,6,40,-1,0,527,528,5,46,0,0,528,529,3,78,39,0,529,530,5,47,0,
  	0,530,562,1,0,0,0,531,533,5,48,0,0,532,534,3,66,33,0,533,532,1,0,0,0,
  	533,534,1,0,0,0,534,536,1,0,0,0,535,537,3,4,2,0,536,535,1,0,0,0,536,537,
  	1,0,0,0,537,538,1,0,0,0,538,562,5,49,0,0,539,540,5,48,0,0,540,542,5,27,
  	0,0,541,543,3,66,33,0,542,541,1,0,0,0,542,543,1,0,0,0,543,544,1,0,0,0,
  	544,545,3,4,2,0,545,546,5,49,0,0,546,562,1,0,0,0,547,548,5,48,0,0,548,
  	549,3,66,33,0,549,550,5,27,0,0,550,551,3,4,2,0,551,552,5,49,0,0,552,562,
  	1,0,0,0,553,554,5,48,0,0,554,555,5,62,0,0,555,562,5,49,0,0,556,558,5,
  	46,0,0,557,559,3,68,34,0,558,557,1,0,0,0,558,559,1,0,0,0,559,560,1,0,
  	0,0,560,562,5,47,0,0,561,526,1,0,0,0,561,531,1,0,0,0,561,539,1,0,0,0,
  	561,547,1,0,0,0,561,553,1,0,0,0,561,556,1,0,0,0,562,600,1,0,0,0,563,564,
  	10,5,0,0,564,566,5,48,0,0,565,567,3,66,33,0,566,565,1,0,0,0,566,567,1,
  	0,0,0,567,569,1,0,0,0,568,570,3,4,2,0,569,568,1,0,0,0,569,570,1,0,0,0,
  	570,571,1,0,0,0,571,599,5,49,0,0,572,573,10,4,0,0,573,574,5,48,0,0,574,
  	576,5,27,0,0,575,577,3,66,33,0,576,575,1,0,0,0,576,577,1,0,0,0,577,578,
  	1,0,0,0,578,579,3,4,2,0,579,580,5,49,0,0,580,599,1,0,0,0,581,582,10,3,
  	0,0,582,583,5,48,0,0,583,584,3,66,33,0,584,585,5,27,0,0,585,586,3,4,2,
  	0,586,587,5,49,0,0,587,599,1,0,0,0,588,589,10,2,0,0,589,590,5,48,0,0,
  	590,591,5,62,0,0,591,599,5,49,0,0,592,593,10,1,0,0,593,595,5,46,0,0,594,
  	596,3,68,34,0,595,594,1,0,0,0,595,596,1,0,0,0,596,597,1,0,0,0,597,599,
  	5,47,0,0,598,563,1,0,0,0,598,572,1,0,0,0,598,581,1,0,0,0,598,588,1,0,
  	0,0,598,592,1,0,0,0,599,602,1,0,0,0,600,598,1,0,0,0,600,601,1,0,0,0,601,
  	81,1,0,0,0,602,600,1,0,0,0,603,604,5,92,0,0,604,83,1,0,0,0,605,614,3,
  	4,2,0,606,607,5,50,0,0,607,609,3,86,43,0,608,610,5,75,0,0,609,608,1,0,
  	0,0,609,610,1,0,0,0,610,611,1,0,0,0,611,612,5,51,0,0,612,614,1,0,0,0,
  	613,605,1,0,0,0,613,606,1,0,0,0,614,85,1,0,0,0,615,617,3,88,44,0,616,
  	615,1,0,0,0,616,617,1,0,0,0,617,618,1,0,0,0,618,620,3,84,42,0,619,616,
  	1,0,0,0,620,621,1,0,0,0,621,619,1,0,0,0,621,622,1,0,0,0,622,87,1,0,0,
  	0,623,624,3,90,45,0,624,625,5,76,0,0,625,89,1,0,0,0,626,628,3,92,46,0,
  	627,626,1,0,0,0,628,629,1,0,0,0,629,627,1,0,0,0,629,630,1,0,0,0,630,91,
  	1,0,0,0,631,632,5,48,0,0,632,633,3,6,3,0,633,634,5,49,0,0,634,638,1,0,
  	0,0,635,636,5,90,0,0,636,638,5,92,0,0,637,631,1,0,0,0,637,635,1,0,0,0,
  	638,93,1,0,0,0,639,640,5,44,0,0,640,641,5,46,0,0,641,642,3,6,3,0,642,
  	643,5,75,0,0,643,644,3,12,6,0,644,645,5,47,0,0,645,646,5,74,0,0,646,95,
  	1,0,0,0,647,654,3,98,49,0,648,654,3,100,50,0,649,654,3,106,53,0,650,654,
  	3,108,54,0,651,654,3,110,55,0,652,654,3,114,57,0,653,647,1,0,0,0,653,
  	648,1,0,0,0,653,649,1,0,0,0,653,650,1,0,0,0,653,651,1,0,0,0,653,652,1,
  	0,0,0,654,97,1,0,0,0,655,656,5,92,0,0,656,657,5,73,0,0,657,667,3,96,48,
  	0,658,659,5,4,0,0,659,660,3,6,3,0,660,661,5,73,0,0,661,662,3,96,48,0,
  	662,667,1,0,0,0,663,664,5,8,0,0,664,665,5,73,0,0,665,667,3,96,48,0,666,
  	655,1,0,0,0,666,658,1,0,0,0,666,663,1,0,0,0,667,99,1,0,0,0,668,670,5,
  	50,0,0,669,671,3,102,51,0,670,669,1,0,0,0,670,671,1,0,0,0,671,672,1,0,
  	0,0,672,673,5,51,0,0,673,101,1,0,0,0,674,676,3,104,52,0,675,674,1,0,0,
  	0,676,677,1,0,0,0,677,675,1,0,0,0,677,678,1,0,0,0,678,103,1,0,0,0,679,
  	682,3,96,48,0,680,682,3,18,9,0,681,679,1,0,0,0,681,680,1,0,0,0,682,105,
  	1,0,0,0,683,685,3,16,8,0,684,683,1,0,0,0,684,685,1,0,0,0,685,686,1,0,
  	0,0,686,687,5,74,0,0,687,107,1,0,0,0,688,689,5,17,0,0,689,690,5,46,0,
  	0,690,691,3,16,8,0,691,692,5,47,0,0,692,695,3,96,48,0,693,694,5,11,0,
  	0,694,696,3,96,48,0,695,693,1,0,0,0,695,696,1,0,0,0,696,704,1,0,0,0,697,
  	698,5,29,0,0,698,699,5,46,0,0,699,700,3,16,8,0,700,701,5,47,0,0,701,702,
  	3,96,48,0,702,704,1,0,0,0,703,688,1,0,0,0,703,697,1,0,0,0,704,109,1,0,
  	0,0,705,706,5,35,0,0,706,707,5,46,0,0,707,708,3,16,8,0,708,709,5,47,0,
  	0,709,710,3,96,48,0,710,726,1,0,0,0,711,712,5,9,0,0,712,713,3,96,48,0,
  	713,714,5,35,0,0,714,715,5,46,0,0,715,716,3,16,8,0,716,717,5,47,0,0,717,
  	718,5,74,0,0,718,726,1,0,0,0,719,720,5,15,0,0,720,721,5,46,0,0,721,722,
  	3,112,56,0,722,723,5,47,0,0,723,724,3,96,48,0,724,726,1,0,0,0,725,705,
  	1,0,0,0,725,711,1,0,0,0,725,719,1,0,0,0,726,111,1,0,0,0,727,729,3,16,
  	8,0,728,727,1,0,0,0,728,729,1,0,0,0,729,730,1,0,0,0,730,733,5,74,0,0,
  	731,733,3,18,9,0,732,728,1,0,0,0,732,731,1,0,0,0,733,735,1,0,0,0,734,
  	736,3,16,8,0,735,734,1,0,0,0,735,736,1,0,0,0,736,737,1,0,0,0,737,739,
  	5,74,0,0,738,740,3,16,8,0,739,738,1,0,0,0,739,740,1,0,0,0,740,113,1,0,
  	0,0,741,742,5,16,0,0,742,750,5,92,0,0,743,750,5,7,0,0,744,750,5,3,0,0,
  	745,747,5,23,0,0,746,748,3,16,8,0,747,746,1,0,0,0,747,748,1,0,0,0,748,
  	750,1,0,0,0,749,741,1,0,0,0,749,743,1,0,0,0,749,744,1,0,0,0,749,745,1,
  	0,0,0,750,751,1,0,0,0,751,752,5,74,0,0,752,115,1,0,0,0,753,757,3,118,
  	59,0,754,757,3,18,9,0,755,757,5,74,0,0,756,753,1,0,0,0,756,754,1,0,0,
  	0,756,755,1,0,0,0,757,117,1,0,0,0,758,759,3,20,10,0,759,761,3,60,30,0,
  	760,762,3,120,60,0,761,760,1,0,0,0,761,762,1,0,0,0,762,763,1,0,0,0,763,
  	764,3,100,50,0,764,119,1,0,0,0,765,767,3,18,9,0,766,765,1,0,0,0,767,768,
  	1,0,0,0,768,766,1,0,0,0,768,769,1,0,0,0,769,121,1,0,0,0,92,123,130,132,
  	149,157,159,207,214,216,218,230,235,239,248,259,264,269,276,278,285,291,
  	310,314,323,330,340,344,346,353,358,362,366,371,377,384,390,407,412,425,
  	430,433,440,455,467,470,472,477,480,485,490,497,503,505,512,517,521,524,
  	533,536,542,558,561,566,569,576,595,598,600,609,613,616,621,629,637,653,
  	666,670,677,681,684,695,703,725,728,732,735,739,747,749,756,761,768
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  cParserStaticData = staticData.release();
}

}

CParser::CParser(TokenStream *input) : CParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CParser::CParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *cParserStaticData->atn, cParserStaticData->decisionToDFA, cParserStaticData->sharedContextCache, options);
}

CParser::~CParser() {
  delete _interpreter;
}

const atn::ATN& CParser::getATN() const {
  return *cParserStaticData->atn;
}

std::string CParser::getGrammarFileName() const {
  return "C.g4";
}

const std::vector<std::string>& CParser::getRuleNames() const {
  return cParserStaticData->ruleNames;
}

const dfa::Vocabulary& CParser::getVocabulary() const {
  return cParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CParser::getSerializedATN() const {
  return cParserStaticData->serializedATN;
}


//----------------- CompilationUnitContext ------------------------------------------------------------------

CParser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::CompilationUnitContext::EOF() {
  return getToken(CParser::EOF, 0);
}

CParser::TranslationUnitContext* CParser::CompilationUnitContext::translationUnit() {
  return getRuleContext<CParser::TranslationUnitContext>(0);
}


size_t CParser::CompilationUnitContext::getRuleIndex() const {
  return CParser::RuleCompilationUnit;
}


std::any CParser::CompilationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitCompilationUnit(this);
  else
    return visitor->visitChildren(this);
}

CParser::CompilationUnitContext* CParser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, CParser::RuleCompilationUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(123);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8936401701028493310) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 7381975649) != 0)) {
      setState(122);
      translationUnit();
    }
    setState(125);
    match(CParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TranslationUnitContext ------------------------------------------------------------------

CParser::TranslationUnitContext::TranslationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::DeclarationContext *> CParser::TranslationUnitContext::declaration() {
  return getRuleContexts<CParser::DeclarationContext>();
}

CParser::DeclarationContext* CParser::TranslationUnitContext::declaration(size_t i) {
  return getRuleContext<CParser::DeclarationContext>(i);
}

std::vector<CParser::FunctionDefinitionContext *> CParser::TranslationUnitContext::functionDefinition() {
  return getRuleContexts<CParser::FunctionDefinitionContext>();
}

CParser::FunctionDefinitionContext* CParser::TranslationUnitContext::functionDefinition(size_t i) {
  return getRuleContext<CParser::FunctionDefinitionContext>(i);
}

std::vector<CParser::StatementContext *> CParser::TranslationUnitContext::statement() {
  return getRuleContexts<CParser::StatementContext>();
}

CParser::StatementContext* CParser::TranslationUnitContext::statement(size_t i) {
  return getRuleContext<CParser::StatementContext>(i);
}


size_t CParser::TranslationUnitContext::getRuleIndex() const {
  return CParser::RuleTranslationUnit;
}


std::any CParser::TranslationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitTranslationUnit(this);
  else
    return visitor->visitChildren(this);
}

CParser::TranslationUnitContext* CParser::translationUnit() {
  TranslationUnitContext *_localctx = _tracker.createInstance<TranslationUnitContext>(_ctx, getState());
  enterRule(_localctx, 2, CParser::RuleTranslationUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(130);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
      case 1: {
        setState(127);
        declaration();
        break;
      }

      case 2: {
        setState(128);
        functionDefinition();
        break;
      }

      case 3: {
        setState(129);
        statement();
        break;
      }

      default:
        break;
      }
      setState(132); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8936401701028493310) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 7381975649) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

CParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CParser::ExpressionContext::getRuleIndex() const {
  return CParser::RuleExpression;
}

void CParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ShiftExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::ShiftExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::ShiftExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::ShiftExpressionContext::LeftShift() {
  return getToken(CParser::LeftShift, 0);
}

tree::TerminalNode* CParser::ShiftExpressionContext::RightShift() {
  return getToken(CParser::RightShift, 0);
}

CParser::ShiftExpressionContext::ShiftExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::ShiftExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitShiftExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AdditiveExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::AdditiveExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::AdditiveExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::AdditiveExpressionContext::Plus() {
  return getToken(CParser::Plus, 0);
}

tree::TerminalNode* CParser::AdditiveExpressionContext::Minus() {
  return getToken(CParser::Minus, 0);
}

CParser::AdditiveExpressionContext::AdditiveExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::AdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RelationalExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::RelationalExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::RelationalExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::RelationalExpressionContext::Less() {
  return getToken(CParser::Less, 0);
}

tree::TerminalNode* CParser::RelationalExpressionContext::LessEqual() {
  return getToken(CParser::LessEqual, 0);
}

tree::TerminalNode* CParser::RelationalExpressionContext::Greater() {
  return getToken(CParser::Greater, 0);
}

tree::TerminalNode* CParser::RelationalExpressionContext::GreaterEqual() {
  return getToken(CParser::GreaterEqual, 0);
}

CParser::RelationalExpressionContext::RelationalExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InclusiveOrExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::InclusiveOrExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::InclusiveOrExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::InclusiveOrExpressionContext::Or() {
  return getToken(CParser::Or, 0);
}

CParser::InclusiveOrExpressionContext::InclusiveOrExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::InclusiveOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitInclusiveOrExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConditionalExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::ConditionalExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::ConditionalExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::ConditionalExpressionContext::Question() {
  return getToken(CParser::Question, 0);
}

tree::TerminalNode* CParser::ConditionalExpressionContext::Colon() {
  return getToken(CParser::Colon, 0);
}

CParser::ConditionalExpressionContext::ConditionalExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::ConditionalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitConditionalExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignmentExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::AssignmentExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::AssignmentExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::AssignmentExpressionContext::Assign() {
  return getToken(CParser::Assign, 0);
}

tree::TerminalNode* CParser::AssignmentExpressionContext::PlusAssign() {
  return getToken(CParser::PlusAssign, 0);
}

tree::TerminalNode* CParser::AssignmentExpressionContext::MinusAssign() {
  return getToken(CParser::MinusAssign, 0);
}

tree::TerminalNode* CParser::AssignmentExpressionContext::StarAssign() {
  return getToken(CParser::StarAssign, 0);
}

tree::TerminalNode* CParser::AssignmentExpressionContext::DivAssign() {
  return getToken(CParser::DivAssign, 0);
}

tree::TerminalNode* CParser::AssignmentExpressionContext::ModAssign() {
  return getToken(CParser::ModAssign, 0);
}

tree::TerminalNode* CParser::AssignmentExpressionContext::LeftShiftAssign() {
  return getToken(CParser::LeftShiftAssign, 0);
}

tree::TerminalNode* CParser::AssignmentExpressionContext::RightShiftAssign() {
  return getToken(CParser::RightShiftAssign, 0);
}

tree::TerminalNode* CParser::AssignmentExpressionContext::AndAssign() {
  return getToken(CParser::AndAssign, 0);
}

tree::TerminalNode* CParser::AssignmentExpressionContext::XorAssign() {
  return getToken(CParser::XorAssign, 0);
}

tree::TerminalNode* CParser::AssignmentExpressionContext::OrAssign() {
  return getToken(CParser::OrAssign, 0);
}

CParser::AssignmentExpressionContext::AssignmentExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::AssignmentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitAssignmentExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::MultiplicativeExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::MultiplicativeExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::MultiplicativeExpressionContext::Star() {
  return getToken(CParser::Star, 0);
}

tree::TerminalNode* CParser::MultiplicativeExpressionContext::Div() {
  return getToken(CParser::Div, 0);
}

tree::TerminalNode* CParser::MultiplicativeExpressionContext::Mod() {
  return getToken(CParser::Mod, 0);
}

CParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::MultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::LogicalOrExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::LogicalOrExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::LogicalOrExpressionContext::OrOr() {
  return getToken(CParser::OrOr, 0);
}

CParser::LogicalOrExpressionContext::LogicalOrExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::LogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::AndExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::AndExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::AndExpressionContext::And() {
  return getToken(CParser::And, 0);
}

CParser::AndExpressionContext::AndExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::AndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitAndExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExclusiveOrExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::ExclusiveOrExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::ExclusiveOrExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::ExclusiveOrExpressionContext::Caret() {
  return getToken(CParser::Caret, 0);
}

CParser::ExclusiveOrExpressionContext::ExclusiveOrExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::ExclusiveOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitExclusiveOrExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EqualityExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::EqualityExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::EqualityExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::EqualityExpressionContext::Equal() {
  return getToken(CParser::Equal, 0);
}

tree::TerminalNode* CParser::EqualityExpressionContext::NotEqual() {
  return getToken(CParser::NotEqual, 0);
}

CParser::EqualityExpressionContext::EqualityExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::EqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::LogicalAndExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::LogicalAndExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::LogicalAndExpressionContext::AndAnd() {
  return getToken(CParser::AndAnd, 0);
}

CParser::LogicalAndExpressionContext::LogicalAndExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::LogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExpressionContext ------------------------------------------------------------------

CParser::ExpressionContext* CParser::UnaryExpressionContext::expression() {
  return getRuleContext<CParser::ExpressionContext>(0);
}

tree::TerminalNode* CParser::UnaryExpressionContext::LeftParen() {
  return getToken(CParser::LeftParen, 0);
}

CParser::TypeNameContext* CParser::UnaryExpressionContext::typeName() {
  return getRuleContext<CParser::TypeNameContext>(0);
}

tree::TerminalNode* CParser::UnaryExpressionContext::RightParen() {
  return getToken(CParser::RightParen, 0);
}

tree::TerminalNode* CParser::UnaryExpressionContext::Sizeof() {
  return getToken(CParser::Sizeof, 0);
}

tree::TerminalNode* CParser::UnaryExpressionContext::Alignof() {
  return getToken(CParser::Alignof, 0);
}

tree::TerminalNode* CParser::UnaryExpressionContext::PlusPlus() {
  return getToken(CParser::PlusPlus, 0);
}

tree::TerminalNode* CParser::UnaryExpressionContext::MinusMinus() {
  return getToken(CParser::MinusMinus, 0);
}

tree::TerminalNode* CParser::UnaryExpressionContext::Plus() {
  return getToken(CParser::Plus, 0);
}

tree::TerminalNode* CParser::UnaryExpressionContext::Minus() {
  return getToken(CParser::Minus, 0);
}

tree::TerminalNode* CParser::UnaryExpressionContext::Not() {
  return getToken(CParser::Not, 0);
}

tree::TerminalNode* CParser::UnaryExpressionContext::Tilde() {
  return getToken(CParser::Tilde, 0);
}

tree::TerminalNode* CParser::UnaryExpressionContext::Star() {
  return getToken(CParser::Star, 0);
}

tree::TerminalNode* CParser::UnaryExpressionContext::And() {
  return getToken(CParser::And, 0);
}

CParser::UnaryExpressionContext::UnaryExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::UnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PostfixExpressionContext ------------------------------------------------------------------

std::vector<CParser::ExpressionContext *> CParser::PostfixExpressionContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::PostfixExpressionContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

tree::TerminalNode* CParser::PostfixExpressionContext::LeftBracket() {
  return getToken(CParser::LeftBracket, 0);
}

tree::TerminalNode* CParser::PostfixExpressionContext::RightBracket() {
  return getToken(CParser::RightBracket, 0);
}

tree::TerminalNode* CParser::PostfixExpressionContext::LeftParen() {
  return getToken(CParser::LeftParen, 0);
}

tree::TerminalNode* CParser::PostfixExpressionContext::RightParen() {
  return getToken(CParser::RightParen, 0);
}

tree::TerminalNode* CParser::PostfixExpressionContext::Identifier() {
  return getToken(CParser::Identifier, 0);
}

tree::TerminalNode* CParser::PostfixExpressionContext::PlusPlus() {
  return getToken(CParser::PlusPlus, 0);
}

tree::TerminalNode* CParser::PostfixExpressionContext::MinusMinus() {
  return getToken(CParser::MinusMinus, 0);
}

tree::TerminalNode* CParser::PostfixExpressionContext::Dot() {
  return getToken(CParser::Dot, 0);
}

tree::TerminalNode* CParser::PostfixExpressionContext::Arrow() {
  return getToken(CParser::Arrow, 0);
}

CParser::ArgumentExpressionListContext* CParser::PostfixExpressionContext::argumentExpressionList() {
  return getRuleContext<CParser::ArgumentExpressionListContext>(0);
}

CParser::PostfixExpressionContext::PostfixExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::PostfixExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitPostfixExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrimaryContext ------------------------------------------------------------------

CParser::PrimaryExpressionContext* CParser::PrimaryContext::primaryExpression() {
  return getRuleContext<CParser::PrimaryExpressionContext>(0);
}

CParser::PrimaryContext::PrimaryContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CParser::PrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitPrimary(this);
  else
    return visitor->visitChildren(this);
}

CParser::ExpressionContext* CParser::expression() {
   return expression(0);
}

CParser::ExpressionContext* CParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  CParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, CParser::RuleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(159);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PrimaryContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(135);
      primaryExpression();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<UnaryExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(157);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(149);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case CParser::PlusPlus: {
            setState(136);
            match(CParser::PlusPlus);
            break;
          }

          case CParser::MinusMinus: {
            setState(137);
            match(CParser::MinusMinus);
            break;
          }

          case CParser::Plus: {
            setState(138);
            match(CParser::Plus);
            break;
          }

          case CParser::Minus: {
            setState(139);
            match(CParser::Minus);
            break;
          }

          case CParser::Not: {
            setState(140);
            match(CParser::Not);
            break;
          }

          case CParser::Tilde: {
            setState(141);
            match(CParser::Tilde);
            break;
          }

          case CParser::LeftParen: {
            setState(142);
            match(CParser::LeftParen);
            setState(143);
            typeName();
            setState(144);
            match(CParser::RightParen);
            break;
          }

          case CParser::Star: {
            setState(146);
            match(CParser::Star);
            break;
          }

          case CParser::And: {
            setState(147);
            match(CParser::And);
            break;
          }

          case CParser::Sizeof: {
            setState(148);
            match(CParser::Sizeof);
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(151);
        expression(0);
        break;
      }

      case 2: {
        setState(152);
        _la = _input->LA(1);
        if (!(_la == CParser::Sizeof

        || _la == CParser::Alignof)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(153);
        match(CParser::LeftParen);
        setState(154);
        typeName();
        setState(155);
        match(CParser::RightParen);
        break;
      }

      default:
        break;
      }
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(218);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(216);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MultiplicativeExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(161);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(162);
          _la = _input->LA(1);
          if (!(((((_la - 62) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 62)) & 7) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(163);
          expression(13);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AdditiveExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(164);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(165);
          _la = _input->LA(1);
          if (!(_la == CParser::Plus

          || _la == CParser::Minus)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(166);
          expression(12);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ShiftExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(167);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(168);
          _la = _input->LA(1);
          if (!(_la == CParser::LeftShift

          || _la == CParser::RightShift)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(169);
          expression(11);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<RelationalExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(170);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(171);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 67553994410557440) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(172);
          expression(10);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<EqualityExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(173);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(174);
          _la = _input->LA(1);
          if (!(_la == CParser::Equal

          || _la == CParser::NotEqual)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(175);
          expression(9);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<AndExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(176);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(177);
          match(CParser::And);
          setState(178);
          expression(8);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<ExclusiveOrExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(179);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(180);
          match(CParser::Caret);
          setState(181);
          expression(7);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<InclusiveOrExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(182);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(183);
          match(CParser::Or);
          setState(184);
          expression(6);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<LogicalAndExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(185);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(186);
          match(CParser::AndAnd);
          setState(187);
          expression(5);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<LogicalOrExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(188);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(189);
          match(CParser::OrOr);
          setState(190);
          expression(4);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<ConditionalExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(191);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(192);
          match(CParser::Question);
          setState(193);
          expression(0);
          setState(194);
          match(CParser::Colon);
          setState(195);
          expression(3);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<AssignmentExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(197);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(198);
          _la = _input->LA(1);
          if (!(((((_la - 76) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 76)) & 2047) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(199);
          expression(1);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<PostfixExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(200);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(214);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case CParser::LeftBracket: {
              setState(201);
              match(CParser::LeftBracket);
              setState(202);
              expression(0);
              setState(203);
              match(CParser::RightBracket);
              break;
            }

            case CParser::LeftParen: {
              setState(205);
              match(CParser::LeftParen);
              setState(207);
              _errHandler->sync(this);

              _la = _input->LA(1);
              if ((((_la & ~ 0x3fULL) == 0) &&
                ((1ULL << _la) & 8935212166953304066) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
                ((1ULL << (_la - 65)) & 7381975137) != 0)) {
                setState(206);
                argumentExpressionList();
              }
              setState(209);
              match(CParser::RightParen);
              break;
            }

            case CParser::Arrow:
            case CParser::Dot: {
              setState(210);
              _la = _input->LA(1);
              if (!(_la == CParser::Arrow

              || _la == CParser::Dot)) {
              _errHandler->recoverInline(this);
              }
              else {
                _errHandler->reportMatch(this);
                consume();
              }
              setState(211);
              match(CParser::Identifier);
              break;
            }

            case CParser::PlusPlus: {
              setState(212);
              match(CParser::PlusPlus);
              break;
            }

            case CParser::MinusMinus: {
              setState(213);
              match(CParser::MinusMinus);
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          break;
        }

        default:
          break;
        } 
      }
      setState(220);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ConstantExpressionContext ------------------------------------------------------------------

CParser::ConstantExpressionContext::ConstantExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::ExpressionContext* CParser::ConstantExpressionContext::expression() {
  return getRuleContext<CParser::ExpressionContext>(0);
}


size_t CParser::ConstantExpressionContext::getRuleIndex() const {
  return CParser::RuleConstantExpression;
}


std::any CParser::ConstantExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitConstantExpression(this);
  else
    return visitor->visitChildren(this);
}

CParser::ConstantExpressionContext* CParser::constantExpression() {
  ConstantExpressionContext *_localctx = _tracker.createInstance<ConstantExpressionContext>(_ctx, getState());
  enterRule(_localctx, 6, CParser::RuleConstantExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(221);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

CParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::PrimaryExpressionContext::Identifier() {
  return getToken(CParser::Identifier, 0);
}

CParser::ConstantContext* CParser::PrimaryExpressionContext::constant() {
  return getRuleContext<CParser::ConstantContext>(0);
}

CParser::StringLiteralContext* CParser::PrimaryExpressionContext::stringLiteral() {
  return getRuleContext<CParser::StringLiteralContext>(0);
}

tree::TerminalNode* CParser::PrimaryExpressionContext::LeftParen() {
  return getToken(CParser::LeftParen, 0);
}

CParser::CommaExpressionContext* CParser::PrimaryExpressionContext::commaExpression() {
  return getRuleContext<CParser::CommaExpressionContext>(0);
}

tree::TerminalNode* CParser::PrimaryExpressionContext::RightParen() {
  return getToken(CParser::RightParen, 0);
}


size_t CParser::PrimaryExpressionContext::getRuleIndex() const {
  return CParser::RulePrimaryExpression;
}


std::any CParser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

CParser::PrimaryExpressionContext* CParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 8, CParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(230);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(223);
        match(CParser::Identifier);
        break;
      }

      case CParser::IntegerConstant:
      case CParser::FloatingConstant:
      case CParser::CharacterConstant: {
        enterOuterAlt(_localctx, 2);
        setState(224);
        constant();
        break;
      }

      case CParser::T__0:
      case CParser::EncodingPrefix: {
        enterOuterAlt(_localctx, 3);
        setState(225);
        stringLiteral();
        break;
      }

      case CParser::LeftParen: {
        enterOuterAlt(_localctx, 4);
        setState(226);
        match(CParser::LeftParen);
        setState(227);
        commaExpression(0);
        setState(228);
        match(CParser::RightParen);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantContext ------------------------------------------------------------------

CParser::ConstantContext::ConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::ConstantContext::IntegerConstant() {
  return getToken(CParser::IntegerConstant, 0);
}

tree::TerminalNode* CParser::ConstantContext::FloatingConstant() {
  return getToken(CParser::FloatingConstant, 0);
}

tree::TerminalNode* CParser::ConstantContext::CharacterConstant() {
  return getToken(CParser::CharacterConstant, 0);
}


size_t CParser::ConstantContext::getRuleIndex() const {
  return CParser::RuleConstant;
}


std::any CParser::ConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitConstant(this);
  else
    return visitor->visitChildren(this);
}

CParser::ConstantContext* CParser::constant() {
  ConstantContext *_localctx = _tracker.createInstance<ConstantContext>(_ctx, getState());
  enterRule(_localctx, 10, CParser::RuleConstant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(232);
    _la = _input->LA(1);
    if (!(((((_la - 93) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 93)) & 11) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringLiteralContext ------------------------------------------------------------------

CParser::StringLiteralContext::StringLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::StringLiteralContext::EncodingPrefix() {
  return getToken(CParser::EncodingPrefix, 0);
}

tree::TerminalNode* CParser::StringLiteralContext::SCharSequence() {
  return getToken(CParser::SCharSequence, 0);
}


size_t CParser::StringLiteralContext::getRuleIndex() const {
  return CParser::RuleStringLiteral;
}


std::any CParser::StringLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitStringLiteral(this);
  else
    return visitor->visitChildren(this);
}

CParser::StringLiteralContext* CParser::stringLiteral() {
  StringLiteralContext *_localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
  enterRule(_localctx, 12, CParser::RuleStringLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(235);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CParser::EncodingPrefix) {
      setState(234);
      match(CParser::EncodingPrefix);
    }
    setState(237);
    match(CParser::T__0);
    setState(239);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CParser::SCharSequence) {
      setState(238);
      match(CParser::SCharSequence);
    }
    setState(241);
    match(CParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentExpressionListContext ------------------------------------------------------------------

CParser::ArgumentExpressionListContext::ArgumentExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::ExpressionContext *> CParser::ArgumentExpressionListContext::expression() {
  return getRuleContexts<CParser::ExpressionContext>();
}

CParser::ExpressionContext* CParser::ArgumentExpressionListContext::expression(size_t i) {
  return getRuleContext<CParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CParser::ArgumentExpressionListContext::Comma() {
  return getTokens(CParser::Comma);
}

tree::TerminalNode* CParser::ArgumentExpressionListContext::Comma(size_t i) {
  return getToken(CParser::Comma, i);
}


size_t CParser::ArgumentExpressionListContext::getRuleIndex() const {
  return CParser::RuleArgumentExpressionList;
}


std::any CParser::ArgumentExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitArgumentExpressionList(this);
  else
    return visitor->visitChildren(this);
}

CParser::ArgumentExpressionListContext* CParser::argumentExpressionList() {
  ArgumentExpressionListContext *_localctx = _tracker.createInstance<ArgumentExpressionListContext>(_ctx, getState());
  enterRule(_localctx, 14, CParser::RuleArgumentExpressionList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(243);
    expression(0);
    setState(248);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CParser::Comma) {
      setState(244);
      match(CParser::Comma);
      setState(245);
      expression(0);
      setState(250);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CommaExpressionContext ------------------------------------------------------------------

CParser::CommaExpressionContext::CommaExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::ExpressionContext* CParser::CommaExpressionContext::expression() {
  return getRuleContext<CParser::ExpressionContext>(0);
}

CParser::CommaExpressionContext* CParser::CommaExpressionContext::commaExpression() {
  return getRuleContext<CParser::CommaExpressionContext>(0);
}

tree::TerminalNode* CParser::CommaExpressionContext::Comma() {
  return getToken(CParser::Comma, 0);
}


size_t CParser::CommaExpressionContext::getRuleIndex() const {
  return CParser::RuleCommaExpression;
}


std::any CParser::CommaExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitCommaExpression(this);
  else
    return visitor->visitChildren(this);
}


CParser::CommaExpressionContext* CParser::commaExpression() {
   return commaExpression(0);
}

CParser::CommaExpressionContext* CParser::commaExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CParser::CommaExpressionContext *_localctx = _tracker.createInstance<CommaExpressionContext>(_ctx, parentState);
  CParser::CommaExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, CParser::RuleCommaExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(252);
    expression(0);
    _ctx->stop = _input->LT(-1);
    setState(259);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<CommaExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleCommaExpression);
        setState(254);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(255);
        match(CParser::Comma);
        setState(256);
        expression(0); 
      }
      setState(261);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

CParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::DeclarationSpecifiersContext* CParser::DeclarationContext::declarationSpecifiers() {
  return getRuleContext<CParser::DeclarationSpecifiersContext>(0);
}

tree::TerminalNode* CParser::DeclarationContext::Semi() {
  return getToken(CParser::Semi, 0);
}

CParser::InitDeclaratorListContext* CParser::DeclarationContext::initDeclaratorList() {
  return getRuleContext<CParser::InitDeclaratorListContext>(0);
}

CParser::StaticAssertDeclarationContext* CParser::DeclarationContext::staticAssertDeclaration() {
  return getRuleContext<CParser::StaticAssertDeclarationContext>(0);
}


size_t CParser::DeclarationContext::getRuleIndex() const {
  return CParser::RuleDeclaration;
}


std::any CParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CParser::DeclarationContext* CParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 18, CParser::RuleDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(269);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CParser::Auto:
      case CParser::Char:
      case CParser::Const:
      case CParser::Double:
      case CParser::Enum:
      case CParser::Extern:
      case CParser::Float:
      case CParser::Inline:
      case CParser::Int:
      case CParser::Long:
      case CParser::Register:
      case CParser::Restrict:
      case CParser::Short:
      case CParser::Signed:
      case CParser::Static:
      case CParser::Struct:
      case CParser::Typedef:
      case CParser::Union:
      case CParser::Unsigned:
      case CParser::Void:
      case CParser::Volatile:
      case CParser::Alignas:
      case CParser::Atomic:
      case CParser::Bool:
      case CParser::Complex:
      case CParser::Noreturn:
      case CParser::ThreadLocal:
      case CParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(262);
        declarationSpecifiers();
        setState(264);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 46) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 46)) & 70368744243201) != 0)) {
          setState(263);
          initDeclaratorList();
        }
        setState(266);
        match(CParser::Semi);
        break;
      }

      case CParser::StaticAssert: {
        enterOuterAlt(_localctx, 2);
        setState(268);
        staticAssertDeclaration();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationSpecifiersContext ------------------------------------------------------------------

CParser::DeclarationSpecifiersContext::DeclarationSpecifiersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::StorageClassSpecifierContext *> CParser::DeclarationSpecifiersContext::storageClassSpecifier() {
  return getRuleContexts<CParser::StorageClassSpecifierContext>();
}

CParser::StorageClassSpecifierContext* CParser::DeclarationSpecifiersContext::storageClassSpecifier(size_t i) {
  return getRuleContext<CParser::StorageClassSpecifierContext>(i);
}

std::vector<CParser::TypeSpecifierContext *> CParser::DeclarationSpecifiersContext::typeSpecifier() {
  return getRuleContexts<CParser::TypeSpecifierContext>();
}

CParser::TypeSpecifierContext* CParser::DeclarationSpecifiersContext::typeSpecifier(size_t i) {
  return getRuleContext<CParser::TypeSpecifierContext>(i);
}

std::vector<CParser::TypeQualifierContext *> CParser::DeclarationSpecifiersContext::typeQualifier() {
  return getRuleContexts<CParser::TypeQualifierContext>();
}

CParser::TypeQualifierContext* CParser::DeclarationSpecifiersContext::typeQualifier(size_t i) {
  return getRuleContext<CParser::TypeQualifierContext>(i);
}

std::vector<CParser::FunctionSpecifierContext *> CParser::DeclarationSpecifiersContext::functionSpecifier() {
  return getRuleContexts<CParser::FunctionSpecifierContext>();
}

CParser::FunctionSpecifierContext* CParser::DeclarationSpecifiersContext::functionSpecifier(size_t i) {
  return getRuleContext<CParser::FunctionSpecifierContext>(i);
}

std::vector<CParser::AlignmentSpecifierContext *> CParser::DeclarationSpecifiersContext::alignmentSpecifier() {
  return getRuleContexts<CParser::AlignmentSpecifierContext>();
}

CParser::AlignmentSpecifierContext* CParser::DeclarationSpecifiersContext::alignmentSpecifier(size_t i) {
  return getRuleContext<CParser::AlignmentSpecifierContext>(i);
}


size_t CParser::DeclarationSpecifiersContext::getRuleIndex() const {
  return CParser::RuleDeclarationSpecifiers;
}


std::any CParser::DeclarationSpecifiersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitDeclarationSpecifiers(this);
  else
    return visitor->visitChildren(this);
}

CParser::DeclarationSpecifiersContext* CParser::declarationSpecifiers() {
  DeclarationSpecifiersContext *_localctx = _tracker.createInstance<DeclarationSpecifiersContext>(_ctx, getState());
  enterRule(_localctx, 20, CParser::RuleDeclarationSpecifiers);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(276); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(276);
              _errHandler->sync(this);
              switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
              case 1: {
                setState(271);
                storageClassSpecifier();
                break;
              }

              case 2: {
                setState(272);
                typeSpecifier();
                break;
              }

              case 3: {
                setState(273);
                typeQualifier();
                break;
              }

              case 4: {
                setState(274);
                functionSpecifier();
                break;
              }

              case 5: {
                setState(275);
                alignmentSpecifier();
                break;
              }

              default:
                break;
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(278); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitDeclaratorListContext ------------------------------------------------------------------

CParser::InitDeclaratorListContext::InitDeclaratorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::InitDeclaratorContext *> CParser::InitDeclaratorListContext::initDeclarator() {
  return getRuleContexts<CParser::InitDeclaratorContext>();
}

CParser::InitDeclaratorContext* CParser::InitDeclaratorListContext::initDeclarator(size_t i) {
  return getRuleContext<CParser::InitDeclaratorContext>(i);
}

std::vector<tree::TerminalNode *> CParser::InitDeclaratorListContext::Comma() {
  return getTokens(CParser::Comma);
}

tree::TerminalNode* CParser::InitDeclaratorListContext::Comma(size_t i) {
  return getToken(CParser::Comma, i);
}


size_t CParser::InitDeclaratorListContext::getRuleIndex() const {
  return CParser::RuleInitDeclaratorList;
}


std::any CParser::InitDeclaratorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitInitDeclaratorList(this);
  else
    return visitor->visitChildren(this);
}

CParser::InitDeclaratorListContext* CParser::initDeclaratorList() {
  InitDeclaratorListContext *_localctx = _tracker.createInstance<InitDeclaratorListContext>(_ctx, getState());
  enterRule(_localctx, 22, CParser::RuleInitDeclaratorList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(280);
    initDeclarator();
    setState(285);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CParser::Comma) {
      setState(281);
      match(CParser::Comma);
      setState(282);
      initDeclarator();
      setState(287);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitDeclaratorContext ------------------------------------------------------------------

CParser::InitDeclaratorContext::InitDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::DeclaratorContext* CParser::InitDeclaratorContext::declarator() {
  return getRuleContext<CParser::DeclaratorContext>(0);
}

tree::TerminalNode* CParser::InitDeclaratorContext::Assign() {
  return getToken(CParser::Assign, 0);
}

CParser::InitializerContext* CParser::InitDeclaratorContext::initializer() {
  return getRuleContext<CParser::InitializerContext>(0);
}


size_t CParser::InitDeclaratorContext::getRuleIndex() const {
  return CParser::RuleInitDeclarator;
}


std::any CParser::InitDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitInitDeclarator(this);
  else
    return visitor->visitChildren(this);
}

CParser::InitDeclaratorContext* CParser::initDeclarator() {
  InitDeclaratorContext *_localctx = _tracker.createInstance<InitDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 24, CParser::RuleInitDeclarator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(288);
    declarator();
    setState(291);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CParser::Assign) {
      setState(289);
      match(CParser::Assign);
      setState(290);
      initializer();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StorageClassSpecifierContext ------------------------------------------------------------------

CParser::StorageClassSpecifierContext::StorageClassSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::StorageClassSpecifierContext::Typedef() {
  return getToken(CParser::Typedef, 0);
}

tree::TerminalNode* CParser::StorageClassSpecifierContext::Extern() {
  return getToken(CParser::Extern, 0);
}

tree::TerminalNode* CParser::StorageClassSpecifierContext::Static() {
  return getToken(CParser::Static, 0);
}

tree::TerminalNode* CParser::StorageClassSpecifierContext::ThreadLocal() {
  return getToken(CParser::ThreadLocal, 0);
}

tree::TerminalNode* CParser::StorageClassSpecifierContext::Auto() {
  return getToken(CParser::Auto, 0);
}

tree::TerminalNode* CParser::StorageClassSpecifierContext::Register() {
  return getToken(CParser::Register, 0);
}


size_t CParser::StorageClassSpecifierContext::getRuleIndex() const {
  return CParser::RuleStorageClassSpecifier;
}


std::any CParser::StorageClassSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitStorageClassSpecifier(this);
  else
    return visitor->visitChildren(this);
}

CParser::StorageClassSpecifierContext* CParser::storageClassSpecifier() {
  StorageClassSpecifierContext *_localctx = _tracker.createInstance<StorageClassSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 26, CParser::RuleStorageClassSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(293);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 35185582153732) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSpecifierContext ------------------------------------------------------------------

CParser::TypeSpecifierContext::TypeSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::TypeSpecifierContext::Void() {
  return getToken(CParser::Void, 0);
}

tree::TerminalNode* CParser::TypeSpecifierContext::Char() {
  return getToken(CParser::Char, 0);
}

tree::TerminalNode* CParser::TypeSpecifierContext::Short() {
  return getToken(CParser::Short, 0);
}

tree::TerminalNode* CParser::TypeSpecifierContext::Int() {
  return getToken(CParser::Int, 0);
}

tree::TerminalNode* CParser::TypeSpecifierContext::Long() {
  return getToken(CParser::Long, 0);
}

tree::TerminalNode* CParser::TypeSpecifierContext::Float() {
  return getToken(CParser::Float, 0);
}

tree::TerminalNode* CParser::TypeSpecifierContext::Double() {
  return getToken(CParser::Double, 0);
}

tree::TerminalNode* CParser::TypeSpecifierContext::Signed() {
  return getToken(CParser::Signed, 0);
}

tree::TerminalNode* CParser::TypeSpecifierContext::Unsigned() {
  return getToken(CParser::Unsigned, 0);
}

tree::TerminalNode* CParser::TypeSpecifierContext::Bool() {
  return getToken(CParser::Bool, 0);
}

tree::TerminalNode* CParser::TypeSpecifierContext::Complex() {
  return getToken(CParser::Complex, 0);
}

CParser::AtomicTypeSpecifierContext* CParser::TypeSpecifierContext::atomicTypeSpecifier() {
  return getRuleContext<CParser::AtomicTypeSpecifierContext>(0);
}

CParser::StructOrUnionSpecifierContext* CParser::TypeSpecifierContext::structOrUnionSpecifier() {
  return getRuleContext<CParser::StructOrUnionSpecifierContext>(0);
}

CParser::EnumSpecifierContext* CParser::TypeSpecifierContext::enumSpecifier() {
  return getRuleContext<CParser::EnumSpecifierContext>(0);
}

CParser::TypedefNameContext* CParser::TypeSpecifierContext::typedefName() {
  return getRuleContext<CParser::TypedefNameContext>(0);
}


size_t CParser::TypeSpecifierContext::getRuleIndex() const {
  return CParser::RuleTypeSpecifier;
}


std::any CParser::TypeSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitTypeSpecifier(this);
  else
    return visitor->visitChildren(this);
}

CParser::TypeSpecifierContext* CParser::typeSpecifier() {
  TypeSpecifierContext *_localctx = _tracker.createInstance<TypeSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 28, CParser::RuleTypeSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(310);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CParser::Void: {
        enterOuterAlt(_localctx, 1);
        setState(295);
        match(CParser::Void);
        break;
      }

      case CParser::Char: {
        enterOuterAlt(_localctx, 2);
        setState(296);
        match(CParser::Char);
        break;
      }

      case CParser::Short: {
        enterOuterAlt(_localctx, 3);
        setState(297);
        match(CParser::Short);
        break;
      }

      case CParser::Int: {
        enterOuterAlt(_localctx, 4);
        setState(298);
        match(CParser::Int);
        break;
      }

      case CParser::Long: {
        enterOuterAlt(_localctx, 5);
        setState(299);
        match(CParser::Long);
        break;
      }

      case CParser::Float: {
        enterOuterAlt(_localctx, 6);
        setState(300);
        match(CParser::Float);
        break;
      }

      case CParser::Double: {
        enterOuterAlt(_localctx, 7);
        setState(301);
        match(CParser::Double);
        break;
      }

      case CParser::Signed: {
        enterOuterAlt(_localctx, 8);
        setState(302);
        match(CParser::Signed);
        break;
      }

      case CParser::Unsigned: {
        enterOuterAlt(_localctx, 9);
        setState(303);
        match(CParser::Unsigned);
        break;
      }

      case CParser::Bool: {
        enterOuterAlt(_localctx, 10);
        setState(304);
        match(CParser::Bool);
        break;
      }

      case CParser::Complex: {
        enterOuterAlt(_localctx, 11);
        setState(305);
        match(CParser::Complex);
        break;
      }

      case CParser::Atomic: {
        enterOuterAlt(_localctx, 12);
        setState(306);
        atomicTypeSpecifier();
        break;
      }

      case CParser::Struct:
      case CParser::Union: {
        enterOuterAlt(_localctx, 13);
        setState(307);
        structOrUnionSpecifier();
        break;
      }

      case CParser::Enum: {
        enterOuterAlt(_localctx, 14);
        setState(308);
        enumSpecifier();
        break;
      }

      case CParser::Identifier: {
        enterOuterAlt(_localctx, 15);
        setState(309);
        typedefName();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructOrUnionSpecifierContext ------------------------------------------------------------------

CParser::StructOrUnionSpecifierContext::StructOrUnionSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::StructOrUnionContext* CParser::StructOrUnionSpecifierContext::structOrUnion() {
  return getRuleContext<CParser::StructOrUnionContext>(0);
}

tree::TerminalNode* CParser::StructOrUnionSpecifierContext::LeftBrace() {
  return getToken(CParser::LeftBrace, 0);
}

CParser::StructDeclarationListContext* CParser::StructOrUnionSpecifierContext::structDeclarationList() {
  return getRuleContext<CParser::StructDeclarationListContext>(0);
}

tree::TerminalNode* CParser::StructOrUnionSpecifierContext::RightBrace() {
  return getToken(CParser::RightBrace, 0);
}

tree::TerminalNode* CParser::StructOrUnionSpecifierContext::Identifier() {
  return getToken(CParser::Identifier, 0);
}


size_t CParser::StructOrUnionSpecifierContext::getRuleIndex() const {
  return CParser::RuleStructOrUnionSpecifier;
}


std::any CParser::StructOrUnionSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitStructOrUnionSpecifier(this);
  else
    return visitor->visitChildren(this);
}

CParser::StructOrUnionSpecifierContext* CParser::structOrUnionSpecifier() {
  StructOrUnionSpecifierContext *_localctx = _tracker.createInstance<StructOrUnionSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 30, CParser::RuleStructOrUnionSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(323);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(312);
      structOrUnion();
      setState(314);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CParser::Identifier) {
        setState(313);
        match(CParser::Identifier);
      }
      setState(316);
      match(CParser::LeftBrace);
      setState(317);
      structDeclarationList();
      setState(318);
      match(CParser::RightBrace);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(320);
      structOrUnion();
      setState(321);
      match(CParser::Identifier);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructOrUnionContext ------------------------------------------------------------------

CParser::StructOrUnionContext::StructOrUnionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::StructOrUnionContext::Struct() {
  return getToken(CParser::Struct, 0);
}

tree::TerminalNode* CParser::StructOrUnionContext::Union() {
  return getToken(CParser::Union, 0);
}


size_t CParser::StructOrUnionContext::getRuleIndex() const {
  return CParser::RuleStructOrUnion;
}


std::any CParser::StructOrUnionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitStructOrUnion(this);
  else
    return visitor->visitChildren(this);
}

CParser::StructOrUnionContext* CParser::structOrUnion() {
  StructOrUnionContext *_localctx = _tracker.createInstance<StructOrUnionContext>(_ctx, getState());
  enterRule(_localctx, 32, CParser::RuleStructOrUnion);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(325);
    _la = _input->LA(1);
    if (!(_la == CParser::Struct

    || _la == CParser::Union)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDeclarationListContext ------------------------------------------------------------------

CParser::StructDeclarationListContext::StructDeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::StructDeclarationContext *> CParser::StructDeclarationListContext::structDeclaration() {
  return getRuleContexts<CParser::StructDeclarationContext>();
}

CParser::StructDeclarationContext* CParser::StructDeclarationListContext::structDeclaration(size_t i) {
  return getRuleContext<CParser::StructDeclarationContext>(i);
}


size_t CParser::StructDeclarationListContext::getRuleIndex() const {
  return CParser::RuleStructDeclarationList;
}


std::any CParser::StructDeclarationListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitStructDeclarationList(this);
  else
    return visitor->visitChildren(this);
}

CParser::StructDeclarationListContext* CParser::structDeclarationList() {
  StructDeclarationListContext *_localctx = _tracker.createInstance<StructDeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 34, CParser::RuleStructDeclarationList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(328); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(327);
      structDeclaration();
      setState(330); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 19548868203616) != 0) || _la == CParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDeclarationContext ------------------------------------------------------------------

CParser::StructDeclarationContext::StructDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::SpecifierQualifierListContext* CParser::StructDeclarationContext::specifierQualifierList() {
  return getRuleContext<CParser::SpecifierQualifierListContext>(0);
}

CParser::StructDeclaratorListContext* CParser::StructDeclarationContext::structDeclaratorList() {
  return getRuleContext<CParser::StructDeclaratorListContext>(0);
}

tree::TerminalNode* CParser::StructDeclarationContext::Semi() {
  return getToken(CParser::Semi, 0);
}

CParser::StaticAssertDeclarationContext* CParser::StructDeclarationContext::staticAssertDeclaration() {
  return getRuleContext<CParser::StaticAssertDeclarationContext>(0);
}


size_t CParser::StructDeclarationContext::getRuleIndex() const {
  return CParser::RuleStructDeclaration;
}


std::any CParser::StructDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitStructDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CParser::StructDeclarationContext* CParser::structDeclaration() {
  StructDeclarationContext *_localctx = _tracker.createInstance<StructDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 36, CParser::RuleStructDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(340);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(332);
      specifierQualifierList();
      setState(333);
      structDeclaratorList();
      setState(334);
      match(CParser::Semi);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(336);
      specifierQualifierList();
      setState(337);
      match(CParser::Semi);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(339);
      staticAssertDeclaration();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SpecifierQualifierListContext ------------------------------------------------------------------

CParser::SpecifierQualifierListContext::SpecifierQualifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::TypeSpecifierContext *> CParser::SpecifierQualifierListContext::typeSpecifier() {
  return getRuleContexts<CParser::TypeSpecifierContext>();
}

CParser::TypeSpecifierContext* CParser::SpecifierQualifierListContext::typeSpecifier(size_t i) {
  return getRuleContext<CParser::TypeSpecifierContext>(i);
}

std::vector<CParser::TypeQualifierContext *> CParser::SpecifierQualifierListContext::typeQualifier() {
  return getRuleContexts<CParser::TypeQualifierContext>();
}

CParser::TypeQualifierContext* CParser::SpecifierQualifierListContext::typeQualifier(size_t i) {
  return getRuleContext<CParser::TypeQualifierContext>(i);
}


size_t CParser::SpecifierQualifierListContext::getRuleIndex() const {
  return CParser::RuleSpecifierQualifierList;
}


std::any CParser::SpecifierQualifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitSpecifierQualifierList(this);
  else
    return visitor->visitChildren(this);
}

CParser::SpecifierQualifierListContext* CParser::specifierQualifierList() {
  SpecifierQualifierListContext *_localctx = _tracker.createInstance<SpecifierQualifierListContext>(_ctx, getState());
  enterRule(_localctx, 38, CParser::RuleSpecifierQualifierList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(344); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(344);
              _errHandler->sync(this);
              switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
              case 1: {
                setState(342);
                typeSpecifier();
                break;
              }

              case 2: {
                setState(343);
                typeQualifier();
                break;
              }

              default:
                break;
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(346); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDeclaratorListContext ------------------------------------------------------------------

CParser::StructDeclaratorListContext::StructDeclaratorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::StructDeclaratorContext *> CParser::StructDeclaratorListContext::structDeclarator() {
  return getRuleContexts<CParser::StructDeclaratorContext>();
}

CParser::StructDeclaratorContext* CParser::StructDeclaratorListContext::structDeclarator(size_t i) {
  return getRuleContext<CParser::StructDeclaratorContext>(i);
}

std::vector<tree::TerminalNode *> CParser::StructDeclaratorListContext::Comma() {
  return getTokens(CParser::Comma);
}

tree::TerminalNode* CParser::StructDeclaratorListContext::Comma(size_t i) {
  return getToken(CParser::Comma, i);
}


size_t CParser::StructDeclaratorListContext::getRuleIndex() const {
  return CParser::RuleStructDeclaratorList;
}


std::any CParser::StructDeclaratorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitStructDeclaratorList(this);
  else
    return visitor->visitChildren(this);
}

CParser::StructDeclaratorListContext* CParser::structDeclaratorList() {
  StructDeclaratorListContext *_localctx = _tracker.createInstance<StructDeclaratorListContext>(_ctx, getState());
  enterRule(_localctx, 40, CParser::RuleStructDeclaratorList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(348);
    structDeclarator();
    setState(353);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CParser::Comma) {
      setState(349);
      match(CParser::Comma);
      setState(350);
      structDeclarator();
      setState(355);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDeclaratorContext ------------------------------------------------------------------

CParser::StructDeclaratorContext::StructDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::DeclaratorContext* CParser::StructDeclaratorContext::declarator() {
  return getRuleContext<CParser::DeclaratorContext>(0);
}

tree::TerminalNode* CParser::StructDeclaratorContext::Colon() {
  return getToken(CParser::Colon, 0);
}

CParser::ConstantExpressionContext* CParser::StructDeclaratorContext::constantExpression() {
  return getRuleContext<CParser::ConstantExpressionContext>(0);
}


size_t CParser::StructDeclaratorContext::getRuleIndex() const {
  return CParser::RuleStructDeclarator;
}


std::any CParser::StructDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitStructDeclarator(this);
  else
    return visitor->visitChildren(this);
}

CParser::StructDeclaratorContext* CParser::structDeclarator() {
  StructDeclaratorContext *_localctx = _tracker.createInstance<StructDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 42, CParser::RuleStructDeclarator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(362);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(356);
      declarator();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(358);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 46) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 46)) & 70368744243201) != 0)) {
        setState(357);
        declarator();
      }
      setState(360);
      match(CParser::Colon);
      setState(361);
      constantExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumSpecifierContext ------------------------------------------------------------------

CParser::EnumSpecifierContext::EnumSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::EnumSpecifierContext::Enum() {
  return getToken(CParser::Enum, 0);
}

tree::TerminalNode* CParser::EnumSpecifierContext::LeftBrace() {
  return getToken(CParser::LeftBrace, 0);
}

CParser::EnumeratorListContext* CParser::EnumSpecifierContext::enumeratorList() {
  return getRuleContext<CParser::EnumeratorListContext>(0);
}

tree::TerminalNode* CParser::EnumSpecifierContext::RightBrace() {
  return getToken(CParser::RightBrace, 0);
}

tree::TerminalNode* CParser::EnumSpecifierContext::Identifier() {
  return getToken(CParser::Identifier, 0);
}

tree::TerminalNode* CParser::EnumSpecifierContext::Comma() {
  return getToken(CParser::Comma, 0);
}


size_t CParser::EnumSpecifierContext::getRuleIndex() const {
  return CParser::RuleEnumSpecifier;
}


std::any CParser::EnumSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitEnumSpecifier(this);
  else
    return visitor->visitChildren(this);
}

CParser::EnumSpecifierContext* CParser::enumSpecifier() {
  EnumSpecifierContext *_localctx = _tracker.createInstance<EnumSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 44, CParser::RuleEnumSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(377);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(364);
      match(CParser::Enum);
      setState(366);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CParser::Identifier) {
        setState(365);
        match(CParser::Identifier);
      }
      setState(368);
      match(CParser::LeftBrace);
      setState(369);
      enumeratorList();
      setState(371);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CParser::Comma) {
        setState(370);
        match(CParser::Comma);
      }
      setState(373);
      match(CParser::RightBrace);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(375);
      match(CParser::Enum);
      setState(376);
      match(CParser::Identifier);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumeratorListContext ------------------------------------------------------------------

CParser::EnumeratorListContext::EnumeratorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::EnumeratorContext *> CParser::EnumeratorListContext::enumerator() {
  return getRuleContexts<CParser::EnumeratorContext>();
}

CParser::EnumeratorContext* CParser::EnumeratorListContext::enumerator(size_t i) {
  return getRuleContext<CParser::EnumeratorContext>(i);
}

std::vector<tree::TerminalNode *> CParser::EnumeratorListContext::Comma() {
  return getTokens(CParser::Comma);
}

tree::TerminalNode* CParser::EnumeratorListContext::Comma(size_t i) {
  return getToken(CParser::Comma, i);
}


size_t CParser::EnumeratorListContext::getRuleIndex() const {
  return CParser::RuleEnumeratorList;
}


std::any CParser::EnumeratorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitEnumeratorList(this);
  else
    return visitor->visitChildren(this);
}

CParser::EnumeratorListContext* CParser::enumeratorList() {
  EnumeratorListContext *_localctx = _tracker.createInstance<EnumeratorListContext>(_ctx, getState());
  enterRule(_localctx, 46, CParser::RuleEnumeratorList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(379);
    enumerator();
    setState(384);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(380);
        match(CParser::Comma);
        setState(381);
        enumerator(); 
      }
      setState(386);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumeratorContext ------------------------------------------------------------------

CParser::EnumeratorContext::EnumeratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::EnumerationConstantContext* CParser::EnumeratorContext::enumerationConstant() {
  return getRuleContext<CParser::EnumerationConstantContext>(0);
}

tree::TerminalNode* CParser::EnumeratorContext::Assign() {
  return getToken(CParser::Assign, 0);
}

CParser::ConstantExpressionContext* CParser::EnumeratorContext::constantExpression() {
  return getRuleContext<CParser::ConstantExpressionContext>(0);
}


size_t CParser::EnumeratorContext::getRuleIndex() const {
  return CParser::RuleEnumerator;
}


std::any CParser::EnumeratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitEnumerator(this);
  else
    return visitor->visitChildren(this);
}

CParser::EnumeratorContext* CParser::enumerator() {
  EnumeratorContext *_localctx = _tracker.createInstance<EnumeratorContext>(_ctx, getState());
  enterRule(_localctx, 48, CParser::RuleEnumerator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(387);
    enumerationConstant();
    setState(390);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CParser::Assign) {
      setState(388);
      match(CParser::Assign);
      setState(389);
      constantExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumerationConstantContext ------------------------------------------------------------------

CParser::EnumerationConstantContext::EnumerationConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::EnumerationConstantContext::Identifier() {
  return getToken(CParser::Identifier, 0);
}


size_t CParser::EnumerationConstantContext::getRuleIndex() const {
  return CParser::RuleEnumerationConstant;
}


std::any CParser::EnumerationConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitEnumerationConstant(this);
  else
    return visitor->visitChildren(this);
}

CParser::EnumerationConstantContext* CParser::enumerationConstant() {
  EnumerationConstantContext *_localctx = _tracker.createInstance<EnumerationConstantContext>(_ctx, getState());
  enterRule(_localctx, 50, CParser::RuleEnumerationConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(392);
    match(CParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomicTypeSpecifierContext ------------------------------------------------------------------

CParser::AtomicTypeSpecifierContext::AtomicTypeSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::AtomicTypeSpecifierContext::Atomic() {
  return getToken(CParser::Atomic, 0);
}

tree::TerminalNode* CParser::AtomicTypeSpecifierContext::LeftParen() {
  return getToken(CParser::LeftParen, 0);
}

CParser::TypeNameContext* CParser::AtomicTypeSpecifierContext::typeName() {
  return getRuleContext<CParser::TypeNameContext>(0);
}

tree::TerminalNode* CParser::AtomicTypeSpecifierContext::RightParen() {
  return getToken(CParser::RightParen, 0);
}


size_t CParser::AtomicTypeSpecifierContext::getRuleIndex() const {
  return CParser::RuleAtomicTypeSpecifier;
}


std::any CParser::AtomicTypeSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitAtomicTypeSpecifier(this);
  else
    return visitor->visitChildren(this);
}

CParser::AtomicTypeSpecifierContext* CParser::atomicTypeSpecifier() {
  AtomicTypeSpecifierContext *_localctx = _tracker.createInstance<AtomicTypeSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 52, CParser::RuleAtomicTypeSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(394);
    match(CParser::Atomic);
    setState(395);
    match(CParser::LeftParen);
    setState(396);
    typeName();
    setState(397);
    match(CParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeQualifierContext ------------------------------------------------------------------

CParser::TypeQualifierContext::TypeQualifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::TypeQualifierContext::Const() {
  return getToken(CParser::Const, 0);
}

tree::TerminalNode* CParser::TypeQualifierContext::Restrict() {
  return getToken(CParser::Restrict, 0);
}

tree::TerminalNode* CParser::TypeQualifierContext::Volatile() {
  return getToken(CParser::Volatile, 0);
}

tree::TerminalNode* CParser::TypeQualifierContext::Atomic() {
  return getToken(CParser::Atomic, 0);
}


size_t CParser::TypeQualifierContext::getRuleIndex() const {
  return CParser::RuleTypeQualifier;
}


std::any CParser::TypeQualifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitTypeQualifier(this);
  else
    return visitor->visitChildren(this);
}

CParser::TypeQualifierContext* CParser::typeQualifier() {
  TypeQualifierContext *_localctx = _tracker.createInstance<TypeQualifierContext>(_ctx, getState());
  enterRule(_localctx, 54, CParser::RuleTypeQualifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(399);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 292061970496) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionSpecifierContext ------------------------------------------------------------------

CParser::FunctionSpecifierContext::FunctionSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::FunctionSpecifierContext::Inline() {
  return getToken(CParser::Inline, 0);
}

tree::TerminalNode* CParser::FunctionSpecifierContext::Noreturn() {
  return getToken(CParser::Noreturn, 0);
}


size_t CParser::FunctionSpecifierContext::getRuleIndex() const {
  return CParser::RuleFunctionSpecifier;
}


std::any CParser::FunctionSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitFunctionSpecifier(this);
  else
    return visitor->visitChildren(this);
}

CParser::FunctionSpecifierContext* CParser::functionSpecifier() {
  FunctionSpecifierContext *_localctx = _tracker.createInstance<FunctionSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 56, CParser::RuleFunctionSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(401);
    _la = _input->LA(1);
    if (!(_la == CParser::Inline

    || _la == CParser::Noreturn)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AlignmentSpecifierContext ------------------------------------------------------------------

CParser::AlignmentSpecifierContext::AlignmentSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::AlignmentSpecifierContext::Alignas() {
  return getToken(CParser::Alignas, 0);
}

tree::TerminalNode* CParser::AlignmentSpecifierContext::LeftParen() {
  return getToken(CParser::LeftParen, 0);
}

tree::TerminalNode* CParser::AlignmentSpecifierContext::RightParen() {
  return getToken(CParser::RightParen, 0);
}

CParser::TypeNameContext* CParser::AlignmentSpecifierContext::typeName() {
  return getRuleContext<CParser::TypeNameContext>(0);
}

CParser::ConstantExpressionContext* CParser::AlignmentSpecifierContext::constantExpression() {
  return getRuleContext<CParser::ConstantExpressionContext>(0);
}


size_t CParser::AlignmentSpecifierContext::getRuleIndex() const {
  return CParser::RuleAlignmentSpecifier;
}


std::any CParser::AlignmentSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitAlignmentSpecifier(this);
  else
    return visitor->visitChildren(this);
}

CParser::AlignmentSpecifierContext* CParser::alignmentSpecifier() {
  AlignmentSpecifierContext *_localctx = _tracker.createInstance<AlignmentSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 58, CParser::RuleAlignmentSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(403);
    match(CParser::Alignas);
    setState(404);
    match(CParser::LeftParen);
    setState(407);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      setState(405);
      typeName();
      break;
    }

    case 2: {
      setState(406);
      constantExpression();
      break;
    }

    default:
      break;
    }
    setState(409);
    match(CParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclaratorContext ------------------------------------------------------------------

CParser::DeclaratorContext::DeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::DirectDeclaratorContext* CParser::DeclaratorContext::directDeclarator() {
  return getRuleContext<CParser::DirectDeclaratorContext>(0);
}

CParser::PointerContext* CParser::DeclaratorContext::pointer() {
  return getRuleContext<CParser::PointerContext>(0);
}


size_t CParser::DeclaratorContext::getRuleIndex() const {
  return CParser::RuleDeclarator;
}


std::any CParser::DeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitDeclarator(this);
  else
    return visitor->visitChildren(this);
}

CParser::DeclaratorContext* CParser::declarator() {
  DeclaratorContext *_localctx = _tracker.createInstance<DeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 60, CParser::RuleDeclarator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(412);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CParser::Star) {
      setState(411);
      pointer();
    }
    setState(414);
    directDeclarator(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DirectDeclaratorContext ------------------------------------------------------------------

CParser::DirectDeclaratorContext::DirectDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::DirectDeclaratorContext::Identifier() {
  return getToken(CParser::Identifier, 0);
}

tree::TerminalNode* CParser::DirectDeclaratorContext::LeftParen() {
  return getToken(CParser::LeftParen, 0);
}

CParser::DeclaratorContext* CParser::DirectDeclaratorContext::declarator() {
  return getRuleContext<CParser::DeclaratorContext>(0);
}

tree::TerminalNode* CParser::DirectDeclaratorContext::RightParen() {
  return getToken(CParser::RightParen, 0);
}

tree::TerminalNode* CParser::DirectDeclaratorContext::Colon() {
  return getToken(CParser::Colon, 0);
}

tree::TerminalNode* CParser::DirectDeclaratorContext::DigitSequence() {
  return getToken(CParser::DigitSequence, 0);
}

CParser::DirectDeclaratorContext* CParser::DirectDeclaratorContext::directDeclarator() {
  return getRuleContext<CParser::DirectDeclaratorContext>(0);
}

tree::TerminalNode* CParser::DirectDeclaratorContext::LeftBracket() {
  return getToken(CParser::LeftBracket, 0);
}

tree::TerminalNode* CParser::DirectDeclaratorContext::RightBracket() {
  return getToken(CParser::RightBracket, 0);
}

CParser::TypeQualifierListContext* CParser::DirectDeclaratorContext::typeQualifierList() {
  return getRuleContext<CParser::TypeQualifierListContext>(0);
}

CParser::ExpressionContext* CParser::DirectDeclaratorContext::expression() {
  return getRuleContext<CParser::ExpressionContext>(0);
}

tree::TerminalNode* CParser::DirectDeclaratorContext::Static() {
  return getToken(CParser::Static, 0);
}

tree::TerminalNode* CParser::DirectDeclaratorContext::Star() {
  return getToken(CParser::Star, 0);
}

CParser::ParameterTypeListContext* CParser::DirectDeclaratorContext::parameterTypeList() {
  return getRuleContext<CParser::ParameterTypeListContext>(0);
}

CParser::IdentifierListContext* CParser::DirectDeclaratorContext::identifierList() {
  return getRuleContext<CParser::IdentifierListContext>(0);
}


size_t CParser::DirectDeclaratorContext::getRuleIndex() const {
  return CParser::RuleDirectDeclarator;
}


std::any CParser::DirectDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitDirectDeclarator(this);
  else
    return visitor->visitChildren(this);
}


CParser::DirectDeclaratorContext* CParser::directDeclarator() {
   return directDeclarator(0);
}

CParser::DirectDeclaratorContext* CParser::directDeclarator(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CParser::DirectDeclaratorContext *_localctx = _tracker.createInstance<DirectDeclaratorContext>(_ctx, parentState);
  CParser::DirectDeclaratorContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, CParser::RuleDirectDeclarator, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(425);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      setState(417);
      match(CParser::Identifier);
      break;
    }

    case 2: {
      setState(418);
      match(CParser::LeftParen);
      setState(419);
      declarator();
      setState(420);
      match(CParser::RightParen);
      break;
    }

    case 3: {
      setState(422);
      match(CParser::Identifier);
      setState(423);
      match(CParser::Colon);
      setState(424);
      match(CParser::DigitSequence);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(472);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(470);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(427);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(428);
          match(CParser::LeftBracket);
          setState(430);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 292061970496) != 0)) {
            setState(429);
            typeQualifierList();
          }
          setState(433);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 8935212166953304066) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 65)) & 7381975137) != 0)) {
            setState(432);
            expression(0);
          }
          setState(435);
          match(CParser::RightBracket);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(436);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(437);
          match(CParser::LeftBracket);
          setState(438);
          match(CParser::Static);
          setState(440);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 292061970496) != 0)) {
            setState(439);
            typeQualifierList();
          }
          setState(442);
          expression(0);
          setState(443);
          match(CParser::RightBracket);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(445);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(446);
          match(CParser::LeftBracket);
          setState(447);
          typeQualifierList();
          setState(448);
          match(CParser::Static);
          setState(449);
          expression(0);
          setState(450);
          match(CParser::RightBracket);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(452);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(453);
          match(CParser::LeftBracket);
          setState(455);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 292061970496) != 0)) {
            setState(454);
            typeQualifierList();
          }
          setState(457);
          match(CParser::Star);
          setState(458);
          match(CParser::RightBracket);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(459);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(460);
          match(CParser::LeftParen);
          setState(461);
          parameterTypeList();
          setState(462);
          match(CParser::RightParen);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(464);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(465);
          match(CParser::LeftParen);
          setState(467);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CParser::Identifier) {
            setState(466);
            identifierList();
          }
          setState(469);
          match(CParser::RightParen);
          break;
        }

        default:
          break;
        } 
      }
      setState(474);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PointerContext ------------------------------------------------------------------

CParser::PointerContext::PointerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::PointerContext::Star() {
  return getToken(CParser::Star, 0);
}

CParser::TypeQualifierListContext* CParser::PointerContext::typeQualifierList() {
  return getRuleContext<CParser::TypeQualifierListContext>(0);
}

CParser::PointerContext* CParser::PointerContext::pointer() {
  return getRuleContext<CParser::PointerContext>(0);
}


size_t CParser::PointerContext::getRuleIndex() const {
  return CParser::RulePointer;
}


std::any CParser::PointerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitPointer(this);
  else
    return visitor->visitChildren(this);
}

CParser::PointerContext* CParser::pointer() {
  PointerContext *_localctx = _tracker.createInstance<PointerContext>(_ctx, getState());
  enterRule(_localctx, 64, CParser::RulePointer);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(475);
    match(CParser::Star);
    setState(477);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 292061970496) != 0)) {
      setState(476);
      typeQualifierList();
    }
    setState(480);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CParser::Star) {
      setState(479);
      pointer();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeQualifierListContext ------------------------------------------------------------------

CParser::TypeQualifierListContext::TypeQualifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::TypeQualifierContext *> CParser::TypeQualifierListContext::typeQualifier() {
  return getRuleContexts<CParser::TypeQualifierContext>();
}

CParser::TypeQualifierContext* CParser::TypeQualifierListContext::typeQualifier(size_t i) {
  return getRuleContext<CParser::TypeQualifierContext>(i);
}


size_t CParser::TypeQualifierListContext::getRuleIndex() const {
  return CParser::RuleTypeQualifierList;
}


std::any CParser::TypeQualifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitTypeQualifierList(this);
  else
    return visitor->visitChildren(this);
}

CParser::TypeQualifierListContext* CParser::typeQualifierList() {
  TypeQualifierListContext *_localctx = _tracker.createInstance<TypeQualifierListContext>(_ctx, getState());
  enterRule(_localctx, 66, CParser::RuleTypeQualifierList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(483); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(482);
      typeQualifier();
      setState(485); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 292061970496) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterTypeListContext ------------------------------------------------------------------

CParser::ParameterTypeListContext::ParameterTypeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::ParameterListContext* CParser::ParameterTypeListContext::parameterList() {
  return getRuleContext<CParser::ParameterListContext>(0);
}

tree::TerminalNode* CParser::ParameterTypeListContext::Comma() {
  return getToken(CParser::Comma, 0);
}

tree::TerminalNode* CParser::ParameterTypeListContext::Ellipsis() {
  return getToken(CParser::Ellipsis, 0);
}


size_t CParser::ParameterTypeListContext::getRuleIndex() const {
  return CParser::RuleParameterTypeList;
}


std::any CParser::ParameterTypeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitParameterTypeList(this);
  else
    return visitor->visitChildren(this);
}

CParser::ParameterTypeListContext* CParser::parameterTypeList() {
  ParameterTypeListContext *_localctx = _tracker.createInstance<ParameterTypeListContext>(_ctx, getState());
  enterRule(_localctx, 68, CParser::RuleParameterTypeList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(487);
    parameterList();
    setState(490);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CParser::Comma) {
      setState(488);
      match(CParser::Comma);
      setState(489);
      match(CParser::Ellipsis);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterListContext ------------------------------------------------------------------

CParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::ParameterDeclarationContext *> CParser::ParameterListContext::parameterDeclaration() {
  return getRuleContexts<CParser::ParameterDeclarationContext>();
}

CParser::ParameterDeclarationContext* CParser::ParameterListContext::parameterDeclaration(size_t i) {
  return getRuleContext<CParser::ParameterDeclarationContext>(i);
}

std::vector<tree::TerminalNode *> CParser::ParameterListContext::Comma() {
  return getTokens(CParser::Comma);
}

tree::TerminalNode* CParser::ParameterListContext::Comma(size_t i) {
  return getToken(CParser::Comma, i);
}


size_t CParser::ParameterListContext::getRuleIndex() const {
  return CParser::RuleParameterList;
}


std::any CParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

CParser::ParameterListContext* CParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 70, CParser::RuleParameterList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(492);
    parameterDeclaration();
    setState(497);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(493);
        match(CParser::Comma);
        setState(494);
        parameterDeclaration(); 
      }
      setState(499);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterDeclarationContext ------------------------------------------------------------------

CParser::ParameterDeclarationContext::ParameterDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::DeclarationSpecifiersContext* CParser::ParameterDeclarationContext::declarationSpecifiers() {
  return getRuleContext<CParser::DeclarationSpecifiersContext>(0);
}

CParser::DeclaratorContext* CParser::ParameterDeclarationContext::declarator() {
  return getRuleContext<CParser::DeclaratorContext>(0);
}

CParser::AbstractDeclaratorContext* CParser::ParameterDeclarationContext::abstractDeclarator() {
  return getRuleContext<CParser::AbstractDeclaratorContext>(0);
}


size_t CParser::ParameterDeclarationContext::getRuleIndex() const {
  return CParser::RuleParameterDeclaration;
}


std::any CParser::ParameterDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitParameterDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CParser::ParameterDeclarationContext* CParser::parameterDeclaration() {
  ParameterDeclarationContext *_localctx = _tracker.createInstance<ParameterDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 72, CParser::RuleParameterDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(500);
    declarationSpecifiers();
    setState(505);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
    case 1: {
      setState(501);
      declarator();
      break;
    }

    case 2: {
      setState(503);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4612037862148276224) != 0)) {
        setState(502);
        abstractDeclarator();
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierListContext ------------------------------------------------------------------

CParser::IdentifierListContext::IdentifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CParser::IdentifierListContext::Identifier() {
  return getTokens(CParser::Identifier);
}

tree::TerminalNode* CParser::IdentifierListContext::Identifier(size_t i) {
  return getToken(CParser::Identifier, i);
}

std::vector<tree::TerminalNode *> CParser::IdentifierListContext::Comma() {
  return getTokens(CParser::Comma);
}

tree::TerminalNode* CParser::IdentifierListContext::Comma(size_t i) {
  return getToken(CParser::Comma, i);
}


size_t CParser::IdentifierListContext::getRuleIndex() const {
  return CParser::RuleIdentifierList;
}


std::any CParser::IdentifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitIdentifierList(this);
  else
    return visitor->visitChildren(this);
}

CParser::IdentifierListContext* CParser::identifierList() {
  IdentifierListContext *_localctx = _tracker.createInstance<IdentifierListContext>(_ctx, getState());
  enterRule(_localctx, 74, CParser::RuleIdentifierList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(507);
    match(CParser::Identifier);
    setState(512);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CParser::Comma) {
      setState(508);
      match(CParser::Comma);
      setState(509);
      match(CParser::Identifier);
      setState(514);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeNameContext ------------------------------------------------------------------

CParser::TypeNameContext::TypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::SpecifierQualifierListContext* CParser::TypeNameContext::specifierQualifierList() {
  return getRuleContext<CParser::SpecifierQualifierListContext>(0);
}

CParser::AbstractDeclaratorContext* CParser::TypeNameContext::abstractDeclarator() {
  return getRuleContext<CParser::AbstractDeclaratorContext>(0);
}


size_t CParser::TypeNameContext::getRuleIndex() const {
  return CParser::RuleTypeName;
}


std::any CParser::TypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitTypeName(this);
  else
    return visitor->visitChildren(this);
}

CParser::TypeNameContext* CParser::typeName() {
  TypeNameContext *_localctx = _tracker.createInstance<TypeNameContext>(_ctx, getState());
  enterRule(_localctx, 76, CParser::RuleTypeName);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(515);
    specifierQualifierList();
    setState(517);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4612037862148276224) != 0)) {
      setState(516);
      abstractDeclarator();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AbstractDeclaratorContext ------------------------------------------------------------------

CParser::AbstractDeclaratorContext::AbstractDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::PointerContext* CParser::AbstractDeclaratorContext::pointer() {
  return getRuleContext<CParser::PointerContext>(0);
}

CParser::DirectAbstractDeclaratorContext* CParser::AbstractDeclaratorContext::directAbstractDeclarator() {
  return getRuleContext<CParser::DirectAbstractDeclaratorContext>(0);
}


size_t CParser::AbstractDeclaratorContext::getRuleIndex() const {
  return CParser::RuleAbstractDeclarator;
}


std::any CParser::AbstractDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitAbstractDeclarator(this);
  else
    return visitor->visitChildren(this);
}

CParser::AbstractDeclaratorContext* CParser::abstractDeclarator() {
  AbstractDeclaratorContext *_localctx = _tracker.createInstance<AbstractDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 78, CParser::RuleAbstractDeclarator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(524);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(519);
      pointer();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(521);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CParser::Star) {
        setState(520);
        pointer();
      }
      setState(523);
      directAbstractDeclarator(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DirectAbstractDeclaratorContext ------------------------------------------------------------------

CParser::DirectAbstractDeclaratorContext::DirectAbstractDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::DirectAbstractDeclaratorContext::LeftParen() {
  return getToken(CParser::LeftParen, 0);
}

CParser::AbstractDeclaratorContext* CParser::DirectAbstractDeclaratorContext::abstractDeclarator() {
  return getRuleContext<CParser::AbstractDeclaratorContext>(0);
}

tree::TerminalNode* CParser::DirectAbstractDeclaratorContext::RightParen() {
  return getToken(CParser::RightParen, 0);
}

tree::TerminalNode* CParser::DirectAbstractDeclaratorContext::LeftBracket() {
  return getToken(CParser::LeftBracket, 0);
}

tree::TerminalNode* CParser::DirectAbstractDeclaratorContext::RightBracket() {
  return getToken(CParser::RightBracket, 0);
}

CParser::TypeQualifierListContext* CParser::DirectAbstractDeclaratorContext::typeQualifierList() {
  return getRuleContext<CParser::TypeQualifierListContext>(0);
}

CParser::ExpressionContext* CParser::DirectAbstractDeclaratorContext::expression() {
  return getRuleContext<CParser::ExpressionContext>(0);
}

tree::TerminalNode* CParser::DirectAbstractDeclaratorContext::Static() {
  return getToken(CParser::Static, 0);
}

tree::TerminalNode* CParser::DirectAbstractDeclaratorContext::Star() {
  return getToken(CParser::Star, 0);
}

CParser::ParameterTypeListContext* CParser::DirectAbstractDeclaratorContext::parameterTypeList() {
  return getRuleContext<CParser::ParameterTypeListContext>(0);
}

CParser::DirectAbstractDeclaratorContext* CParser::DirectAbstractDeclaratorContext::directAbstractDeclarator() {
  return getRuleContext<CParser::DirectAbstractDeclaratorContext>(0);
}


size_t CParser::DirectAbstractDeclaratorContext::getRuleIndex() const {
  return CParser::RuleDirectAbstractDeclarator;
}


std::any CParser::DirectAbstractDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitDirectAbstractDeclarator(this);
  else
    return visitor->visitChildren(this);
}


CParser::DirectAbstractDeclaratorContext* CParser::directAbstractDeclarator() {
   return directAbstractDeclarator(0);
}

CParser::DirectAbstractDeclaratorContext* CParser::directAbstractDeclarator(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CParser::DirectAbstractDeclaratorContext *_localctx = _tracker.createInstance<DirectAbstractDeclaratorContext>(_ctx, parentState);
  CParser::DirectAbstractDeclaratorContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 80;
  enterRecursionRule(_localctx, 80, CParser::RuleDirectAbstractDeclarator, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(561);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
    case 1: {
      setState(527);
      match(CParser::LeftParen);
      setState(528);
      abstractDeclarator();
      setState(529);
      match(CParser::RightParen);
      break;
    }

    case 2: {
      setState(531);
      match(CParser::LeftBracket);
      setState(533);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 292061970496) != 0)) {
        setState(532);
        typeQualifierList();
      }
      setState(536);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 8935212166953304066) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 65)) & 7381975137) != 0)) {
        setState(535);
        expression(0);
      }
      setState(538);
      match(CParser::RightBracket);
      break;
    }

    case 3: {
      setState(539);
      match(CParser::LeftBracket);
      setState(540);
      match(CParser::Static);
      setState(542);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 292061970496) != 0)) {
        setState(541);
        typeQualifierList();
      }
      setState(544);
      expression(0);
      setState(545);
      match(CParser::RightBracket);
      break;
    }

    case 4: {
      setState(547);
      match(CParser::LeftBracket);
      setState(548);
      typeQualifierList();
      setState(549);
      match(CParser::Static);
      setState(550);
      expression(0);
      setState(551);
      match(CParser::RightBracket);
      break;
    }

    case 5: {
      setState(553);
      match(CParser::LeftBracket);
      setState(554);
      match(CParser::Star);
      setState(555);
      match(CParser::RightBracket);
      break;
    }

    case 6: {
      setState(556);
      match(CParser::LeftParen);
      setState(558);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 46007077074020) != 0) || _la == CParser::Identifier) {
        setState(557);
        parameterTypeList();
      }
      setState(560);
      match(CParser::RightParen);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(600);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(598);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<DirectAbstractDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectAbstractDeclarator);
          setState(563);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(564);
          match(CParser::LeftBracket);
          setState(566);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 292061970496) != 0)) {
            setState(565);
            typeQualifierList();
          }
          setState(569);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 8935212166953304066) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 65)) & 7381975137) != 0)) {
            setState(568);
            expression(0);
          }
          setState(571);
          match(CParser::RightBracket);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<DirectAbstractDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectAbstractDeclarator);
          setState(572);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(573);
          match(CParser::LeftBracket);
          setState(574);
          match(CParser::Static);
          setState(576);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 292061970496) != 0)) {
            setState(575);
            typeQualifierList();
          }
          setState(578);
          expression(0);
          setState(579);
          match(CParser::RightBracket);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<DirectAbstractDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectAbstractDeclarator);
          setState(581);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(582);
          match(CParser::LeftBracket);
          setState(583);
          typeQualifierList();
          setState(584);
          match(CParser::Static);
          setState(585);
          expression(0);
          setState(586);
          match(CParser::RightBracket);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<DirectAbstractDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectAbstractDeclarator);
          setState(588);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(589);
          match(CParser::LeftBracket);
          setState(590);
          match(CParser::Star);
          setState(591);
          match(CParser::RightBracket);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<DirectAbstractDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectAbstractDeclarator);
          setState(592);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(593);
          match(CParser::LeftParen);
          setState(595);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 46007077074020) != 0) || _la == CParser::Identifier) {
            setState(594);
            parameterTypeList();
          }
          setState(597);
          match(CParser::RightParen);
          break;
        }

        default:
          break;
        } 
      }
      setState(602);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TypedefNameContext ------------------------------------------------------------------

CParser::TypedefNameContext::TypedefNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::TypedefNameContext::Identifier() {
  return getToken(CParser::Identifier, 0);
}


size_t CParser::TypedefNameContext::getRuleIndex() const {
  return CParser::RuleTypedefName;
}


std::any CParser::TypedefNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitTypedefName(this);
  else
    return visitor->visitChildren(this);
}

CParser::TypedefNameContext* CParser::typedefName() {
  TypedefNameContext *_localctx = _tracker.createInstance<TypedefNameContext>(_ctx, getState());
  enterRule(_localctx, 82, CParser::RuleTypedefName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(603);
    match(CParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitializerContext ------------------------------------------------------------------

CParser::InitializerContext::InitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::ExpressionContext* CParser::InitializerContext::expression() {
  return getRuleContext<CParser::ExpressionContext>(0);
}

tree::TerminalNode* CParser::InitializerContext::LeftBrace() {
  return getToken(CParser::LeftBrace, 0);
}

CParser::InitializerListContext* CParser::InitializerContext::initializerList() {
  return getRuleContext<CParser::InitializerListContext>(0);
}

tree::TerminalNode* CParser::InitializerContext::RightBrace() {
  return getToken(CParser::RightBrace, 0);
}

tree::TerminalNode* CParser::InitializerContext::Comma() {
  return getToken(CParser::Comma, 0);
}


size_t CParser::InitializerContext::getRuleIndex() const {
  return CParser::RuleInitializer;
}


std::any CParser::InitializerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitInitializer(this);
  else
    return visitor->visitChildren(this);
}

CParser::InitializerContext* CParser::initializer() {
  InitializerContext *_localctx = _tracker.createInstance<InitializerContext>(_ctx, getState());
  enterRule(_localctx, 84, CParser::RuleInitializer);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(613);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CParser::T__0:
      case CParser::Sizeof:
      case CParser::Alignof:
      case CParser::LeftParen:
      case CParser::Plus:
      case CParser::PlusPlus:
      case CParser::Minus:
      case CParser::MinusMinus:
      case CParser::Star:
      case CParser::And:
      case CParser::Not:
      case CParser::Tilde:
      case CParser::Identifier:
      case CParser::IntegerConstant:
      case CParser::FloatingConstant:
      case CParser::CharacterConstant:
      case CParser::EncodingPrefix: {
        enterOuterAlt(_localctx, 1);
        setState(605);
        expression(0);
        break;
      }

      case CParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(606);
        match(CParser::LeftBrace);
        setState(607);
        initializerList();
        setState(609);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CParser::Comma) {
          setState(608);
          match(CParser::Comma);
        }
        setState(611);
        match(CParser::RightBrace);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitializerListContext ------------------------------------------------------------------

CParser::InitializerListContext::InitializerListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::InitializerContext *> CParser::InitializerListContext::initializer() {
  return getRuleContexts<CParser::InitializerContext>();
}

CParser::InitializerContext* CParser::InitializerListContext::initializer(size_t i) {
  return getRuleContext<CParser::InitializerContext>(i);
}

std::vector<CParser::DesignationContext *> CParser::InitializerListContext::designation() {
  return getRuleContexts<CParser::DesignationContext>();
}

CParser::DesignationContext* CParser::InitializerListContext::designation(size_t i) {
  return getRuleContext<CParser::DesignationContext>(i);
}


size_t CParser::InitializerListContext::getRuleIndex() const {
  return CParser::RuleInitializerList;
}


std::any CParser::InitializerListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitInitializerList(this);
  else
    return visitor->visitChildren(this);
}

CParser::InitializerListContext* CParser::initializerList() {
  InitializerListContext *_localctx = _tracker.createInstance<InitializerListContext>(_ctx, getState());
  enterRule(_localctx, 86, CParser::RuleInitializerList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(619); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(616);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CParser::LeftBracket

      || _la == CParser::Dot) {
        setState(615);
        designation();
      }
      setState(618);
      initializer();
      setState(621); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8936619541836857346) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 7415529569) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DesignationContext ------------------------------------------------------------------

CParser::DesignationContext::DesignationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::DesignatorListContext* CParser::DesignationContext::designatorList() {
  return getRuleContext<CParser::DesignatorListContext>(0);
}

tree::TerminalNode* CParser::DesignationContext::Assign() {
  return getToken(CParser::Assign, 0);
}


size_t CParser::DesignationContext::getRuleIndex() const {
  return CParser::RuleDesignation;
}


std::any CParser::DesignationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitDesignation(this);
  else
    return visitor->visitChildren(this);
}

CParser::DesignationContext* CParser::designation() {
  DesignationContext *_localctx = _tracker.createInstance<DesignationContext>(_ctx, getState());
  enterRule(_localctx, 88, CParser::RuleDesignation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(623);
    designatorList();
    setState(624);
    match(CParser::Assign);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DesignatorListContext ------------------------------------------------------------------

CParser::DesignatorListContext::DesignatorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::DesignatorContext *> CParser::DesignatorListContext::designator() {
  return getRuleContexts<CParser::DesignatorContext>();
}

CParser::DesignatorContext* CParser::DesignatorListContext::designator(size_t i) {
  return getRuleContext<CParser::DesignatorContext>(i);
}


size_t CParser::DesignatorListContext::getRuleIndex() const {
  return CParser::RuleDesignatorList;
}


std::any CParser::DesignatorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitDesignatorList(this);
  else
    return visitor->visitChildren(this);
}

CParser::DesignatorListContext* CParser::designatorList() {
  DesignatorListContext *_localctx = _tracker.createInstance<DesignatorListContext>(_ctx, getState());
  enterRule(_localctx, 90, CParser::RuleDesignatorList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(627); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(626);
      designator();
      setState(629); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CParser::LeftBracket

    || _la == CParser::Dot);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DesignatorContext ------------------------------------------------------------------

CParser::DesignatorContext::DesignatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::DesignatorContext::LeftBracket() {
  return getToken(CParser::LeftBracket, 0);
}

CParser::ConstantExpressionContext* CParser::DesignatorContext::constantExpression() {
  return getRuleContext<CParser::ConstantExpressionContext>(0);
}

tree::TerminalNode* CParser::DesignatorContext::RightBracket() {
  return getToken(CParser::RightBracket, 0);
}

tree::TerminalNode* CParser::DesignatorContext::Dot() {
  return getToken(CParser::Dot, 0);
}

tree::TerminalNode* CParser::DesignatorContext::Identifier() {
  return getToken(CParser::Identifier, 0);
}


size_t CParser::DesignatorContext::getRuleIndex() const {
  return CParser::RuleDesignator;
}


std::any CParser::DesignatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitDesignator(this);
  else
    return visitor->visitChildren(this);
}

CParser::DesignatorContext* CParser::designator() {
  DesignatorContext *_localctx = _tracker.createInstance<DesignatorContext>(_ctx, getState());
  enterRule(_localctx, 92, CParser::RuleDesignator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(637);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CParser::LeftBracket: {
        enterOuterAlt(_localctx, 1);
        setState(631);
        match(CParser::LeftBracket);
        setState(632);
        constantExpression();
        setState(633);
        match(CParser::RightBracket);
        break;
      }

      case CParser::Dot: {
        enterOuterAlt(_localctx, 2);
        setState(635);
        match(CParser::Dot);
        setState(636);
        match(CParser::Identifier);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StaticAssertDeclarationContext ------------------------------------------------------------------

CParser::StaticAssertDeclarationContext::StaticAssertDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::StaticAssertDeclarationContext::StaticAssert() {
  return getToken(CParser::StaticAssert, 0);
}

tree::TerminalNode* CParser::StaticAssertDeclarationContext::LeftParen() {
  return getToken(CParser::LeftParen, 0);
}

CParser::ConstantExpressionContext* CParser::StaticAssertDeclarationContext::constantExpression() {
  return getRuleContext<CParser::ConstantExpressionContext>(0);
}

tree::TerminalNode* CParser::StaticAssertDeclarationContext::Comma() {
  return getToken(CParser::Comma, 0);
}

CParser::StringLiteralContext* CParser::StaticAssertDeclarationContext::stringLiteral() {
  return getRuleContext<CParser::StringLiteralContext>(0);
}

tree::TerminalNode* CParser::StaticAssertDeclarationContext::RightParen() {
  return getToken(CParser::RightParen, 0);
}

tree::TerminalNode* CParser::StaticAssertDeclarationContext::Semi() {
  return getToken(CParser::Semi, 0);
}


size_t CParser::StaticAssertDeclarationContext::getRuleIndex() const {
  return CParser::RuleStaticAssertDeclaration;
}


std::any CParser::StaticAssertDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitStaticAssertDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CParser::StaticAssertDeclarationContext* CParser::staticAssertDeclaration() {
  StaticAssertDeclarationContext *_localctx = _tracker.createInstance<StaticAssertDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 94, CParser::RuleStaticAssertDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(639);
    match(CParser::StaticAssert);
    setState(640);
    match(CParser::LeftParen);
    setState(641);
    constantExpression();
    setState(642);
    match(CParser::Comma);
    setState(643);
    stringLiteral();
    setState(644);
    match(CParser::RightParen);
    setState(645);
    match(CParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

CParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::LabeledStatementContext* CParser::StatementContext::labeledStatement() {
  return getRuleContext<CParser::LabeledStatementContext>(0);
}

CParser::CompoundStatementContext* CParser::StatementContext::compoundStatement() {
  return getRuleContext<CParser::CompoundStatementContext>(0);
}

CParser::ExpressionStatementContext* CParser::StatementContext::expressionStatement() {
  return getRuleContext<CParser::ExpressionStatementContext>(0);
}

CParser::SelectionStatementContext* CParser::StatementContext::selectionStatement() {
  return getRuleContext<CParser::SelectionStatementContext>(0);
}

CParser::IterationStatementContext* CParser::StatementContext::iterationStatement() {
  return getRuleContext<CParser::IterationStatementContext>(0);
}

CParser::JumpStatementContext* CParser::StatementContext::jumpStatement() {
  return getRuleContext<CParser::JumpStatementContext>(0);
}


size_t CParser::StatementContext::getRuleIndex() const {
  return CParser::RuleStatement;
}


std::any CParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

CParser::StatementContext* CParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 96, CParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(653);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(647);
      labeledStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(648);
      compoundStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(649);
      expressionStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(650);
      selectionStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(651);
      iterationStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(652);
      jumpStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabeledStatementContext ------------------------------------------------------------------

CParser::LabeledStatementContext::LabeledStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::LabeledStatementContext::Identifier() {
  return getToken(CParser::Identifier, 0);
}

tree::TerminalNode* CParser::LabeledStatementContext::Colon() {
  return getToken(CParser::Colon, 0);
}

CParser::StatementContext* CParser::LabeledStatementContext::statement() {
  return getRuleContext<CParser::StatementContext>(0);
}

tree::TerminalNode* CParser::LabeledStatementContext::Case() {
  return getToken(CParser::Case, 0);
}

CParser::ConstantExpressionContext* CParser::LabeledStatementContext::constantExpression() {
  return getRuleContext<CParser::ConstantExpressionContext>(0);
}

tree::TerminalNode* CParser::LabeledStatementContext::Default() {
  return getToken(CParser::Default, 0);
}


size_t CParser::LabeledStatementContext::getRuleIndex() const {
  return CParser::RuleLabeledStatement;
}


std::any CParser::LabeledStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitLabeledStatement(this);
  else
    return visitor->visitChildren(this);
}

CParser::LabeledStatementContext* CParser::labeledStatement() {
  LabeledStatementContext *_localctx = _tracker.createInstance<LabeledStatementContext>(_ctx, getState());
  enterRule(_localctx, 98, CParser::RuleLabeledStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(666);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(655);
        match(CParser::Identifier);
        setState(656);
        match(CParser::Colon);
        setState(657);
        statement();
        break;
      }

      case CParser::Case: {
        enterOuterAlt(_localctx, 2);
        setState(658);
        match(CParser::Case);
        setState(659);
        constantExpression();
        setState(660);
        match(CParser::Colon);
        setState(661);
        statement();
        break;
      }

      case CParser::Default: {
        enterOuterAlt(_localctx, 3);
        setState(663);
        match(CParser::Default);
        setState(664);
        match(CParser::Colon);
        setState(665);
        statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompoundStatementContext ------------------------------------------------------------------

CParser::CompoundStatementContext::CompoundStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::CompoundStatementContext::LeftBrace() {
  return getToken(CParser::LeftBrace, 0);
}

tree::TerminalNode* CParser::CompoundStatementContext::RightBrace() {
  return getToken(CParser::RightBrace, 0);
}

CParser::BlockItemListContext* CParser::CompoundStatementContext::blockItemList() {
  return getRuleContext<CParser::BlockItemListContext>(0);
}


size_t CParser::CompoundStatementContext::getRuleIndex() const {
  return CParser::RuleCompoundStatement;
}


std::any CParser::CompoundStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitCompoundStatement(this);
  else
    return visitor->visitChildren(this);
}

CParser::CompoundStatementContext* CParser::compoundStatement() {
  CompoundStatementContext *_localctx = _tracker.createInstance<CompoundStatementContext>(_ctx, getState());
  enterRule(_localctx, 100, CParser::RuleCompoundStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(668);
    match(CParser::LeftBrace);
    setState(670);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8936401701028493310) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 7381975649) != 0)) {
      setState(669);
      blockItemList();
    }
    setState(672);
    match(CParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemListContext ------------------------------------------------------------------

CParser::BlockItemListContext::BlockItemListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::BlockItemContext *> CParser::BlockItemListContext::blockItem() {
  return getRuleContexts<CParser::BlockItemContext>();
}

CParser::BlockItemContext* CParser::BlockItemListContext::blockItem(size_t i) {
  return getRuleContext<CParser::BlockItemContext>(i);
}


size_t CParser::BlockItemListContext::getRuleIndex() const {
  return CParser::RuleBlockItemList;
}


std::any CParser::BlockItemListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitBlockItemList(this);
  else
    return visitor->visitChildren(this);
}

CParser::BlockItemListContext* CParser::blockItemList() {
  BlockItemListContext *_localctx = _tracker.createInstance<BlockItemListContext>(_ctx, getState());
  enterRule(_localctx, 102, CParser::RuleBlockItemList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(675); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(674);
      blockItem();
      setState(677); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8936401701028493310) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 7381975649) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

CParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::StatementContext* CParser::BlockItemContext::statement() {
  return getRuleContext<CParser::StatementContext>(0);
}

CParser::DeclarationContext* CParser::BlockItemContext::declaration() {
  return getRuleContext<CParser::DeclarationContext>(0);
}


size_t CParser::BlockItemContext::getRuleIndex() const {
  return CParser::RuleBlockItem;
}


std::any CParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

CParser::BlockItemContext* CParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 104, CParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(681);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(679);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(680);
      declaration();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

CParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::ExpressionStatementContext::Semi() {
  return getToken(CParser::Semi, 0);
}

CParser::CommaExpressionContext* CParser::ExpressionStatementContext::commaExpression() {
  return getRuleContext<CParser::CommaExpressionContext>(0);
}


size_t CParser::ExpressionStatementContext::getRuleIndex() const {
  return CParser::RuleExpressionStatement;
}


std::any CParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

CParser::ExpressionStatementContext* CParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 106, CParser::RuleExpressionStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(684);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8935212166953304066) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 7381975137) != 0)) {
      setState(683);
      commaExpression(0);
    }
    setState(686);
    match(CParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectionStatementContext ------------------------------------------------------------------

CParser::SelectionStatementContext::SelectionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::SelectionStatementContext::If() {
  return getToken(CParser::If, 0);
}

tree::TerminalNode* CParser::SelectionStatementContext::LeftParen() {
  return getToken(CParser::LeftParen, 0);
}

CParser::CommaExpressionContext* CParser::SelectionStatementContext::commaExpression() {
  return getRuleContext<CParser::CommaExpressionContext>(0);
}

tree::TerminalNode* CParser::SelectionStatementContext::RightParen() {
  return getToken(CParser::RightParen, 0);
}

std::vector<CParser::StatementContext *> CParser::SelectionStatementContext::statement() {
  return getRuleContexts<CParser::StatementContext>();
}

CParser::StatementContext* CParser::SelectionStatementContext::statement(size_t i) {
  return getRuleContext<CParser::StatementContext>(i);
}

tree::TerminalNode* CParser::SelectionStatementContext::Else() {
  return getToken(CParser::Else, 0);
}

tree::TerminalNode* CParser::SelectionStatementContext::Switch() {
  return getToken(CParser::Switch, 0);
}


size_t CParser::SelectionStatementContext::getRuleIndex() const {
  return CParser::RuleSelectionStatement;
}


std::any CParser::SelectionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitSelectionStatement(this);
  else
    return visitor->visitChildren(this);
}

CParser::SelectionStatementContext* CParser::selectionStatement() {
  SelectionStatementContext *_localctx = _tracker.createInstance<SelectionStatementContext>(_ctx, getState());
  enterRule(_localctx, 108, CParser::RuleSelectionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(703);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CParser::If: {
        enterOuterAlt(_localctx, 1);
        setState(688);
        match(CParser::If);
        setState(689);
        match(CParser::LeftParen);
        setState(690);
        commaExpression(0);
        setState(691);
        match(CParser::RightParen);
        setState(692);
        statement();
        setState(695);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 80, _ctx)) {
        case 1: {
          setState(693);
          match(CParser::Else);
          setState(694);
          statement();
          break;
        }

        default:
          break;
        }
        break;
      }

      case CParser::Switch: {
        enterOuterAlt(_localctx, 2);
        setState(697);
        match(CParser::Switch);
        setState(698);
        match(CParser::LeftParen);
        setState(699);
        commaExpression(0);
        setState(700);
        match(CParser::RightParen);
        setState(701);
        statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IterationStatementContext ------------------------------------------------------------------

CParser::IterationStatementContext::IterationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::IterationStatementContext::While() {
  return getToken(CParser::While, 0);
}

tree::TerminalNode* CParser::IterationStatementContext::LeftParen() {
  return getToken(CParser::LeftParen, 0);
}

CParser::CommaExpressionContext* CParser::IterationStatementContext::commaExpression() {
  return getRuleContext<CParser::CommaExpressionContext>(0);
}

tree::TerminalNode* CParser::IterationStatementContext::RightParen() {
  return getToken(CParser::RightParen, 0);
}

CParser::StatementContext* CParser::IterationStatementContext::statement() {
  return getRuleContext<CParser::StatementContext>(0);
}

tree::TerminalNode* CParser::IterationStatementContext::Do() {
  return getToken(CParser::Do, 0);
}

tree::TerminalNode* CParser::IterationStatementContext::Semi() {
  return getToken(CParser::Semi, 0);
}

tree::TerminalNode* CParser::IterationStatementContext::For() {
  return getToken(CParser::For, 0);
}

CParser::ForConditionContext* CParser::IterationStatementContext::forCondition() {
  return getRuleContext<CParser::ForConditionContext>(0);
}


size_t CParser::IterationStatementContext::getRuleIndex() const {
  return CParser::RuleIterationStatement;
}


std::any CParser::IterationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitIterationStatement(this);
  else
    return visitor->visitChildren(this);
}

CParser::IterationStatementContext* CParser::iterationStatement() {
  IterationStatementContext *_localctx = _tracker.createInstance<IterationStatementContext>(_ctx, getState());
  enterRule(_localctx, 110, CParser::RuleIterationStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(725);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CParser::While: {
        enterOuterAlt(_localctx, 1);
        setState(705);
        match(CParser::While);
        setState(706);
        match(CParser::LeftParen);
        setState(707);
        commaExpression(0);
        setState(708);
        match(CParser::RightParen);
        setState(709);
        statement();
        break;
      }

      case CParser::Do: {
        enterOuterAlt(_localctx, 2);
        setState(711);
        match(CParser::Do);
        setState(712);
        statement();
        setState(713);
        match(CParser::While);
        setState(714);
        match(CParser::LeftParen);
        setState(715);
        commaExpression(0);
        setState(716);
        match(CParser::RightParen);
        setState(717);
        match(CParser::Semi);
        break;
      }

      case CParser::For: {
        enterOuterAlt(_localctx, 3);
        setState(719);
        match(CParser::For);
        setState(720);
        match(CParser::LeftParen);
        setState(721);
        forCondition();
        setState(722);
        match(CParser::RightParen);
        setState(723);
        statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForConditionContext ------------------------------------------------------------------

CParser::ForConditionContext::ForConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CParser::ForConditionContext::Semi() {
  return getTokens(CParser::Semi);
}

tree::TerminalNode* CParser::ForConditionContext::Semi(size_t i) {
  return getToken(CParser::Semi, i);
}

CParser::DeclarationContext* CParser::ForConditionContext::declaration() {
  return getRuleContext<CParser::DeclarationContext>(0);
}

std::vector<CParser::CommaExpressionContext *> CParser::ForConditionContext::commaExpression() {
  return getRuleContexts<CParser::CommaExpressionContext>();
}

CParser::CommaExpressionContext* CParser::ForConditionContext::commaExpression(size_t i) {
  return getRuleContext<CParser::CommaExpressionContext>(i);
}


size_t CParser::ForConditionContext::getRuleIndex() const {
  return CParser::RuleForCondition;
}


std::any CParser::ForConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitForCondition(this);
  else
    return visitor->visitChildren(this);
}

CParser::ForConditionContext* CParser::forCondition() {
  ForConditionContext *_localctx = _tracker.createInstance<ForConditionContext>(_ctx, getState());
  enterRule(_localctx, 112, CParser::RuleForCondition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(732);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx)) {
    case 1: {
      setState(728);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 8935212166953304066) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 65)) & 7381975137) != 0)) {
        setState(727);
        commaExpression(0);
      }
      setState(730);
      match(CParser::Semi);
      break;
    }

    case 2: {
      setState(731);
      declaration();
      break;
    }

    default:
      break;
    }
    setState(735);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8935212166953304066) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 7381975137) != 0)) {
      setState(734);
      commaExpression(0);
    }
    setState(737);
    match(CParser::Semi);
    setState(739);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8935212166953304066) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 7381975137) != 0)) {
      setState(738);
      commaExpression(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JumpStatementContext ------------------------------------------------------------------

CParser::JumpStatementContext::JumpStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CParser::JumpStatementContext::Semi() {
  return getToken(CParser::Semi, 0);
}

tree::TerminalNode* CParser::JumpStatementContext::Goto() {
  return getToken(CParser::Goto, 0);
}

tree::TerminalNode* CParser::JumpStatementContext::Identifier() {
  return getToken(CParser::Identifier, 0);
}

tree::TerminalNode* CParser::JumpStatementContext::Continue() {
  return getToken(CParser::Continue, 0);
}

tree::TerminalNode* CParser::JumpStatementContext::Break() {
  return getToken(CParser::Break, 0);
}

tree::TerminalNode* CParser::JumpStatementContext::Return() {
  return getToken(CParser::Return, 0);
}

CParser::CommaExpressionContext* CParser::JumpStatementContext::commaExpression() {
  return getRuleContext<CParser::CommaExpressionContext>(0);
}


size_t CParser::JumpStatementContext::getRuleIndex() const {
  return CParser::RuleJumpStatement;
}


std::any CParser::JumpStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitJumpStatement(this);
  else
    return visitor->visitChildren(this);
}

CParser::JumpStatementContext* CParser::jumpStatement() {
  JumpStatementContext *_localctx = _tracker.createInstance<JumpStatementContext>(_ctx, getState());
  enterRule(_localctx, 114, CParser::RuleJumpStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(749);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CParser::Goto: {
        setState(741);
        match(CParser::Goto);
        setState(742);
        match(CParser::Identifier);
        break;
      }

      case CParser::Continue: {
        setState(743);
        match(CParser::Continue);
        break;
      }

      case CParser::Break: {
        setState(744);
        match(CParser::Break);
        break;
      }

      case CParser::Return: {
        setState(745);
        match(CParser::Return);
        setState(747);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 8935212166953304066) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 65)) & 7381975137) != 0)) {
          setState(746);
          commaExpression(0);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(751);
    match(CParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternalDeclarationContext ------------------------------------------------------------------

CParser::ExternalDeclarationContext::ExternalDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::FunctionDefinitionContext* CParser::ExternalDeclarationContext::functionDefinition() {
  return getRuleContext<CParser::FunctionDefinitionContext>(0);
}

CParser::DeclarationContext* CParser::ExternalDeclarationContext::declaration() {
  return getRuleContext<CParser::DeclarationContext>(0);
}

tree::TerminalNode* CParser::ExternalDeclarationContext::Semi() {
  return getToken(CParser::Semi, 0);
}


size_t CParser::ExternalDeclarationContext::getRuleIndex() const {
  return CParser::RuleExternalDeclaration;
}


std::any CParser::ExternalDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitExternalDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CParser::ExternalDeclarationContext* CParser::externalDeclaration() {
  ExternalDeclarationContext *_localctx = _tracker.createInstance<ExternalDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 116, CParser::RuleExternalDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(756);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 89, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(753);
      functionDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(754);
      declaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(755);
      match(CParser::Semi);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefinitionContext ------------------------------------------------------------------

CParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CParser::DeclarationSpecifiersContext* CParser::FunctionDefinitionContext::declarationSpecifiers() {
  return getRuleContext<CParser::DeclarationSpecifiersContext>(0);
}

CParser::DeclaratorContext* CParser::FunctionDefinitionContext::declarator() {
  return getRuleContext<CParser::DeclaratorContext>(0);
}

CParser::CompoundStatementContext* CParser::FunctionDefinitionContext::compoundStatement() {
  return getRuleContext<CParser::CompoundStatementContext>(0);
}

CParser::DeclarationListContext* CParser::FunctionDefinitionContext::declarationList() {
  return getRuleContext<CParser::DeclarationListContext>(0);
}


size_t CParser::FunctionDefinitionContext::getRuleIndex() const {
  return CParser::RuleFunctionDefinition;
}


std::any CParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

CParser::FunctionDefinitionContext* CParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 118, CParser::RuleFunctionDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(758);
    declarationSpecifiers();
    setState(759);
    declarator();
    setState(761);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 63599263118436) != 0) || _la == CParser::Identifier) {
      setState(760);
      declarationList();
    }
    setState(763);
    compoundStatement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationListContext ------------------------------------------------------------------

CParser::DeclarationListContext::DeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CParser::DeclarationContext *> CParser::DeclarationListContext::declaration() {
  return getRuleContexts<CParser::DeclarationContext>();
}

CParser::DeclarationContext* CParser::DeclarationListContext::declaration(size_t i) {
  return getRuleContext<CParser::DeclarationContext>(i);
}


size_t CParser::DeclarationListContext::getRuleIndex() const {
  return CParser::RuleDeclarationList;
}


std::any CParser::DeclarationListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CVisitor*>(visitor))
    return parserVisitor->visitDeclarationList(this);
  else
    return visitor->visitChildren(this);
}

CParser::DeclarationListContext* CParser::declarationList() {
  DeclarationListContext *_localctx = _tracker.createInstance<DeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 120, CParser::RuleDeclarationList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(766); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(765);
      declaration();
      setState(768); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 63599263118436) != 0) || _la == CParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool CParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);
    case 8: return commaExpressionSempred(antlrcpp::downCast<CommaExpressionContext *>(context), predicateIndex);
    case 31: return directDeclaratorSempred(antlrcpp::downCast<DirectDeclaratorContext *>(context), predicateIndex);
    case 40: return directAbstractDeclaratorSempred(antlrcpp::downCast<DirectAbstractDeclaratorContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 12);
    case 1: return precpred(_ctx, 11);
    case 2: return precpred(_ctx, 10);
    case 3: return precpred(_ctx, 9);
    case 4: return precpred(_ctx, 8);
    case 5: return precpred(_ctx, 7);
    case 6: return precpred(_ctx, 6);
    case 7: return precpred(_ctx, 5);
    case 8: return precpred(_ctx, 4);
    case 9: return precpred(_ctx, 3);
    case 10: return precpred(_ctx, 2);
    case 11: return precpred(_ctx, 1);
    case 12: return precpred(_ctx, 14);

  default:
    break;
  }
  return true;
}

bool CParser::commaExpressionSempred(CommaExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 13: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CParser::directDeclaratorSempred(DirectDeclaratorContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 14: return precpred(_ctx, 7);
    case 15: return precpred(_ctx, 6);
    case 16: return precpred(_ctx, 5);
    case 17: return precpred(_ctx, 4);
    case 18: return precpred(_ctx, 3);
    case 19: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CParser::directAbstractDeclaratorSempred(DirectAbstractDeclaratorContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 20: return precpred(_ctx, 5);
    case 21: return precpred(_ctx, 4);
    case 22: return precpred(_ctx, 3);
    case 23: return precpred(_ctx, 2);
    case 24: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void CParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  cParserInitialize();
#else
  ::antlr4::internal::call_once(cParserOnceFlag, cParserInitialize);
#endif
}
