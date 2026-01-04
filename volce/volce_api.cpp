#include "volce/volce_api.h"

#include <limits>
#include <unordered_set>

#include "z3.h"

namespace {

bool isZeroArity(const Z3_context ctx, Z3_func_decl decl) {
    return Z3_get_arity(ctx, decl) == 0;
}

bool isBitVector(const Z3_context ctx, Z3_sort sort) {
    return Z3_get_sort_kind(ctx, sort) == Z3_BV_SORT;
}

unsigned getBitVectorSize(const Z3_context ctx, Z3_sort sort) {
    return Z3_get_bv_sort_size(ctx, sort);
}

Z3_ast mkSignedBound(Z3_context ctx, std::int64_t value, Z3_sort sort) {
    return Z3_mk_int64(ctx, value, sort);
}

bool fitsSignedRange(unsigned bits, const volce::Range& range) {
    if (bits == 0 || bits > 63) {
        return false;
    }
    if (bits == 63) {
        return range.lower >= std::numeric_limits<std::int64_t>::min() &&
               range.upper <= std::numeric_limits<std::int64_t>::max();
    }
    const std::int64_t min = -(static_cast<std::int64_t>(1) << (bits - 1));
    const std::int64_t max = (static_cast<std::int64_t>(1) << (bits - 1)) - 1;
    return range.lower >= min && range.upper <= max;
}

void assertBound(Z3_context ctx, Z3_solver solver, Z3_ast var, const volce::Range& range) {
    Z3_sort sort = Z3_get_sort(ctx, var);
    Z3_ast lowerAst = mkSignedBound(ctx, range.lower, sort);
    Z3_ast upperAst = mkSignedBound(ctx, range.upper, sort);
    Z3_ast ge = Z3_mk_bvsge(ctx, var, lowerAst);
    Z3_ast le = Z3_mk_bvsle(ctx, var, upperAst);
    Z3_ast bounds[2] = {ge, le};
    Z3_solver_assert(ctx, solver, Z3_mk_and(ctx, 2, bounds));
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
            isBitVector(ctx, Z3_get_range(ctx, decl))) {
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
        Z3_solver_assert(ctx, solver, Z3_mk_not(ctx, all));
        ++count;
    }
    return count;
}

std::optional<volce::Range> lookupRange(const std::string& name,
                                       const std::unordered_map<std::string, volce::Range>& ranges,
                                       const std::optional<volce::Range>& default_range) {
    auto it = ranges.find(name);
    if (it != ranges.end()) {
        return it->second;
    }
    return default_range;
}

std::optional<volce::CountResult> countInternal(Z3_context ctx,
                                               Z3_solver solver,
                                               Z3_ast_vector vec,
                                               const std::unordered_map<std::string, volce::Range>& ranges,
                                               const std::optional<volce::Range>& default_range) {
    assertParsedFormulas(ctx, solver, vec);

    const auto decls = collectZeroArityDecls(ctx, vec);
    std::vector<std::string> bounded_vars;
    bounded_vars.reserve(decls.size());

    for (auto decl : decls) {
        Z3_sort sort = Z3_get_range(ctx, decl);
        unsigned bits = getBitVectorSize(ctx, sort);
        if (bits == 0 || bits > 63) {
            return std::nullopt;
        }
        const char* name = Z3_get_symbol_string(ctx, Z3_get_decl_name(ctx, decl));
        std::string nameStr = name ? name : "";
        auto rangeOpt = lookupRange(nameStr, ranges, default_range);
        if (!rangeOpt) {
            return std::nullopt;
        }
        if (rangeOpt->lower > rangeOpt->upper || !fitsSignedRange(bits, *rangeOpt)) {
            return std::nullopt;
        }
        Z3_ast var = Z3_mk_app(ctx, decl, 0, nullptr);
        assertBound(ctx, solver, var, *rangeOpt);
        bounded_vars.push_back(nameStr);
    }

    std::uint64_t count = countModels(ctx, solver, decls);
    return volce::CountResult{count, std::move(bounded_vars)};
}

}  // namespace

namespace volce {

std::optional<CountResult> countModelsFromSmt2(
    const std::string& smt2,
    const std::unordered_map<std::string, Range>& ranges,
    const std::optional<Range>& default_range) {
    if (smt2.empty()) {
        return std::nullopt;
    }

    Z3_config config = Z3_mk_config();
    Z3_context ctx = Z3_mk_context(config);
    Z3_del_config(config);

    Z3_solver solver = Z3_mk_solver(ctx);
    Z3_solver_inc_ref(ctx, solver);

    Z3_ast_vector vec = Z3_parse_smtlib2_string(ctx, smt2.c_str(), 0, nullptr, nullptr, 0, nullptr, nullptr);
    auto result = countInternal(ctx, solver, vec, ranges, default_range);

    Z3_solver_dec_ref(ctx, solver);
    Z3_del_context(ctx);

    return result;
}

std::optional<CountResult> countModelsFromSmt2File(
    const std::string& smt2_path,
    const std::unordered_map<std::string, Range>& ranges,
    const std::optional<Range>& default_range) {
    if (smt2_path.empty()) {
        return std::nullopt;
    }

    Z3_config config = Z3_mk_config();
    Z3_context ctx = Z3_mk_context(config);
    Z3_del_config(config);

    Z3_solver solver = Z3_mk_solver(ctx);
    Z3_solver_inc_ref(ctx, solver);

    Z3_ast_vector vec = Z3_parse_smtlib2_file(ctx, smt2_path.c_str(), 0, nullptr, nullptr, 0, nullptr, nullptr);
    auto result = countInternal(ctx, solver, vec, ranges, default_range);

    Z3_solver_dec_ref(ctx, solver);
    Z3_del_context(ctx);

    return result;
}

}  // namespace volce
