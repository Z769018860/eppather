// Minimal VolCE-style model counter for SMT2 files using Z3.
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

#include "volce/volce_api.h"

namespace {
struct Options {
    std::string smtFile;
    std::optional<volce::Range> defaultRange = volce::Range{-8, 8};
    std::unordered_map<std::string, volce::Range> namedRanges;
};

bool parseRange(const std::string& spec, std::string& name, volce::Range& range) {
    auto first = spec.find(':');
    if (first == std::string::npos) {
        return false;
    }
    auto second = spec.find(':', first + 1);
    if (second == std::string::npos) {
        return false;
    }
    name = spec.substr(0, first);
    if (name.empty()) {
        return false;
    }
    range.lower = std::strtoll(spec.substr(first + 1, second - first - 1).c_str(), nullptr, 10);
    range.upper = std::strtoll(spec.substr(second + 1).c_str(), nullptr, 10);
    return true;
}

std::optional<Options> parseArgs(int argc, char** argv) {
    Options opts;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--lower" && i + 1 < argc) {
            if (!opts.defaultRange) {
                opts.defaultRange = volce::Range{0, 0};
            }
            opts.defaultRange->lower = std::strtoll(argv[++i], nullptr, 10);
        } else if (arg == "--upper" && i + 1 < argc) {
            if (!opts.defaultRange) {
                opts.defaultRange = volce::Range{0, 0};
            }
            opts.defaultRange->upper = std::strtoll(argv[++i], nullptr, 10);
        } else if (arg == "--smt" && i + 1 < argc) {
            opts.smtFile = argv[++i];
        } else if (arg == "--range" && i + 1 < argc) {
            std::string name;
            volce::Range range{0, 0};
            if (parseRange(argv[++i], name, range)) {
                opts.namedRanges[name] = range;
            }
        } else if (arg == "--no-default-range") {
            opts.defaultRange.reset();
        } else if (arg == "--help" || arg == "-h") {
            return std::nullopt;
        }
    }
    if (opts.smtFile.empty()) {
        return std::nullopt;
    }
    return opts;
}

}  // namespace

int main(int argc, char** argv) {
    auto opts = parseArgs(argc, argv);
    if (!opts) {
        std::cerr << "Usage: volce --smt <file> [--lower N] [--upper N] [--range name:lower:upper] [--no-default-range]\n";
        return 1;
    }

    auto result = volce::countModelsFromSmt2File(opts->smtFile, opts->namedRanges, opts->defaultRange);
    if (!result) {
        std::cerr << "Failed to count models (check ranges and SMT2 input).\n";
        return 1;
    }

    std::cout << result->count << std::endl;
    return 0;
}
