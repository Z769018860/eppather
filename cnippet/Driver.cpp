// Copyright (c) 2016/17/18/19/20/21/22 Leandro T. C. Melo <ltcmelo@gmail.com>
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

#include "Driver.h"

#include "CompilerFrontend.h"
#include "CompilerFrontend_C.h"
#include "Configuration.h"
#include "Configuration_C.h"
#include "FileInfo.h"
#include "IO.h"
#include "Plugin.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <cstring>
#include <cctype>
#include <vector>

using namespace psy;
using namespace cnip;

namespace DEBUG { extern bool globalDebugEnabled; }

constexpr int Driver::SUCCESS;
constexpr int Driver::ERROR_NoInputFile;
constexpr int Driver::ERROR_UnrecognizedCmdLineOption;
constexpr int Driver::ERROR_CannotLoadPluging;
constexpr int Driver::ERROR_LanguageNotRecognized;

Driver::Driver()
{}

Driver::~Driver()
{}

int Driver::execute(int argc, char* argv[])
{
    cxxopts::Options cmdLineOpts(argv[0], "cnippet");
    cmdLineOpts
        .positional_help("file")
        .add_options()
            ("file",
                "The input file(s) path(s).",
                cxxopts::value<std::vector<std::string>>())
            ("l,lang",
                "Specify the language.",
                cxxopts::value<std::string>()->default_value("C"),
                "<C>")
            ("z,dump-AST",
                "Dump the program's AST to the console.")
            ("c,dump-CFG",
                "Dump the program's CFG to the console.")
            ("f,dump-DFS",
              "Dump the program's path in the DFS mode to the console.(icov)")
            ("q,dump-DFS2",
              "Dump the program's path in the DFS mode to the console.(bcov)")
            ("g,dump-MaxMemDP",
              "Dump the program's worst path in the DP mode to the console.")
            ("b,dump-BFS",
              "Dump the program's path in the BFS mode to the console.")
            ("d,debug",
                "Enable debugging.",
                cxxopts::value<bool>(DEBUG::globalDebugEnabled))
            ("volce",
                "Enable VolCE model counting.")
            ("maxloop",
                "Set loop unroll upper bound.",
                cxxopts::value<int>()->default_value("3"))
            ("maxpaths",
                "Set maximum path count.",
                cxxopts::value<int>()->default_value("1000"))
            ("p,plugin",
                "Load plugin with the given name.",
                cxxopts::value<std::string>())
            ("w,WIP",
                "Enable Work-In-Progress features.")
            ("h,help",
                "Print instructions.")
    ;

    ConfigurationForC::extend(cmdLineOpts);

    std::unique_ptr<CompilerFrontend> FE;
    std::vector<std::string> filesPaths;
    try {
        cmdLineOpts.parse_positional(std::vector<std::string>{"file"});
        std::vector<std::string> normalizedArgs;
        normalizedArgs.reserve(static_cast<size_t>(argc));
        for (int i = 0; i < argc; ++i) {
            if (std::strcmp(argv[i], "-volce") == 0) {
                normalizedArgs.emplace_back("--volce");
            } else {
                normalizedArgs.emplace_back(argv[i]);
            }
        }
        if (normalizedArgs.size() > 2) {
            auto isNumber = [](const std::string& value) {
                return !value.empty() &&
                       std::all_of(value.begin(), value.end(),
                                   [](unsigned char ch) { return std::isdigit(ch); });
            };
            const bool hasMaxLoop = std::find(normalizedArgs.begin(),
                                              normalizedArgs.end(),
                                              "--maxloop") != normalizedArgs.end();
            const bool hasMaxPaths = std::find(normalizedArgs.begin(),
                                               normalizedArgs.end(),
                                               "--maxpaths") != normalizedArgs.end();
            std::vector<std::string> trailingNumbers;
            for (int i = static_cast<int>(normalizedArgs.size()) - 1; i > 0; --i) {
                const std::string& arg = normalizedArgs[static_cast<size_t>(i)];
                if (arg == "--") break;
                if (isNumber(arg)) {
                    trailingNumbers.push_back(arg);
                } else {
                    break;
                }
            }
            auto findInsertIndex = [&]() {
                size_t insertIndex = normalizedArgs.size();
                auto dashDashIt = std::find(normalizedArgs.begin() + 1,
                                            normalizedArgs.end(),
                                            "--");
                if (dashDashIt != normalizedArgs.end()) {
                    insertIndex = static_cast<size_t>(std::distance(normalizedArgs.begin(),
                                                                    dashDashIt));
                } else {
                    auto positionalIt = std::find_if(normalizedArgs.begin() + 1,
                                                     normalizedArgs.end(),
                                                     [](const std::string& arg) {
                                                         return arg.empty() || arg[0] != '-';
                                                     });
                    if (positionalIt != normalizedArgs.end()) {
                        insertIndex = static_cast<size_t>(std::distance(normalizedArgs.begin(),
                                                                        positionalIt));
                    }
                }
                if (insertIndex > normalizedArgs.size()) {
                    insertIndex = normalizedArgs.size();
                }
                return insertIndex;
            };
            auto insertOption = [&](const std::string& option, const std::string& value) {
                size_t insertIndex = findInsertIndex();
                normalizedArgs.insert(normalizedArgs.begin() + insertIndex, option);
                normalizedArgs.insert(normalizedArgs.begin() + insertIndex + 1, value);
            };
            if (!trailingNumbers.empty()) {
                size_t consumed = 0;
                if (trailingNumbers.size() == 1) {
                    if (!hasMaxLoop) {
                        insertOption("--maxloop", trailingNumbers[0]);
                        consumed = 1;
                    } else if (!hasMaxPaths) {
                        insertOption("--maxpaths", trailingNumbers[0]);
                        consumed = 1;
                    }
                } else {
                    if (!hasMaxPaths) {
                        insertOption("--maxpaths", trailingNumbers[0]);
                        consumed += 1;
                    }
                    if (!hasMaxLoop && consumed < trailingNumbers.size()) {
                        insertOption("--maxloop", trailingNumbers[consumed]);
                        consumed += 1;
                    }
                }
                for (size_t i = 0; i < consumed; ++i) {
                    normalizedArgs.pop_back();
                }
            }
        }
        std::vector<char*> argPtrs;
        argPtrs.reserve(normalizedArgs.size());
        for (auto& arg : normalizedArgs) {
            argPtrs.push_back(const_cast<char*>(arg.c_str()));
        }

        int argcCopy = static_cast<int>(argPtrs.size());
        auto argvCopy = argPtrs.data();
        auto parsedCmdLine = cmdLineOpts.parse(argcCopy, argvCopy);

        if (parsedCmdLine.count("help")) {
            std::cout << cmdLineOpts.help({"", "Group"}) << std::endl;
            return SUCCESS;
        }

        if (parsedCmdLine.count("plugin")) {
            auto pluginName = parsedCmdLine["plugin"].as<std::string>();
            Plugin::load(pluginName);
            if (!Plugin::isLoaded()) {
                std::cerr << kCnip << "cannot load plugin " << pluginName << std::endl;
                return ERROR_CannotLoadPluging;
            }
        }

        if (parsedCmdLine.count("file")) {
            filesPaths = parsedCmdLine["file"].as<std::vector<std::string>>();
        }
        else {
            std::cerr << kCnip << "no input file(s)" << std::endl;
            return ERROR_NoInputFile;
        }

        auto lang = parsedCmdLine["lang"].as<std::string>();
        if (lang != "C") {
            std::cerr << kCnip << "language " << lang << " not recognized" << std::endl;
            return ERROR_LanguageNotRecognized;
        }

        FE.reset(new CCompilerFrontend(parsedCmdLine));
    }
    catch (...) {
        std::cerr << kCnip << "unrecognized command-line option" << std::endl;
        return ERROR_UnrecognizedCmdLineOption;
    }

    for (auto filePath : filesPaths) {
        auto [exit, srcText] = readFile(filePath);
        if (exit != 0)
            return ERROR_FileNotFound;

        FileInfo fi(filePath);

        try {
            exit = FE->run(srcText, fi);
        }
        catch (...) {
            Plugin::unload();
            return Driver::ERROR;
        }

        if (exit != 0)
            return exit;
    }

    return SUCCESS;
}
