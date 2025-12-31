// Minimal VolCE-style model counter for SMT2 files using Z3.
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

#include "z3.h"

namespace {
struct Options {
    std::string smtFile;
    int lower = -1023;
    int upper = 1024;
};

std::optional<Options> parseArgs(int argc, char** argv) {
    Options opts;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--lower" && i + 1 < argc) {
            opts.lower = std::atoi(argv[++i]);
        } else if (arg == "--upper" && i + 1 < argc) {
            opts.upper = std::atoi(argv[++i]);
        } else if (arg == "--smt" && i + 1 < argc) {
            opts.smtFile = argv[++i];
        } else if (arg == "--help" || arg == "-h") {
            return std::nullopt;
        }
    }
    if (opts.smtFile.empty()) {
        return std::nullopt;
    }
    return opts;
}

bool isZeroArity(const Z3_context ctx, Z3_func_decl decl) {
    return Z3_get_arity(ctx, decl) == 0;
}

bool isBv32(const Z3_context ctx, Z3_sort sort) {
    if (Z3_get_sort_kind(ctx, sort) != Z3_BV_SORT) {
        return false;
    }
    return Z3_get_bv_sort_size(ctx, sort) == 32;
}

Z3_ast mkSignedBound(Z3_context ctx, int value) {
    Z3_sort bv32 = Z3_mk_bv_sort(ctx, 32);
    return Z3_mk_int64(ctx, value, bv32);
}

void assertBound(Z3_context ctx, Z3_solver solver, Z3_ast var, int lower, int upper) {
    Z3_ast lowerAst = mkSignedBound(ctx, lower);
    Z3_ast upperAst = mkSignedBound(ctx, upper);
    Z3_ast ge = Z3_mk_bvsge(ctx, var, lowerAst);
    Z3_ast le = Z3_mk_bvsle(ctx, var, upperAst);
    Z3_ast bounds[2] = {ge, le};
    Z3_ast both = Z3_mk_and(ctx, 2, bounds);
    Z3_solver_assert(ctx, solver, both);
}

void assertParsedFormulas(Z3_context ctx, Z3_solver solver, Z3_ast_vector vec) {
    unsigned num = Z3_ast_vector_size(ctx, vec);
    for (unsigned i = 0; i < num; ++i) {
        Z3_ast ast = Z3_ast_vector_get(ctx, vec, i);
        Z3_solver_assert(ctx, solver, ast);
    }
}

void collectFromAst(Z3_context ctx,
                    Z3_ast ast,
                    std::unordered_set<unsigned>& seen,
                    std::vector<Z3_func_decl>& decls) {
    if (Z3_get_ast_kind(ctx, ast) == Z3_APP_AST) {
        Z3_app app = Z3_to_app(ctx, ast);
        Z3_func_decl decl = Z3_get_app_decl(ctx, app);
        if (Z3_get_decl_kind(ctx, decl) == Z3_OP_UNINTERPRETED && isZeroArity(ctx, decl) &&
            isBv32(ctx, Z3_get_range(ctx, decl))) {
            unsigned id = Z3_get_ast_id(ctx, Z3_func_decl_to_ast(ctx, decl));
            if (seen.insert(id).second) {
                decls.push_back(decl);
            }
        }
        unsigned argc = Z3_get_app_num_args(ctx, app);
        for (unsigned i = 0; i < argc; ++i) {
            collectFromAst(ctx, Z3_get_app_arg(ctx, app, i), seen, decls);
        }
    }
}

std::vector<Z3_func_decl> collectZeroArityDecls(Z3_context ctx, Z3_ast_vector vec) {
    std::vector<Z3_func_decl> decls;
    std::unordered_set<unsigned> seen;
    unsigned num = Z3_ast_vector_size(ctx, vec);
    for (unsigned i = 0; i < num; ++i) {
        collectFromAst(ctx, Z3_ast_vector_get(ctx, vec, i), seen, decls);
    }
    return decls;
}

std::uint64_t countModels(Z3_context ctx, Z3_solver solver, const std::vector<Z3_func_decl>& decls) {
    std::uint64_t count = 0;
    while (Z3_solver_check(ctx, solver) == Z3_L_TRUE) {
        Z3_model model = Z3_solver_get_model(ctx, solver);
        if (!model) {
            break;
        }
        Z3_model_inc_ref(ctx, model);
        std::vector<Z3_ast> equalities;
        equalities.reserve(decls.size());
        for (auto decl : decls) {
            Z3_ast value = nullptr;
            Z3_ast var = Z3_mk_app(ctx, decl, 0, nullptr);
            if (Z3_model_eval(ctx, model, var, true, &value) == Z3_L_TRUE && value) {
                equalities.push_back(Z3_mk_eq(ctx, var, value));
            }
        }
        Z3_model_dec_ref(ctx, model);
        if (equalities.empty()) {
            ++count;
            break;
        }
        Z3_ast all = Z3_mk_and(ctx, static_cast<unsigned>(equalities.size()), equalities.data());
        Z3_ast block = Z3_mk_not(ctx, all);
        Z3_solver_assert(ctx, solver, block);
        ++count;
    }
    return count;
}
}  // namespace

int main(int argc, char** argv) {
    auto opts = parseArgs(argc, argv);
    if (!opts) {
        std::cerr << "Usage: volce --smt <file> [--lower N] [--upper N]\n";
        return 1;
    }

    Z3_config config = Z3_mk_config();
    Z3_context ctx = Z3_mk_context(config);
    Z3_del_config(config);

    Z3_solver solver = Z3_mk_solver(ctx);
    Z3_solver_inc_ref(ctx, solver);

    Z3_ast_vector vec = Z3_parse_smtlib2_file(ctx, opts->smtFile.c_str(), 0, nullptr, nullptr, 0, nullptr, nullptr);
    assertParsedFormulas(ctx, solver, vec);

    const auto decls = collectZeroArityDecls(ctx, vec);
    for (auto decl : decls) {
        Z3_ast var = Z3_mk_app(ctx, decl, 0, nullptr);
        assertBound(ctx, solver, var, opts->lower, opts->upper);
    }

    std::uint64_t count = countModels(ctx, solver, decls);
    std::cout << count << std::endl;

    Z3_solver_dec_ref(ctx, solver);
    Z3_del_context(ctx);
    return 0;
}
