/**
* @file driver.h
* @brief 工具接口类
* @details 定义接口类供调用
* @author zrz
* @version 1.4.2
*/

#ifndef TOOL_DRIVER_H
#define TOOL_DRIVER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>

//// Give Flex the prototype of yylex we want ...
//# define YY_DECL \
//	tool::Parser::symbol_type yylex (Driver& drv)
//// ... and declare it for the parser's sake.
//YY_DECL;

/**
* @brief 工具接口的命名空间
* 工具接口的命名空间，使用using namespace tool来方便调用接口
*/
namespace tool {
    // class location;
    class Scanner;
    class Solver;
    class location;

    class Context;
    class Node;
    class QualType;

    enum class result;

    /**
    * @brief 接口类Driver
    * 工具的接口类Driver，在使用工具时，需要先实例化一个Driver类
    */
    class Driver
    {
        friend class Parser;
        friend class Scanner;
        Scanner* lexer = nullptr;
        Solver* solver = nullptr;
        std::vector<Context*> ctxs;
        bool analyzed = false, parsed = false;
        // int path_type = 0;
        result res;
        std::string source_name = "no source";
        QualType& qt;
        int stars;

        void setQualType(const QualType& qt);
        QualType& getQualType();

        // Whether to generate parser debug traces.
        bool trace_parsing;

        // Handling the scanner.
        //void scan_begin ();
        //void scan_end ();
        // Whether to generate scanner debug traces.
        bool trace_scanning;
        // The token's location used by the scanner.
        tool::location& location;

        void reset();
    public:
        /**
        * @brief Driver的构造函数
        */
        Driver();
        /**
        * @brief Driver的析构函数
        */
        ~Driver();

        Context* getContext() { return ctxs.back(); }
        void push(Context* ctx);
        void pop();
        void pushAST(Node* node);
        /**
        * @brief 打印抽象语法树
        */
        void printAST();
        /**
        * @brief 打印抽象语法树
        * @param os		输出流
        */
        void printAST(std::ostream& os);
        /**
        * @brief 打印路径代码。
        */
        void printCode();
        /**
        * @brief 打印路径代码
        * @param os		输出流
        */
        void printCode(std::ostream& os);

        /**
        * @brief 分析路径可行性。
        * @note 需要先读取路径再调用该函数。
        * @see parseStream parseString parseFile
        * @return 路径可行与否
        *	@retval false 不可行
        *	@retval	true 可行
        */
        bool feasible();
        /**
        * @brief 从流中分析路径可行性
        * @param in			输入流
        * @param in_name	输入流的名称，默认为"stream input"
        * @return 路径可行与否
        *	@retval false 不可行
        *	@retval	true 可行
        */
        int feasible(std::istream& in, const std::string &in_name = "stream input");
        /**
        * @brief 从字符串中分析路径可行性
        * @param in			输入字符串
        * @param in_name	输入的名称，默认为"string stream"
        * @return 路径可行与否
        *	@retval false 不可行
        *	@retval	true 可行
        */
        int feasible(const std::string& in, const std::string& in_name = "string stream");
        // int feasible(const std::string& file_name);
        
        /**
        * @brief 从流中读取路径
        * @param in			输入流
        * @param in_name	输入流的名称，默认为"stream input"
        * @return 读取是否成功
        *	@retval 0 路径读取成功
        *	@retval 1 路径读取失败
        */
        int parseStream(std::istream& in, const std::string& in_name = "stream input");
        /**
        * @brief 从字符串中读取路径
        * @param in			输入字符串
        * @param in_name	输入的名称，默认为"string stream"
        * @return 读取是否成功
        *	@retval 0 路径读取成功
        *	@retval 1 路径读取失败
        */
        int parseString(const std::string& in, const std::string& in_name = "string stream");
        /**
        * @brief 从文件中读取路径
        * @param file_name	输入文件的名称（或路径）
        * @return 读取是否成功
        *	@retval 0 路径读取成功
        *	@retval 1 路径读取失败
        */
        int parseFile(const std::string& file_name);
        
        /**
        * @brief 打印可行的初始输入
        * @note 输出为SMT2格式。使用前需要先调用\ref feasible。
        * @see feasible
        * @param os			输出流，默认为标准输出流
        */
        void printModel(std::ostream& os = std::cout);
        /**
        * @brief 获取可行的初始输入
        * @note 返回为SMT2格式。使用前需要先调用\ref feasible。
        * @see feasible
        * @return 表示输入的SMT2格式字符串
        */
        std::string getModel();
        /**
        * @brief 打印可行输入的解空间
        * @note 需要先调用\ref feasible。
        * @see feasible
        * @param os			输出流，默认为标准输出流
        */
        void printSMT2(std::ostream& os = std::cout);
        /**
        * @brief 获取可行输入的解空间
        * @note 需要先调用\ref feasible。
        * @see feasible
        * @return 表示输入解空间的SMT2格式字符串
        */
        std::string getSMT2();
        /**
        * @brief 打印数组访存次数
        * @param os			输出流，默认为标准输出
        */
        void printMem(std::ostream& os = std::cout);
        /**
        * @brief 获取数组访存次数
        * @return 数组访存次数
        */
        int getMem();
    };
}

#endif // !TOOL_DRIVER_H
