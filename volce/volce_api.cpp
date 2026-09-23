#include "volce/volce_api.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <map>
#include <set>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "z3.h"

namespace {

constexpr volce::Range kVolceWordRange{-8, 8};

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

void collectSelectsFromAst(Z3_context ctx,
                           Z3_ast ast,
                           std::unordered_set<unsigned>& seen,
                           std::vector<Z3_ast>& selects) {
    if (Z3_get_ast_kind(ctx, ast) != Z3_APP_AST) return;
    Z3_app app = Z3_to_app(ctx, ast);
    Z3_func_decl decl = Z3_get_app_decl(ctx, app);
    // epat++ models locals and memory in one array. Selects at numeral
    // addresses are compiler-internal local/SSA slots; bounding them to the
    // user input domain can make a valid loop infeasible once its counter is
    // greater than the configured upper bound. Project only symbolic-address
    // reads, which represent pointer dereferences or symbolic subscripts.
    const bool symbolicIndex = Z3_get_app_num_args(ctx, app) >= 2 &&
        Z3_get_ast_kind(ctx, Z3_get_app_arg(ctx, app, 1)) == Z3_APP_AST &&
        Z3_get_decl_kind(
            ctx, Z3_get_app_decl(
                ctx, Z3_to_app(ctx, Z3_get_app_arg(ctx, app, 1)))) !=
            Z3_OP_BNUM;
    if (Z3_get_decl_kind(ctx, decl) == Z3_OP_SELECT && symbolicIndex &&
        isBitVector(ctx, Z3_get_sort(ctx, ast))) {
        const unsigned id = Z3_get_ast_id(ctx, ast);
        if (seen.insert(id).second) selects.push_back(ast);
    }
    const unsigned argc = Z3_get_app_num_args(ctx, app);
    for (unsigned i = 0; i < argc; ++i) {
        collectSelectsFromAst(ctx, Z3_get_app_arg(ctx, app, i), seen, selects);
    }
}

std::vector<Z3_ast> collectBitVectorSelects(Z3_context ctx,
                                            Z3_ast_vector vec) {
    std::vector<Z3_ast> selects;
    std::unordered_set<unsigned> seen;
    const unsigned num = Z3_ast_vector_size(ctx, vec);
    for (unsigned i = 0; i < num; ++i) {
        collectSelectsFromAst(
            ctx, Z3_ast_vector_get(ctx, vec, i), seen, selects);
    }
    return selects;
}

Z3_ast findNamedArrayConstantFromAst(
    Z3_context ctx,
    Z3_ast ast,
    const std::string& expected_name,
    std::unordered_set<unsigned>& seen) {
    const unsigned ast_id = Z3_get_ast_id(ctx, ast);
    if (!seen.insert(ast_id).second) return nullptr;
    if (Z3_get_ast_kind(ctx, ast) != Z3_APP_AST) return nullptr;

    Z3_app app = Z3_to_app(ctx, ast);
    Z3_func_decl decl = Z3_get_app_decl(ctx, app);
    if (Z3_get_app_num_args(ctx, app) == 0 &&
        Z3_get_decl_kind(ctx, decl) == Z3_OP_UNINTERPRETED &&
        Z3_get_sort_kind(ctx, Z3_get_sort(ctx, ast)) == Z3_ARRAY_SORT) {
        const char* raw =
            Z3_get_symbol_string(ctx, Z3_get_decl_name(ctx, decl));
        if (raw && expected_name == raw) return ast;
    }

    const unsigned argc = Z3_get_app_num_args(ctx, app);
    for (unsigned i = 0; i < argc; ++i) {
        if (Z3_ast found = findNamedArrayConstantFromAst(
                ctx, Z3_get_app_arg(ctx, app, i), expected_name, seen)) {
            return found;
        }
    }
    return nullptr;
}

Z3_ast findNamedArrayConstant(
    Z3_context ctx,
    Z3_ast_vector vec,
    const std::string& expected_name) {
    std::unordered_set<unsigned> seen;
    const unsigned num = Z3_ast_vector_size(ctx, vec);
    for (unsigned i = 0; i < num; ++i) {
        if (Z3_ast found = findNamedArrayConstantFromAst(
                ctx, Z3_ast_vector_get(ctx, vec, i), expected_name, seen)) {
            return found;
        }
    }
    return nullptr;
}

struct DeclInfo {
    std::string name;
    unsigned bits;
};

void skipSpaceAndComments(std::string_view text, size_t& pos) {
    while (pos < text.size()) {
        char c = text[pos];
        if (std::isspace(static_cast<unsigned char>(c)) != 0) {
            ++pos;
            continue;
        }
        if (c == ';') {
            while (pos < text.size() && text[pos] != '\n') {
                ++pos;
            }
            continue;
        }
        break;
    }
}

bool consumeChar(std::string_view text, size_t& pos, char expected) {
    skipSpaceAndComments(text, pos);
    if (pos < text.size() && text[pos] == expected) {
        ++pos;
        return true;
    }
    return false;
}

bool consumeToken(std::string_view text, size_t& pos, std::string_view token) {
    skipSpaceAndComments(text, pos);
    if (text.substr(pos, token.size()) == token) {
        pos += token.size();
        return true;
    }
    return false;
}

std::optional<std::string> parseSymbol(std::string_view text, size_t& pos) {
    skipSpaceAndComments(text, pos);
    if (pos >= text.size()) {
        return std::nullopt;
    }
    if (text[pos] == '|') {
        ++pos;
        size_t start = pos;
        while (pos < text.size() && text[pos] != '|') {
            ++pos;
        }
        if (pos >= text.size()) {
            return std::nullopt;
        }
        std::string symbol(text.substr(start, pos - start));
        ++pos;
        return symbol;
    }
    size_t start = pos;
    while (pos < text.size()) {
        char c = text[pos];
        if (std::isspace(static_cast<unsigned char>(c)) != 0 || c == '(' || c == ')') {
            break;
        }
        ++pos;
    }
    if (pos == start) {
        return std::nullopt;
    }
    return std::string(text.substr(start, pos - start));
}

std::optional<unsigned> parseUnsigned(std::string_view text, size_t& pos) {
    skipSpaceAndComments(text, pos);
    size_t start = pos;
    while (pos < text.size() && std::isdigit(static_cast<unsigned char>(text[pos])) != 0) {
        ++pos;
    }
    if (pos == start) {
        return std::nullopt;
    }
    return static_cast<unsigned>(std::stoul(std::string(text.substr(start, pos - start))));
}

std::optional<unsigned> parseBitVectorSort(std::string_view text, size_t& pos) {
    if (!consumeChar(text, pos, '(')) {
        return std::nullopt;
    }
    if (!consumeToken(text, pos, "_")) {
        return std::nullopt;
    }
    if (!consumeToken(text, pos, "BitVec")) {
        return std::nullopt;
    }
    auto bits = parseUnsigned(text, pos);
    if (!bits) {
        return std::nullopt;
    }
    if (!consumeChar(text, pos, ')')) {
        return std::nullopt;
    }
    return bits;
}

std::optional<DeclInfo> parseDeclareFun(std::string_view text, size_t& pos) {
    if (!consumeChar(text, pos, '(')) {
        return std::nullopt;
    }
    if (!consumeToken(text, pos, "declare-fun")) {
        return std::nullopt;
    }
    auto name = parseSymbol(text, pos);
    if (!name) {
        return std::nullopt;
    }
    if (!consumeChar(text, pos, '(') || !consumeChar(text, pos, ')')) {
        return std::nullopt;
    }
    auto bits = parseBitVectorSort(text, pos);
    if (!bits) {
        return std::nullopt;
    }
    consumeChar(text, pos, ')');
    return DeclInfo{std::move(*name), *bits};
}

std::optional<DeclInfo> parseDeclareConst(std::string_view text, size_t& pos) {
    if (!consumeChar(text, pos, '(')) {
        return std::nullopt;
    }
    if (!consumeToken(text, pos, "declare-const")) {
        return std::nullopt;
    }
    auto name = parseSymbol(text, pos);
    if (!name) {
        return std::nullopt;
    }
    auto bits = parseBitVectorSort(text, pos);
    if (!bits) {
        return std::nullopt;
    }
    consumeChar(text, pos, ')');
    return DeclInfo{std::move(*name), *bits};
}

std::vector<DeclInfo> parseBitVectorDecls(std::string_view text) {
    std::vector<DeclInfo> decls;
    size_t pos = 0;
    while (pos < text.size()) {
        skipSpaceAndComments(text, pos);
        if (pos >= text.size()) {
            break;
        }
        if (text[pos] != '(') {
            ++pos;
            continue;
        }
        size_t probe = pos;
        if (auto decl = parseDeclareFun(text, probe)) {
            decls.push_back(std::move(*decl));
            pos = probe;
            continue;
        }
        probe = pos;
        if (auto decl = parseDeclareConst(text, probe)) {
            decls.push_back(std::move(*decl));
            pos = probe;
            continue;
        }
        ++pos;
    }
    return decls;
}

void addDeclaredBitVectors(Z3_context ctx,
                           const std::vector<DeclInfo>& parsed,
                           std::vector<Z3_func_decl>& decls) {
    std::unordered_set<std::string> seen;
    seen.reserve(decls.size() + parsed.size());
    for (auto decl : decls) {
        const char* name = Z3_get_symbol_string(ctx, Z3_get_decl_name(ctx, decl));
        if (name) {
            seen.insert(name);
        }
    }
    for (const auto& info : parsed) {
        if (!seen.insert(info.name).second) {
            continue;
        }
        Z3_sort sort = Z3_mk_bv_sort(ctx, info.bits);
        Z3_symbol symbol = Z3_mk_string_symbol(ctx, info.name.c_str());
        Z3_ast var = Z3_mk_const(ctx, symbol, sort);
        decls.push_back(Z3_get_app_decl(ctx, Z3_to_app(ctx, var)));
    }
}

std::uint64_t countModels(Z3_context ctx,
                          Z3_solver solver,
                          const std::vector<Z3_ast>& projection_terms) {
    std::uint64_t count = 0;
    while (true) {
        Z3_lbool status = Z3_solver_check(ctx, solver);
        if (status != Z3_L_TRUE) {
            break;
        }
        Z3_model model = Z3_solver_get_model(ctx, solver);
        if (!model) {
            break;
        }
        Z3_model_inc_ref(ctx, model);
        std::vector<Z3_ast> equalities;
        equalities.reserve(projection_terms.size());
        for (Z3_ast var : projection_terms) {
            Z3_ast value = nullptr;
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

// Enumerate bounded projections with one small exclusion set per term. The
// flat blocking scheme above retains one assertion for every complete model;
// array regions can produce thousands of models and a growing solver state.
std::uint64_t countModelsByProjection(Z3_context ctx, Z3_solver solver,
                                      const std::vector<Z3_ast>& terms,
                                      std::size_t depth) {
    if (depth == terms.size())
        return Z3_solver_check(ctx, solver) == Z3_L_TRUE ? 1 : 0;

    Z3_solver_push(ctx, solver);
    std::uint64_t count = 0;
    while (Z3_solver_check(ctx, solver) == Z3_L_TRUE) {
        Z3_model model = Z3_solver_get_model(ctx, solver);
        if (!model) break;
        Z3_model_inc_ref(ctx, model);
        Z3_ast value = nullptr;
        const bool evaluated =
            Z3_model_eval(ctx, model, terms[depth], true, &value);
        if (!evaluated || !value) {
            Z3_model_dec_ref(ctx, model);
            break;
        }
        // Keep the evaluated value alive across model release and recursive
        // solver calls. A solver frame also bounds the sibling exclusions.
        Z3_inc_ref(ctx, value);
        Z3_model_dec_ref(ctx, model);
        Z3_ast equals = Z3_mk_eq(ctx, terms[depth], value);
        Z3_inc_ref(ctx, equals);
        Z3_solver_push(ctx, solver);
        Z3_solver_assert(ctx, solver, equals);
        count += countModelsByProjection(ctx, solver, terms, depth + 1);
        Z3_solver_pop(ctx, solver, 1);
        Z3_solver_assert(ctx, solver, Z3_mk_not(ctx, equals));
        Z3_dec_ref(ctx, equals);
        Z3_dec_ref(ctx, value);
    }
    Z3_solver_pop(ctx, solver, 1);
    return count;
}


class ProjectionDisjointSet {
public:
    explicit ProjectionDisjointSet(std::size_t initial) {
        parent_.reserve(initial);
        rank_.reserve(initial);
        for (std::size_t i = 0; i < initial; ++i) {
            parent_.push_back(i);
            rank_.push_back(0);
        }
    }

    std::size_t addNode() {
        const std::size_t id = parent_.size();
        parent_.push_back(id);
        rank_.push_back(0);
        return id;
    }

    std::size_t find(std::size_t node) {
        if (parent_[node] != node)
            parent_[node] = find(parent_[node]);
        return parent_[node];
    }

    void unite(std::size_t lhs, std::size_t rhs) {
        lhs = find(lhs);
        rhs = find(rhs);
        if (lhs == rhs) return;
        if (rank_[lhs] < rank_[rhs]) std::swap(lhs, rhs);
        parent_[rhs] = lhs;
        if (rank_[lhs] == rank_[rhs]) ++rank_[lhs];
    }

private:
    std::vector<std::size_t> parent_;
    std::vector<unsigned> rank_;
};

struct SelectDependency {
    std::size_t node{0};
    Z3_ast select{nullptr};
    Z3_ast array{nullptr};
    Z3_ast address{nullptr};
};

struct ProjectionFactorization {
    std::vector<std::vector<Z3_ast>> components;
};

std::uint64_t dependencyKey(unsigned kind, unsigned ast_id) {
    return (static_cast<std::uint64_t>(kind) << 32) |
           static_cast<std::uint64_t>(ast_id);
}

bool isPlainArrayConstant(Z3_context ctx, Z3_ast ast) {
    if (Z3_get_ast_kind(ctx, ast) != Z3_APP_AST) return false;
    Z3_app app = Z3_to_app(ctx, ast);
    Z3_func_decl decl = Z3_get_app_decl(ctx, app);
    return Z3_get_app_num_args(ctx, app) == 0 &&
           Z3_get_decl_kind(ctx, decl) == Z3_OP_UNINTERPRETED &&
           Z3_get_sort_kind(ctx, Z3_get_sort(ctx, ast)) == Z3_ARRAY_SORT;
}

std::size_t getAuxDependencyNode(
    ProjectionDisjointSet& dsu,
    std::unordered_map<std::uint64_t, std::size_t>& aux_nodes,
    unsigned kind,
    unsigned ast_id) {
    const auto key = dependencyKey(kind, ast_id);
    auto it = aux_nodes.find(key);
    if (it != aux_nodes.end()) return it->second;
    const auto node = dsu.addNode();
    aux_nodes.emplace(key, node);
    return node;
}

void rememberSelectDependency(
    Z3_context ctx,
    Z3_ast ast,
    std::size_t node,
    std::unordered_map<unsigned, std::size_t>& seen_selects,
    std::vector<SelectDependency>& selects,
    bool& unsafe) {
    if (Z3_get_ast_kind(ctx, ast) != Z3_APP_AST) return;
    Z3_app app = Z3_to_app(ctx, ast);
    if (Z3_get_decl_kind(ctx, Z3_get_app_decl(ctx, app)) != Z3_OP_SELECT ||
        Z3_get_app_num_args(ctx, app) < 2) {
        return;
    }
    Z3_ast array = Z3_get_app_arg(ctx, app, 0);
    if (!isPlainArrayConstant(ctx, array)) {
        // Store chains and array-valued expressions can couple otherwise
        // distinct cells; keep the existing monolithic enumeration.
        unsafe = true;
        return;
    }
    const unsigned id = Z3_get_ast_id(ctx, ast);
    if (seen_selects.emplace(id, node).second) {
        selects.push_back(
            SelectDependency{node, ast, array, Z3_get_app_arg(ctx, app, 1)});
    }
}

std::optional<std::size_t> lookupProjectionNode(
    Z3_context ctx,
    Z3_ast ast,
    const std::unordered_map<unsigned, std::size_t>& projection_by_ast,
    const std::unordered_map<std::string, std::size_t>& projection_by_text) {
    auto by_id = projection_by_ast.find(Z3_get_ast_id(ctx, ast));
    if (by_id != projection_by_ast.end()) return by_id->second;
    const char* raw = Z3_ast_to_string(ctx, ast);
    if (!raw) return std::nullopt;
    auto by_text = projection_by_text.find(raw);
    if (by_text == projection_by_text.end() ||
        by_text->second == std::numeric_limits<std::size_t>::max()) {
        return std::nullopt;
    }
    return by_text->second;
}

void collectProjectionDependencies(
    Z3_context ctx,
    Z3_ast ast,
    const std::unordered_map<unsigned, std::size_t>& projection_by_ast,
    const std::unordered_map<std::string, std::size_t>& projection_by_text,
    ProjectionDisjointSet& dsu,
    std::unordered_map<std::uint64_t, std::size_t>& aux_nodes,
    std::unordered_map<unsigned, std::size_t>& seen_selects,
    std::vector<SelectDependency>& selects,
    std::vector<std::size_t>& nodes,
    bool& unsafe) {
    const unsigned ast_id = Z3_get_ast_id(ctx, ast);
    if (auto projected = lookupProjectionNode(
            ctx, ast, projection_by_ast, projection_by_text)) {
        nodes.push_back(*projected);
        rememberSelectDependency(
            ctx, ast, *projected, seen_selects, selects, unsafe);
        return;
    }

    const Z3_ast_kind ast_kind = Z3_get_ast_kind(ctx, ast);
    if (ast_kind == Z3_VAR_AST || ast_kind == Z3_QUANTIFIER_AST) {
        unsafe = true;
        return;
    }
    if (ast_kind != Z3_APP_AST) return;

    Z3_app app = Z3_to_app(ctx, ast);
    Z3_func_decl decl = Z3_get_app_decl(ctx, app);
    const Z3_decl_kind decl_kind = Z3_get_decl_kind(ctx, decl);
    const unsigned argc = Z3_get_app_num_args(ctx, app);

    if (decl_kind == Z3_OP_STORE) {
        unsafe = true;
        return;
    }
    if (decl_kind == Z3_OP_SELECT) {
        const auto node = getAuxDependencyNode(
            dsu, aux_nodes, 1, ast_id);
        nodes.push_back(node);
        rememberSelectDependency(
            ctx, ast, node, seen_selects, selects, unsafe);
        return;
    }

    if (decl_kind == Z3_OP_UNINTERPRETED) {
        if (argc != 0) {
            unsafe = true;
            return;
        }
        const Z3_sort_kind sort_kind =
            Z3_get_sort_kind(ctx, Z3_get_sort(ctx, ast));
        if (sort_kind == Z3_BV_SORT) {
            nodes.push_back(getAuxDependencyNode(
                dsu, aux_nodes, 2, ast_id));
        } else if (sort_kind == Z3_ARRAY_SORT) {
            // A raw array value outside select() can express extensional
            // relations across many cells, so it is not separable here.
            unsafe = true;
        }
        return;
    }

    for (unsigned i = 0; i < argc; ++i) {
        collectProjectionDependencies(
            ctx, Z3_get_app_arg(ctx, app, i), projection_by_ast,
            projection_by_text, dsu, aux_nodes, seen_selects, selects, nodes,
            unsafe);
    }
}

void collectAddressDependencies(
    Z3_context ctx,
    Z3_ast ast,
    const std::unordered_map<unsigned, std::size_t>& projection_by_ast,
    const std::unordered_map<std::string, std::size_t>& projection_by_text,
    ProjectionDisjointSet& dsu,
    std::unordered_map<std::uint64_t, std::size_t>& aux_nodes,
    std::vector<std::size_t>& nodes,
    bool& unsafe) {
    const unsigned ast_id = Z3_get_ast_id(ctx, ast);
    if (auto projected = lookupProjectionNode(
            ctx, ast, projection_by_ast, projection_by_text)) {
        nodes.push_back(*projected);
        return;
    }
    const Z3_ast_kind ast_kind = Z3_get_ast_kind(ctx, ast);
    if (ast_kind == Z3_VAR_AST || ast_kind == Z3_QUANTIFIER_AST) {
        unsafe = true;
        return;
    }
    if (ast_kind != Z3_APP_AST) return;
    Z3_app app = Z3_to_app(ctx, ast);
    Z3_func_decl decl = Z3_get_app_decl(ctx, app);
    const Z3_decl_kind decl_kind = Z3_get_decl_kind(ctx, decl);
    const unsigned argc = Z3_get_app_num_args(ctx, app);
    if (decl_kind == Z3_OP_SELECT || decl_kind == Z3_OP_STORE) {
        unsafe = true;
        return;
    }
    if (decl_kind == Z3_OP_UNINTERPRETED) {
        if (argc == 0 &&
            Z3_get_sort_kind(ctx, Z3_get_sort(ctx, ast)) == Z3_BV_SORT) {
            nodes.push_back(getAuxDependencyNode(
                dsu, aux_nodes, 2, ast_id));
        } else if (argc != 0) {
            unsafe = true;
        }
        return;
    }
    for (unsigned i = 0; i < argc; ++i) {
        collectAddressDependencies(
            ctx, Z3_get_app_arg(ctx, app, i), projection_by_ast,
            projection_by_text, dsu, aux_nodes, nodes, unsafe);
    }
}

bool mayAliasSelects(
    Z3_context ctx,
    Z3_solver solver,
    const SelectDependency& lhs,
    const SelectDependency& rhs) {
    if (!Z3_is_eq_ast(ctx, lhs.array, rhs.array)) return false;
    if (Z3_is_eq_ast(ctx, lhs.address, rhs.address)) return true;
    Z3_solver_push(ctx, solver);
    Z3_solver_assert(ctx, solver, Z3_mk_eq(ctx, lhs.address, rhs.address));
    const Z3_lbool status = Z3_solver_check(ctx, solver);
    Z3_solver_pop(ctx, solver, 1);
    // UNKNOWN is conservatively treated as possible aliasing.
    return status != Z3_L_FALSE;
}

std::optional<ProjectionFactorization> buildProjectionFactorization(
    Z3_context ctx,
    Z3_solver solver,
    const std::vector<Z3_ast>& projection_terms) {
    if (projection_terms.size() < 2) return std::nullopt;

    ProjectionDisjointSet dsu(projection_terms.size());
    std::unordered_map<unsigned, std::size_t> projection_by_ast;
    std::unordered_map<std::string, std::size_t> projection_by_text;
    projection_by_ast.reserve(projection_terms.size());
    projection_by_text.reserve(projection_terms.size());
    for (std::size_t i = 0; i < projection_terms.size(); ++i) {
        projection_by_ast.emplace(
            Z3_get_ast_id(ctx, projection_terms[i]), i);
        const char* raw = Z3_ast_to_string(ctx, projection_terms[i]);
        if (!raw) continue;
        auto inserted = projection_by_text.emplace(raw, i);
        if (!inserted.second && inserted.first->second != i) {
            // Printed-expression matching is only a fallback across Z3
            // simplification. If two distinct projections print identically,
            // refuse to use the textual key instead of guessing.
            inserted.first->second = std::numeric_limits<std::size_t>::max();
        }
    }

    std::unordered_map<std::uint64_t, std::size_t> aux_nodes;
    std::unordered_map<unsigned, std::size_t> seen_selects;
    std::vector<SelectDependency> selects;
    bool unsafe = false;

    Z3_ast_vector assertions = Z3_solver_get_assertions(ctx, solver);
    Z3_ast_vector_inc_ref(ctx, assertions);
    const unsigned assertion_count = Z3_ast_vector_size(ctx, assertions);
    for (unsigned i = 0; i < assertion_count && !unsafe; ++i) {
        std::vector<std::size_t> nodes;
        collectProjectionDependencies(
            ctx, Z3_ast_vector_get(ctx, assertions, i), projection_by_ast,
            projection_by_text, dsu, aux_nodes, seen_selects, selects, nodes,
            unsafe);
        if (!nodes.empty()) {
            const auto first = nodes.front();
            for (std::size_t j = 1; j < nodes.size(); ++j)
                dsu.unite(first, nodes[j]);
        }
    }
    Z3_ast_vector_dec_ref(ctx, assertions);
    if (unsafe) return std::nullopt;

    // Keep the proof cost bounded. Larger memory projections retain the
    // existing exact enumerator until a cheaper alias analysis is available.
    if (selects.size() > 64) return std::nullopt;

    for (std::size_t i = 0; i < selects.size() && !unsafe; ++i) {
        for (std::size_t j = i + 1; j < selects.size(); ++j) {
            if (!mayAliasSelects(ctx, solver, selects[i], selects[j]))
                continue;
            dsu.unite(selects[i].node, selects[j].node);
            std::vector<std::size_t> address_nodes;
            collectAddressDependencies(
                ctx, selects[i].address, projection_by_ast,
                projection_by_text, dsu, aux_nodes, address_nodes, unsafe);
            collectAddressDependencies(
                ctx, selects[j].address, projection_by_ast,
                projection_by_text, dsu, aux_nodes, address_nodes, unsafe);
            for (auto node : address_nodes) {
                dsu.unite(selects[i].node, node);
                dsu.unite(selects[j].node, node);
            }
            if (unsafe) break;
        }
    }
    if (unsafe) return std::nullopt;

    std::unordered_map<std::size_t, std::size_t> component_index;
    ProjectionFactorization result;
    for (std::size_t i = 0; i < projection_terms.size(); ++i) {
        const auto root = dsu.find(i);
        auto inserted = component_index.emplace(
            root, result.components.size());
        if (inserted.second)
            result.components.emplace_back();
        result.components[inserted.first->second].push_back(
            projection_terms[i]);
    }
    if (result.components.size() <= 1) return std::nullopt;
    return result;
}

std::optional<std::uint64_t> countFactoredProjection(
    Z3_context ctx,
    Z3_solver solver,
    const ProjectionFactorization& factorization) {
    std::uint64_t product = 1;
    for (const auto& component : factorization.components) {
        Z3_solver_push(ctx, solver);
        const std::uint64_t component_count = component.size() >= 5
            ? countModelsByProjection(ctx, solver, component, 0)
            : countModels(ctx, solver, component);
        Z3_solver_pop(ctx, solver, 1);
        if (component_count == 0) return std::uint64_t{0};
        if (product > std::numeric_limits<std::uint64_t>::max() /
                          component_count) {
            return std::nullopt;
        }
        product *= component_count;
    }
    return product;
}

std::optional<volce::Range> lookupRange(const std::string& name,
                                       const std::unordered_map<std::string, volce::Range>& ranges,
                                       const std::optional<volce::Range>& default_range) {
    auto it = ranges.find(name);
    if (it != ranges.end()) {
        return it->second;
    }
    if (default_range) {
        return default_range;
    }
    return kVolceWordRange;
}

bool isDerivedSsaStateName(const std::string& name) {
    // epat++ materializes source writes with this suffix.  These declarations
    // are deterministic functions of source inputs, so projecting them would
    // multiply the apparent solution space instead of adding information.
    return name.find("#ssa") != std::string::npos;
}

bool isSummaryCandidateName(const std::string& declared,
                            const std::string& source) {
    if (declared == source) return true;
    if (declared.size() <= source.size() ||
        declared.compare(0, source.size(), source) != 0) return false;
    const char separator = declared[source.size()];
    return separator == '@' || separator == '!' || separator == '#' ||
           separator == '$' || separator == '_';
}

void applyEntailedStateSummaries(
    Z3_context ctx,
    Z3_solver solver,
    const std::vector<Z3_func_decl>& decls,
    const std::vector<volce::AffineStateSummary>& summaries,
    std::vector<std::string>& applied,
    std::vector<std::string>& validated_ground,
    std::vector<std::string>& rejected,
    bool apply_entailed_summaries) {
    for (const auto& summary : summaries) {
        bool accepted = false;
        for (auto decl : decls) {
            const char* rawName =
                Z3_get_symbol_string(ctx, Z3_get_decl_name(ctx, decl));
            const std::string name = rawName ? rawName : "";
            if (!isSummaryCandidateName(name, summary.variable)) continue;

            Z3_ast var = Z3_mk_app(ctx, decl, 0, nullptr);
            Z3_ast value =
                Z3_mk_int64(ctx, summary.final_value, Z3_get_range(ctx, decl));
            Z3_ast equality = Z3_mk_eq(ctx, var, value);

            Z3_solver_push(ctx, solver);
            Z3_solver_assert(ctx, solver, Z3_mk_not(ctx, equality));
            const Z3_lbool check = Z3_solver_check(ctx, solver);
            Z3_solver_pop(ctx, solver, 1);
            if (check == Z3_L_FALSE) {
                if (apply_entailed_summaries) {
                    Z3_solver_assert(ctx, solver, equality);
                }
                applied.push_back(summary.variable + "->" + name + "=" +
                                  std::to_string(summary.final_value));
                accepted = true;
                break;
            }
        }
        if (!accepted) {
            // epat++ commonly substitutes a constant induction variable away,
            // leaving no source/SSA declaration to bind. Preserve the closed
            // transition explicitly as a ground 32-bit bit-vector equality.
            // This records the summarized transition without introducing a
            // model-count dimension.
            Z3_sort sort = Z3_mk_bv_sort(ctx, 32);
            Z3_ast initial = Z3_mk_int64(ctx, summary.initial_value, sort);
            Z3_ast step = Z3_mk_int64(ctx, summary.step, sort);
            Z3_ast iterations = Z3_mk_int64(ctx, summary.iterations, sort);
            Z3_ast product = Z3_mk_bvmul(ctx, step, iterations);
            Z3_ast closedForm = Z3_mk_bvadd(ctx, initial, product);
            Z3_ast finalValue = Z3_mk_int64(ctx, summary.final_value, sort);
            Z3_ast equality = Z3_mk_eq(ctx, finalValue, closedForm);

            Z3_solver_push(ctx, solver);
            Z3_solver_assert(ctx, solver, Z3_mk_not(ctx, equality));
            const Z3_lbool groundCheck = Z3_solver_check(ctx, solver);
            Z3_solver_pop(ctx, solver, 1);
            if (groundCheck == Z3_L_FALSE) {
                if (apply_entailed_summaries) {
                    Z3_solver_assert(ctx, solver, equality);
                }
                validated_ground.push_back(summary.variable +
                    "->constant-folded=" +
                    std::to_string(summary.final_value));
                accepted = true;
            }
        }
        if (!accepted) {
            rejected.push_back(summary.variable + "=" +
                               std::to_string(summary.final_value) +
                               ": closed-form identity is inconsistent");
        }
    }
}

struct SsaRelationState {
    Z3_func_decl decl{nullptr};
    std::string name;
    std::string prefix;
    unsigned version{0};
};

std::optional<SsaRelationState> parseSsaRelationState(
    Z3_context ctx,
    Z3_func_decl decl,
    const std::string& source) {
    const char* rawName =
        Z3_get_symbol_string(ctx, Z3_get_decl_name(ctx, decl));
    const std::string name = rawName ? rawName : "";
    if (!isSummaryCandidateName(name, source)) return std::nullopt;
    const auto marker = name.rfind("#ssa");
    if (marker == std::string::npos || marker + 4 >= name.size())
        return std::nullopt;
    unsigned version = 0;
    for (std::size_t i = marker + 4; i < name.size(); ++i) {
        const unsigned char ch = static_cast<unsigned char>(name[i]);
        if (!std::isdigit(ch)) return std::nullopt;
        const unsigned digit = static_cast<unsigned>(ch - '0');
        if (version > (std::numeric_limits<unsigned>::max() - digit) / 10)
            return std::nullopt;
        version = version * 10 + digit;
    }
    return SsaRelationState{
        decl, name, name.substr(0, marker), version};
}

void applyEntailedAffineRelations(
    Z3_context ctx,
    Z3_solver solver,
    const std::vector<Z3_func_decl>& decls,
    const std::vector<volce::AffineRelationSummary>& summaries,
    std::vector<std::string>& applied,
    std::vector<std::string>& rejected,
    bool apply_entailed_summaries) {
    for (const auto& summary : summaries) {
        std::unordered_map<std::string, std::vector<SsaRelationState>> groups;
        for (auto decl : decls) {
            auto state = parseSsaRelationState(
                ctx, decl, summary.variable);
            if (!state) continue;
            groups[state->prefix].push_back(std::move(*state));
        }

        if (groups.size() != 1) {
            rejected.push_back(
                summary.variable +
                ": expected exactly one SSA scope for affine relation");
            continue;
        }
        auto& states = groups.begin()->second;
        std::sort(
            states.begin(), states.end(),
            [](const SsaRelationState& lhs,
               const SsaRelationState& rhs) {
                return lhs.version < rhs.version;
            });
        if (states.size() < 2 || states.front().version != 0 ||
            states.front().version == states.back().version) {
            rejected.push_back(
                summary.variable +
                ": affine relation requires SSA entry #ssa0 and a later exit");
            continue;
        }

        Z3_ast entry = Z3_mk_app(ctx, states.front().decl, 0, nullptr);
        Z3_ast exit = Z3_mk_app(ctx, states.back().decl, 0, nullptr);
        Z3_sort entrySort = Z3_get_sort(ctx, entry);
        Z3_sort exitSort = Z3_get_sort(ctx, exit);
        if (!Z3_is_eq_sort(ctx, entrySort, exitSort) ||
            !isBitVector(ctx, entrySort)) {
            rejected.push_back(
                summary.variable +
                ": affine relation SSA endpoints have incompatible sorts");
            continue;
        }

        Z3_ast scale =
            Z3_mk_int64(ctx, summary.scale, entrySort);
        Z3_ast offset =
            Z3_mk_int64(ctx, summary.offset, entrySort);
        Z3_ast scaled = summary.scale == 1
            ? entry
            : (summary.scale == 0
                ? Z3_mk_int64(ctx, 0, entrySort)
                : Z3_mk_bvmul(ctx, entry, scale));
        Z3_ast rhs = summary.offset == 0
            ? scaled
            : Z3_mk_bvadd(ctx, scaled, offset);
        Z3_ast equality = Z3_mk_eq(ctx, exit, rhs);

        Z3_solver_push(ctx, solver);
        Z3_solver_assert(ctx, solver, Z3_mk_not(ctx, equality));
        const Z3_lbool check = Z3_solver_check(ctx, solver);
        Z3_solver_pop(ctx, solver, 1);

        if (check == Z3_L_FALSE) {
            if (apply_entailed_summaries) {
                Z3_solver_assert(ctx, solver, equality);
            }
            applied.push_back(
                summary.variable + ":" +
                states.front().name + "->" + states.back().name +
                " scale=" + std::to_string(summary.scale) +
                " offset=" + std::to_string(summary.offset));
        } else {
            rejected.push_back(
                summary.variable + ":" +
                states.front().name + "->" + states.back().name +
                ": path formula does not entail affine relation");
        }
    }
}


// A definition (x = expression) of an unprojected SSA state can be
// existentially eliminated by substituting expression for x everywhere.
// Restrict this to the declaration scope of an entailed loop summary.
bool isNamedState(Z3_context ctx, Z3_ast ast, const std::string& prefix) {
    if (Z3_get_ast_kind(ctx, ast) != Z3_APP_AST) return false;
    Z3_app app = Z3_to_app(ctx, ast);
    Z3_func_decl decl = Z3_get_app_decl(ctx, app);
    if (Z3_get_app_num_args(ctx, app) != 0 ||
        Z3_get_decl_kind(ctx, decl) != Z3_OP_UNINTERPRETED) return false;
    const char* raw = Z3_get_symbol_string(ctx, Z3_get_decl_name(ctx, decl));
    return raw && std::string(raw).compare(0, prefix.size(), prefix) == 0;
}

bool containsAst(Z3_context ctx, Z3_ast tree, Z3_ast target) {
    if (Z3_is_eq_ast(ctx, tree, target)) return true;
    if (Z3_get_ast_kind(ctx, tree) != Z3_APP_AST) return false;
    Z3_app app = Z3_to_app(ctx, tree);
    for (unsigned i = 0; i < Z3_get_app_num_args(ctx, app); ++i)
        if (containsAst(ctx, Z3_get_app_arg(ctx, app, i), target)) return true;
    return false;
}

std::size_t eliminateEntailedSsaDefinitions(
    Z3_context ctx, Z3_solver solver,
    std::vector<Z3_ast>& projection_terms,
    const std::vector<std::string>& applied,
    const std::vector<std::string>& applied_affine_relations,
    bool enabled,
    Z3_ast_vector retained) {
    std::unordered_set<std::string> prefixes;
    if (enabled) {
        for (const auto& item : applied) {
            const auto arrow = item.find("->");
            const auto equal = item.find('=', arrow == std::string::npos ? 0 : arrow + 2);
            if (arrow == std::string::npos || equal == std::string::npos) continue;
            const std::string name = item.substr(arrow + 2, equal - arrow - 2);
            const auto suffix = name.rfind("#ssa");
            if (suffix != std::string::npos)
                prefixes.insert(name.substr(0, suffix + 4));
        }
        for (const auto& item : applied_affine_relations) {
            const auto colon = item.find(':');
            const auto arrow = item.find("->", colon == std::string::npos ? 0 : colon + 1);
            if (colon == std::string::npos || arrow == std::string::npos)
                continue;
            const std::string entry =
                item.substr(colon + 1, arrow - colon - 1);
            const auto suffix = entry.rfind("#ssa");
            if (suffix != std::string::npos)
                prefixes.insert(entry.substr(0, suffix + 4));
        }
    }

    Z3_ast_vector original = Z3_solver_get_assertions(ctx, solver);
    Z3_ast_vector_inc_ref(ctx, original);
    std::vector<Z3_ast> assertions;
    const unsigned count = Z3_ast_vector_size(ctx, original);
    assertions.reserve(count);
    for (unsigned i = 0; i < count; ++i)
        assertions.push_back(Z3_ast_vector_get(ctx, original, i));

    std::unordered_set<unsigned> eliminated;
    std::size_t removed = 0;
    // This bounded pass avoids expression blow-up on long symbolic loops.
    for (std::size_t i = 0; enabled && i < assertions.size() && removed < 64; ++i) {
        Z3_ast formula = assertions[i];
        if (Z3_get_ast_kind(ctx, formula) != Z3_APP_AST) continue;
        Z3_app eq = Z3_to_app(ctx, formula);
        if (Z3_get_decl_kind(ctx, Z3_get_app_decl(ctx, eq)) != Z3_OP_EQ ||
            Z3_get_app_num_args(ctx, eq) != 2) continue;
        Z3_ast left = Z3_get_app_arg(ctx, eq, 0);
        Z3_ast right = Z3_get_app_arg(ctx, eq, 1);
        Z3_ast state = nullptr;
        Z3_ast value = nullptr;
        for (const auto& prefix : prefixes) {
            if (isNamedState(ctx, left, prefix) &&
                !containsAst(ctx, right, left)) {
                state = left; value = right; break;
            }
            if (isNamedState(ctx, right, prefix) &&
                !containsAst(ctx, left, right)) {
                state = right; value = left; break;
            }
        }
        if (!state) continue;
        const unsigned id = Z3_get_ast_id(ctx, state);
        if (!eliminated.insert(id).second) continue;
        for (std::size_t j = 0; j < assertions.size(); ++j) {
            if (j == i) continue;
            if (!assertions[j]) continue;
            assertions[j] = Z3_substitute(ctx, assertions[j], 1, &state, &value);
            Z3_ast_vector_push(ctx, retained, assertions[j]);
        }
        for (auto& term : projection_terms) {
            term = Z3_substitute(ctx, term, 1, &state, &value);
            Z3_ast_vector_push(ctx, retained, term);
        }
        assertions[i] = nullptr;
        ++removed;
    }

    // Recreate both solvers, including validation-only baseline, to keep
    // solver initialization comparable in the model-count phase.
    Z3_solver_reset(ctx, solver);
    std::size_t remaining = 0;
    for (Z3_ast assertion : assertions) {
        if (!assertion) continue;
        assertion = Z3_simplify(ctx, assertion);
        if (Z3_get_bool_value(ctx, assertion) == Z3_L_TRUE) continue;
        Z3_solver_assert(ctx, solver, assertion);
        ++remaining;
    }
    Z3_ast_vector_dec_ref(ctx, original);
    return remaining;
}

std::optional<volce::CountResult> countInternal(Z3_context ctx,
                                               Z3_solver solver,
                                               Z3_ast_vector vec,
                                               const std::vector<DeclInfo>& parsed_decls,
                                               const std::vector<volce::AffineStateSummary>& summaries,
                                               const std::vector<volce::AffineRelationSummary>& affine_relations,
                                               const std::unordered_map<std::string, volce::Range>& ranges,
                                               const std::optional<volce::Range>& default_range,
                                               bool include_memory_terms,
                                               const std::vector<volce::MemoryRegionProjection>& memory_regions,
                                               bool apply_entailed_summaries) {
    assertParsedFormulas(ctx, solver, vec);
    const std::size_t formula_assertions =
        static_cast<std::size_t>(Z3_ast_vector_size(ctx, vec));

    auto decls = collectZeroArityDecls(ctx, vec);
    addDeclaredBitVectors(ctx, parsed_decls, decls);
    auto memory_terms = include_memory_terms && memory_regions.empty()
        ? collectBitVectorSelects(ctx, vec) : std::vector<Z3_ast>{};
    std::vector<Z3_ast> projection_terms;
    projection_terms.reserve(decls.size() + memory_terms.size());
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
        if (isDerivedSsaStateName(nameStr)) {
            // Keep the declaration and its defining equality in the solver so
            // summaries can bind to it, but do not count a derived SSA state
            // as an independent input dimension.
            continue;
        }
        auto rangeOpt = lookupRange(nameStr, ranges, default_range);
        if (!rangeOpt) {
            return std::nullopt;
        }
        if (rangeOpt->lower > rangeOpt->upper || !fitsSignedRange(bits, *rangeOpt)) {
            return std::nullopt;
        }
        Z3_ast var = Z3_mk_app(ctx, decl, 0, nullptr);
        assertBound(ctx, solver, var, *rangeOpt);
        projection_terms.push_back(var);
        bounded_vars.push_back(nameStr);
    }

    if (include_memory_terms && !memory_regions.empty()) {
        Z3_sort word = Z3_mk_bv_sort(ctx, 32);
        Z3_sort memory_sort = Z3_mk_array_sort(ctx, word, word);
        // Reuse the array declaration parsed from the path formula whenever
        // it is present. Creating another constant with the same printed
        // symbol produces a distinct Z3 declaration, which would disconnect
        // canonical projections from constraints on epat++'s %a memory.
        Z3_ast memory = findNamedArrayConstant(ctx, vec, "%a");
        if (!memory) {
            memory = Z3_mk_const(
                ctx, Z3_mk_string_symbol(ctx, "%a"), memory_sort);
        }
        std::unordered_set<unsigned> seen_memory_terms;
        std::size_t fallback_base = 0;
        for (const auto& region : memory_regions) {
            Z3_ast base = nullptr;
            for (auto decl : decls) {
                const char* raw = Z3_get_symbol_string(
                    ctx, Z3_get_decl_name(ctx, decl));
                const std::string name = raw ? raw : "";
                if (isSummaryCandidateName(name, region.source_name)) {
                    base = Z3_mk_app(ctx, decl, 0, nullptr);
                    break;
                }
            }
            if (!base) {
                base = Z3_mk_int64(
                    ctx, static_cast<std::int64_t>(fallback_base), word);
            }
            for (std::size_t cell = 0; cell < region.cells; ++cell) {
                Z3_ast offset = Z3_mk_int64(
                    ctx, static_cast<std::int64_t>(cell), word);
                Z3_ast address = cell == 0
                    ? base : Z3_mk_bvadd(ctx, base, offset);
                Z3_ast term = Z3_mk_select(ctx, memory, address);
                if (seen_memory_terms.insert(Z3_get_ast_id(ctx, term)).second) {
                    memory_terms.push_back(term);
                }
            }
            fallback_base += std::max<std::size_t>(region.cells, 1);
        }
    }

    std::vector<std::string> bounded_memory_terms;
    bounded_memory_terms.reserve(memory_terms.size());
    for (Z3_ast term : memory_terms) {
        Z3_sort sort = Z3_get_sort(ctx, term);
        const unsigned bits = getBitVectorSize(ctx, sort);
        if (bits == 0 || bits > 63) return std::nullopt;
        const auto rangeOpt = lookupRange("%memory", ranges, default_range);
        if (!rangeOpt || rangeOpt->lower > rangeOpt->upper ||
            !fitsSignedRange(bits, *rangeOpt)) {
            return std::nullopt;
        }
        assertBound(ctx, solver, term, *rangeOpt);
        projection_terms.push_back(term);
        bounded_memory_terms.push_back(
            "select#" + std::to_string(Z3_get_ast_id(ctx, term)));
    }

    std::vector<std::string> applied;
    std::vector<std::string> validated_ground;
    std::vector<std::string> rejected;
    std::vector<std::string> applied_affine_relations;
    std::vector<std::string> rejected_affine_relations;

    // Both summary and baseline modes receive the same initial solver check.
    // Without this control, summary entailment checks warm Z3's internal state
    // and make the following model-count phase look artificially faster.
    const auto warmup_start = std::chrono::steady_clock::now();
    (void)Z3_solver_check(ctx, solver);
    const auto warmup_end = std::chrono::steady_clock::now();

    const auto summary_start = std::chrono::steady_clock::now();
    applyEntailedStateSummaries(
        ctx, solver, decls, summaries, applied, validated_ground, rejected,
        apply_entailed_summaries);
    applyEntailedAffineRelations(
        ctx, solver, decls, affine_relations,
        applied_affine_relations, rejected_affine_relations,
        apply_entailed_summaries);

    Z3_ast_vector retained = Z3_mk_ast_vector(ctx);
    Z3_ast_vector_inc_ref(ctx, retained);
    const std::size_t counting_assertions =
        eliminateEntailedSsaDefinitions(
            ctx, solver, projection_terms, applied, applied_affine_relations,
            apply_entailed_summaries, retained);

    // The rebuilt solver simplifies assertions, including canonical memory
    // addresses such as (bvadd 0 1) -> 1. Normalize projection terms in the
    // same way so dependency matching and alias checks refer to the same cell
    // expressions after reconstruction.
    for (auto& term : projection_terms) {
        term = Z3_simplify(ctx, term);
        Z3_ast_vector_push(ctx, retained, term);
    }

    // Factor only after semantics-preserving SSA elimination and solver
    // reconstruction. The reduced solver is equivalent over the remaining
    // projected terms, while transient store/SSA structure that no longer
    // constrains those terms has been removed. Building the dependency graph
    // on the pre-elimination formula was overly conservative and prevented
    // real read-only array cases from using factorization even when the
    // counting formula had become a conjunction of independent bounds.
    std::optional<ProjectionFactorization> proven_factorization;
    if (bounded_memory_terms.size() >= 5) {
        proven_factorization =
            buildProjectionFactorization(ctx, solver, projection_terms);
    }
    const auto summary_end = std::chrono::steady_clock::now();

    // Both modes start enumeration from a freshly constructed solver.
    const auto count_warmup_start = std::chrono::steady_clock::now();
    (void)Z3_solver_check(ctx, solver);
    const auto count_warmup_end = std::chrono::steady_clock::now();

    const auto count_start = std::chrono::steady_clock::now();
    std::size_t factored_projection_components = 0;
    std::uint64_t count = 0;
    bool used_factorization = false;

    // A conjunction can be counted component-wise only when every projected
    // term was proved disconnected in the complete pre-elimination formula.
    // Unsupported memory operations and ambiguous aliasing make that proof
    // fail and retain exact monolithic counting.
    if (proven_factorization) {
        if (auto factored =
                countFactoredProjection(ctx, solver, *proven_factorization)) {
            count = *factored;
            factored_projection_components =
                proven_factorization->components.size();
            used_factorization = true;
        }
    }

    if (!used_factorization) {
        // Retain the bounded recursive enumerator for one small canonical
        // region. It keeps solver state bounded even when the component proof
        // cannot separate the formula.
        count = memory_regions.size() == 1 &&
                memory_regions[0].cells <= 6 &&
                bounded_memory_terms.size() >= 5
            ? countModelsByProjection(ctx, solver, projection_terms, 0)
            : countModels(ctx, solver, projection_terms);
    }
    Z3_ast_vector_dec_ref(ctx, retained);
    const auto count_end = std::chrono::steady_clock::now();
    return volce::CountResult{
        count, std::move(bounded_vars), std::move(bounded_memory_terms),
        std::move(applied), std::move(validated_ground), std::move(rejected),
        std::move(applied_affine_relations),
        std::move(rejected_affine_relations),
        formula_assertions, decls.size(), projection_terms.size(),
        counting_assertions, factored_projection_components,
        static_cast<std::uint64_t>(
            std::chrono::duration_cast<std::chrono::microseconds>(
                warmup_end - warmup_start +
                count_warmup_end - count_warmup_start).count()),
        static_cast<std::uint64_t>(
            std::chrono::duration_cast<std::chrono::microseconds>(
                summary_end - summary_start).count()),
        static_cast<std::uint64_t>(
            std::chrono::duration_cast<std::chrono::microseconds>(
                count_end - count_start).count())};
}

}  // namespace

namespace volce {

std::optional<CountResult> countModelsFromSmt2(
    const std::string& smt2,
    const std::unordered_map<std::string, Range>& ranges,
    const std::optional<Range>& default_range,
    bool include_memory_terms,
    const std::vector<MemoryRegionProjection>& memory_regions) {
    if (smt2.empty()) {
        return std::nullopt;
    }

    const auto parsed_decls = parseBitVectorDecls(smt2);
    Z3_config config = Z3_mk_config();
    Z3_context ctx = Z3_mk_context(config);
    Z3_del_config(config);

    Z3_solver solver = Z3_mk_solver(ctx);
    Z3_solver_inc_ref(ctx, solver);
    Z3_ast_vector vec = Z3_parse_smtlib2_string(ctx, smt2.c_str(), 0, nullptr, nullptr, 0, nullptr, nullptr);
    auto result = countInternal(ctx, solver, vec, parsed_decls, {}, {}, ranges,
                                default_range, include_memory_terms,
                                memory_regions, false);

    Z3_solver_dec_ref(ctx, solver);
    Z3_del_context(ctx);

    return result;
}

std::optional<CountResult> countModelsFromSmt2WithSummaries(
    const std::string& smt2,
    const std::vector<AffineStateSummary>& summaries,
    const std::unordered_map<std::string, Range>& ranges,
    const std::optional<Range>& default_range,
    bool include_memory_terms,
    const std::vector<MemoryRegionProjection>& memory_regions,
    bool apply_entailed_summaries,
    const std::vector<AffineRelationSummary>& affine_relations) {
    if (smt2.empty()) return std::nullopt;

    const auto parsed_decls = parseBitVectorDecls(smt2);
    Z3_config config = Z3_mk_config();
    Z3_context ctx = Z3_mk_context(config);
    Z3_del_config(config);
    Z3_solver solver = Z3_mk_solver(ctx);
    Z3_solver_inc_ref(ctx, solver);
    Z3_ast_vector vec = Z3_parse_smtlib2_string(
        ctx, smt2.c_str(), 0, nullptr, nullptr, 0, nullptr, nullptr);
    auto result = countInternal(
        ctx, solver, vec, parsed_decls, summaries, affine_relations,
        ranges, default_range, include_memory_terms, memory_regions,
        apply_entailed_summaries);
    Z3_solver_dec_ref(ctx, solver);
    Z3_del_context(ctx);
    return result;
}

std::optional<MemoryRelationValidationResult>
validateMemoryCellRelationsFromSmt2(
    const std::string& smt2,
    const std::vector<MemoryCellAffineRelationSummary>& summaries) {
    if (smt2.empty()) return std::nullopt;

    Z3_config config = Z3_mk_config();
    Z3_context ctx = Z3_mk_context(config);
    Z3_del_config(config);
    Z3_solver solver = Z3_mk_solver(ctx);
    Z3_solver_inc_ref(ctx, solver);
    Z3_ast_vector vec = Z3_parse_smtlib2_string(
        ctx, smt2.c_str(), 0, nullptr, nullptr, 0, nullptr, nullptr);
    assertParsedFormulas(ctx, solver, vec);

    MemoryRelationValidationResult result;
    Z3_ast initialMemory = findNamedArrayConstant(ctx, vec, "%a");
    Z3_ast finalMemory =
        findNamedArrayConstant(ctx, vec, "%a#ssa_final");
    const auto decls = collectZeroArityDecls(ctx, vec);

    for (const auto& summary : summaries) {
        if (summary.cell_index < 0) {
            result.rejected.push_back(
                summary.source_name + "[" +
                std::to_string(summary.cell_index) +
                "]: negative cell index");
            continue;
        }
        if (!initialMemory || !finalMemory) {
            result.rejected.push_back(
                summary.source_name + "[" +
                std::to_string(summary.cell_index) +
                "]: initial/final memory provenance is missing");
            continue;
        }

        Z3_func_decl baseDecl = nullptr;
        std::string baseName;
        bool ambiguousBase = false;
        for (auto decl : decls) {
            const char* raw =
                Z3_get_symbol_string(ctx, Z3_get_decl_name(ctx, decl));
            const std::string name = raw ? raw : "";
            if (name.find("#base") == std::string::npos ||
                !isSummaryCandidateName(
                    name, summary.source_name)) {
                continue;
            }
            if (baseDecl) {
                ambiguousBase = true;
                break;
            }
            baseDecl = decl;
            baseName = name;
        }
        if (!baseDecl || ambiguousBase) {
            result.rejected.push_back(
                summary.source_name + "[" +
                std::to_string(summary.cell_index) +
                "]: expected exactly one source memory base");
            continue;
        }

        Z3_ast base = Z3_mk_app(ctx, baseDecl, 0, nullptr);
        Z3_sort addressSort = Z3_get_sort(ctx, base);
        if (!isBitVector(ctx, addressSort)) {
            result.rejected.push_back(
                summary.source_name + ": memory base is not a bit-vector");
            continue;
        }
        Z3_ast address = base;
        if (summary.cell_index != 0) {
            Z3_ast offset =
                Z3_mk_int64(ctx, summary.cell_index, addressSort);
            address = Z3_mk_bvadd(ctx, base, offset);
        }

        // Prefer the source cell declaration materialized for a local
        // uninitialized array. It represents the cell value at source-array
        // initialization and, when there is no pre-loop write, is the exact
        // loop-entry value. Falling back to select(%a,address) is conservative:
        // any intervening source initialization/write makes a wrong relation
        // fail the entailment check rather than being assumed away.
        Z3_ast entry = nullptr;
        const auto baseMarker = baseName.rfind("#base");
        if (baseMarker != std::string::npos) {
            const std::string scopePrefix =
                baseName.substr(0, baseMarker);
            const std::string expectedCell =
                scopePrefix + "@" +
                std::to_string(summary.cell_index);
            for (auto decl : decls) {
                const char* raw =
                    Z3_get_symbol_string(
                        ctx, Z3_get_decl_name(ctx, decl));
                const std::string name = raw ? raw : "";
                if (name == expectedCell) {
                    entry = Z3_mk_app(ctx, decl, 0, nullptr);
                    break;
                }
            }
        }
        if (!entry) {
            entry = Z3_mk_select(ctx, initialMemory, address);
        }
        Z3_ast exit = Z3_mk_select(ctx, finalMemory, address);
        Z3_sort valueSort = Z3_get_sort(ctx, entry);
        if (!isBitVector(ctx, valueSort) ||
            !Z3_is_eq_sort(ctx, valueSort, Z3_get_sort(ctx, exit))) {
            result.rejected.push_back(
                summary.source_name + ": memory cell sort mismatch");
            continue;
        }

        Z3_ast scaled = entry;
        if (summary.scale == 0) {
            scaled = Z3_mk_int64(ctx, 0, valueSort);
        } else if (summary.scale != 1) {
            Z3_ast scale =
                Z3_mk_int64(ctx, summary.scale, valueSort);
            scaled = Z3_mk_bvmul(ctx, entry, scale);
        }
        Z3_ast rhs = scaled;
        if (summary.offset != 0) {
            Z3_ast offset =
                Z3_mk_int64(ctx, summary.offset, valueSort);
            rhs = Z3_mk_bvadd(ctx, scaled, offset);
        }
        Z3_ast equality = Z3_mk_eq(ctx, exit, rhs);

        Z3_solver_push(ctx, solver);
        Z3_solver_assert(ctx, solver, Z3_mk_not(ctx, equality));
        const Z3_lbool check = Z3_solver_check(ctx, solver);
        Z3_solver_pop(ctx, solver, 1);

        const std::string label =
            summary.source_name + "[" +
            std::to_string(summary.cell_index) + "]@" + baseName +
            " scale=" + std::to_string(summary.scale) +
            " offset=" + std::to_string(summary.offset);
        if (check == Z3_L_FALSE) {
            result.applied.push_back(label);
        } else {
            result.rejected.push_back(
                label +
                ": path formula does not entail memory relation");
        }
    }

    // Frame proof for local source arrays. The #base symbol is emitted only
    // for concrete array objects, not pointer parameters. Source cells
    // (<scope>@N) define the region's entry state; every discovered cell not
    // written by the summary must be unchanged in the final memory.
    std::unordered_map<std::string, std::set<std::int64_t>> writtenCells;
    for (const auto& summary : summaries) {
        writtenCells[summary.source_name].insert(summary.cell_index);
    }
    for (const auto& group : writtenCells) {
        const std::string& source = group.first;
        Z3_func_decl baseDecl = nullptr;
        std::string baseName;
        bool ambiguousBase = false;
        for (auto decl : decls) {
            const char* raw =
                Z3_get_symbol_string(ctx, Z3_get_decl_name(ctx, decl));
            const std::string name = raw ? raw : "";
            if (name.find("#base") == std::string::npos ||
                !isSummaryCandidateName(name, source)) {
                continue;
            }
            if (baseDecl) {
                ambiguousBase = true;
                break;
            }
            baseDecl = decl;
            baseName = name;
        }
        if (!baseDecl || ambiguousBase) {
            result.frame_rejected.push_back(
                source + ": expected exactly one local array base");
            continue;
        }

        const auto baseMarker = baseName.rfind("#base");
        if (baseMarker == std::string::npos) {
            result.frame_rejected.push_back(
                source + ": malformed memory base provenance");
            continue;
        }
        const std::string scopePrefix =
            baseName.substr(0, baseMarker);
        const std::string cellPrefix = scopePrefix + "@";

        std::map<std::int64_t, Z3_func_decl> sourceCells;
        for (auto decl : decls) {
            const char* raw =
                Z3_get_symbol_string(ctx, Z3_get_decl_name(ctx, decl));
            const std::string name = raw ? raw : "";
            if (name.rfind(cellPrefix, 0) != 0) continue;
            const std::string suffix =
                name.substr(cellPrefix.size());
            if (suffix.empty() ||
                !std::all_of(
                    suffix.begin(), suffix.end(),
                    [](unsigned char ch) {
                        return std::isdigit(ch) != 0;
                    })) {
                continue;
            }
            const std::int64_t index =
                std::strtoll(suffix.c_str(), nullptr, 10);
            sourceCells.emplace(index, decl);
        }
        if (sourceCells.empty()) {
            result.frame_rejected.push_back(
                source + ": no source cells found for frame proof");
            continue;
        }

        bool valid = true;
        for (std::int64_t written : group.second) {
            if (sourceCells.find(written) == sourceCells.end()) {
                result.frame_rejected.push_back(
                    source + "[" + std::to_string(written) +
                    "]: summary cell is outside discovered source region");
                valid = false;
            }
        }
        if (!valid) continue;

        Z3_ast base = Z3_mk_app(ctx, baseDecl, 0, nullptr);
        Z3_sort addressSort = Z3_get_sort(ctx, base);
        std::size_t checked = 0;
        for (const auto& cell : sourceCells) {
            if (group.second.count(cell.first) != 0) continue;
            Z3_ast address = base;
            if (cell.first != 0) {
                Z3_ast offset =
                    Z3_mk_int64(ctx, cell.first, addressSort);
                address = Z3_mk_bvadd(ctx, base, offset);
            }
            Z3_ast entry =
                Z3_mk_app(ctx, cell.second, 0, nullptr);
            Z3_ast exit =
                Z3_mk_select(ctx, finalMemory, address);
            Z3_ast equality = Z3_mk_eq(ctx, exit, entry);

            Z3_solver_push(ctx, solver);
            Z3_solver_assert(ctx, solver, Z3_mk_not(ctx, equality));
            const Z3_lbool check = Z3_solver_check(ctx, solver);
            Z3_solver_pop(ctx, solver, 1);
            if (check != Z3_L_FALSE) {
                result.frame_rejected.push_back(
                    source + "[" + std::to_string(cell.first) +
                    "]: final memory does not preserve untouched cell");
                valid = false;
                break;
            }
            ++checked;
        }
        if (valid) {
            result.frame_applied.push_back(
                source + "@" + baseName +
                " cells=" + std::to_string(sourceCells.size()) +
                " untouched_checked=" + std::to_string(checked));
        }
    }

    Z3_solver_dec_ref(ctx, solver);
    Z3_del_context(ctx);
    return result;
}

std::optional<CountResult> countModelsFromSmt2File(
    const std::string& smt2_path,
    const std::unordered_map<std::string, Range>& ranges,
    const std::optional<Range>& default_range,
    bool include_memory_terms) {
    if (smt2_path.empty()) {
        return std::nullopt;
    }

    std::ifstream file(smt2_path);
    if (!file) {
        return std::nullopt;
    }
    std::string smt2((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    const auto parsed_decls = parseBitVectorDecls(smt2);

    Z3_config config = Z3_mk_config();
    Z3_context ctx = Z3_mk_context(config);
    Z3_del_config(config);

    Z3_solver solver = Z3_mk_solver(ctx);
    Z3_solver_inc_ref(ctx, solver);
    Z3_ast_vector vec = Z3_parse_smtlib2_string(ctx, smt2.c_str(), 0, nullptr, nullptr, 0, nullptr, nullptr);
    auto result = countInternal(ctx, solver, vec, parsed_decls, {}, {}, ranges,
                                default_range, include_memory_terms, {},
                                false);

    Z3_solver_dec_ref(ctx, solver);
    Z3_del_context(ctx);

    return result;
}

}  // namespace volce
