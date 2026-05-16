typedef struct te_expr {
    int type;
    union {double value; const double *bound; const void *function;};
    void *parameters[1];
} te_expr;
enum {
    TE_VARIABLE = 0,
    TE_FUNCTION0 = 8, TE_FUNCTION1, TE_FUNCTION2, TE_FUNCTION3,
    TE_FUNCTION4, TE_FUNCTION5, TE_FUNCTION6, TE_FUNCTION7,
    TE_CLOSURE0 = 16, TE_CLOSURE1, TE_CLOSURE2, TE_CLOSURE3,
    TE_CLOSURE4, TE_CLOSURE5, TE_CLOSURE6, TE_CLOSURE7,
    TE_FLAG_PURE = 32
};
typedef struct te_variable {
    const char *name;
    const void *address;
    int type;
    void *context;
} te_variable;
double te_interp(const char *expression, int *error);
te_expr *te_compile(const char *expression, const te_variable *variables, int var_count, int *error);
double te_eval(const te_expr *n);
void te_print(const te_expr *n);
void te_free(te_expr *n);

typedef long unsigned int size_t;

extern void *malloc(size_t __size);
extern void free(void *__ptr);
extern void *memset(void *__s, int __c, size_t __n);
extern void *memcpy(void * restrict __dest, const void * restrict __src, size_t __n);
extern int isalpha(int);
extern int isdigit(int);
extern double strtod(const char * restrict __nptr, char ** restrict __endptr);
extern int strncmp(const char *__s1, const char *__s2, size_t __n);
extern int printf(const char * restrict __format, ...);

extern double acos(double);
extern double asin(double);
extern double atan(double);
extern double atan2(double, double);
extern double ceil(double);
extern double cos(double);
extern double cosh(double);
extern double exp(double);
extern double fabs(double);
extern double floor(double);
extern double fmod(double, double);
extern double log(double);
extern double log10(double);
extern double pow(double, double);
extern double sin(double);
extern double sinh(double);
extern double sqrt(double);
extern double tan(double);
extern double tanh(double);
extern float nanf(const char *);

typedef double (*te_fun2)(double, double);
enum {
    TOK_NULL = TE_CLOSURE7+1, TOK_ERROR, TOK_END, TOK_SEP,
    TOK_OPEN, TOK_CLOSE, TOK_NUMBER, TOK_VARIABLE, TOK_INFIX
};
enum {TE_CONSTANT = 1};
typedef struct state {
    const char *start;
    const char *next;
    int type;
    union {double value; const double *bound; const void *function;};
    void *context;
    const te_variable *lookup;
    int lookup_len;
} state;
static te_expr *new_expr(const int type, const te_expr *parameters[]) {
    const int arity = ( ((type) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((type) & 0x00000007) : 0 );
    const int psize = sizeof(void*) * arity;
    const int size = (sizeof(te_expr) - sizeof(void*)) + psize + ((((type) & TE_CLOSURE0) != 0) ? sizeof(void*) : 0);
    te_expr *ret = malloc(size);
    if ((ret) == ((void *)0)) { ; return ((void *)0); };
    memset(ret, 0, size);
    if (arity && parameters) {
        memcpy(ret->parameters, parameters, psize);
    }
    ret->type = type;
    ret->bound = 0;
    return ret;
}
void te_free_parameters(te_expr *n) {
    if (!n) return;
    switch (((n->type)&0x0000001F)) {
        case TE_FUNCTION7: case TE_CLOSURE7: te_free(n->parameters[6]);
        case TE_FUNCTION6: case TE_CLOSURE6: te_free(n->parameters[5]);
        case TE_FUNCTION5: case TE_CLOSURE5: te_free(n->parameters[4]);
        case TE_FUNCTION4: case TE_CLOSURE4: te_free(n->parameters[3]);
        case TE_FUNCTION3: case TE_CLOSURE3: te_free(n->parameters[2]);
        case TE_FUNCTION2: case TE_CLOSURE2: te_free(n->parameters[1]);
        case TE_FUNCTION1: case TE_CLOSURE1: te_free(n->parameters[0]);
    }
}
void te_free(te_expr *n) {
    if (!n) return;
    te_free_parameters(n);
    free(n);
}
static double pi(void) {return 3.14159265358979323846;}
static double e(void) {return 2.71828182845904523536;}
static double fac(double a) {
    if (a < 0.0)
        return nanf("");
    if (a > (0x7fffffff * 2U + 1U))
        return (1.0/0.0);
    unsigned int ua = (unsigned int)(a);
    unsigned long int result = 1, i;
    for (i = 1; i <= ua; i++) {
        if (i > (0x7fffffffffffffffL * 2UL + 1UL) / result)
            return (1.0/0.0);
        result *= i;
    }
    return (double)result;
}
static double ncr(double n, double r) {
    if (n < 0.0 || r < 0.0 || n < r) return nanf("");
    if (n > (0x7fffffff * 2U + 1U) || r > (0x7fffffff * 2U + 1U)) return (1.0/0.0);
    unsigned long int un = (unsigned int)(n), ur = (unsigned int)(r), i;
    unsigned long int result = 1;
    if (ur > un / 2) ur = un - ur;
    for (i = 1; i <= ur; i++) {
        if (result > (0x7fffffffffffffffL * 2UL + 1UL) / (un - ur + i))
            return (1.0/0.0);
        result *= un - ur + i;
        result /= i;
    }
    return result;
}
static double npr(double n, double r) {return ncr(n, r) * fac(r);}
static const te_variable functions[] = {
    {"abs", fabs, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"acos", acos, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"asin", asin, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"atan", atan, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"atan2", atan2, TE_FUNCTION2 | TE_FLAG_PURE, 0},
    {"ceil", ceil, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"cos", cos, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"cosh", cosh, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"e", e, TE_FUNCTION0 | TE_FLAG_PURE, 0},
    {"exp", exp, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"fac", fac, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"floor", floor, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"ln", log, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"log", log10, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"log10", log10, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"ncr", ncr, TE_FUNCTION2 | TE_FLAG_PURE, 0},
    {"npr", npr, TE_FUNCTION2 | TE_FLAG_PURE, 0},
    {"pi", pi, TE_FUNCTION0 | TE_FLAG_PURE, 0},
    {"pow", pow, TE_FUNCTION2 | TE_FLAG_PURE, 0},
    {"sin", sin, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"sinh", sinh, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"sqrt", sqrt, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"tan", tan, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"tanh", tanh, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {0, 0, 0, 0}
};
static const te_variable *find_builtin(const char *name, int len) {
    int imin = 0;
    int imax = sizeof(functions) / sizeof(te_variable) - 2;
    while (imax >= imin) {
        const int i = (imin + ((imax-imin)/2));
        int c = strncmp(name, functions[i].name, len);
        if (!c) c = '\0' - functions[i].name[len];
        if (c == 0) {
            return functions + i;
        } else if (c > 0) {
            imin = i + 1;
        } else {
            imax = i - 1;
        }
    }
    return 0;
}
static const te_variable *find_lookup(const state *s, const char *name, int len) {
    int iters;
    const te_variable *var;
    if (!s->lookup) return 0;
    for (var = s->lookup, iters = s->lookup_len; iters; ++var, --iters) {
        if (strncmp(name, var->name, len) == 0 && var->name[len] == '\0') {
            return var;
        }
    }
    return 0;
}
static double add(double a, double b) {return a + b;}
static double sub(double a, double b) {return a - b;}
static double mul(double a, double b) {return a * b;}
static double divide(double a, double b) {return a / b;}
static double negate(double a) {return -a;}
static double comma(double a, double b) {(void)a; return b;}
void next_token(state *s) {
    s->type = TOK_NULL;
    do {
        if (!*s->next){
            s->type = TOK_END;
            return;
        }
        if ((s->next[0] >= '0' && s->next[0] <= '9') || s->next[0] == '.') {
            s->value = strtod(s->next, (char**)&s->next);
            s->type = TOK_NUMBER;
        } else {
            if (isalpha((unsigned char)s->next[0])) {
                const char *start;
                start = s->next;
                while (isalpha((unsigned char)s->next[0]) || isdigit((unsigned char)s->next[0]) || (s->next[0] == '_')) s->next++;
                const te_variable *var = find_lookup(s, start, s->next - start);
                if (!var) var = find_builtin(start, s->next - start);
                if (!var) {
                    s->type = TOK_ERROR;
                } else {
                    switch(((var->type)&0x0000001F))
                    {
                        case TE_VARIABLE:
                            s->type = TOK_VARIABLE;
                            s->bound = var->address;
                            break;
                        case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:
                        case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
                            s->context = var->context;
                        case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:
                        case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
                            s->type = var->type;
                            s->function = var->address;
                            break;
                    }
                }
            } else {
                switch (s->next++[0]) {
                    case '+': s->type = TOK_INFIX; s->function = add; break;
                    case '-': s->type = TOK_INFIX; s->function = sub; break;
                    case '*': s->type = TOK_INFIX; s->function = mul; break;
                    case '/': s->type = TOK_INFIX; s->function = divide; break;
                    case '^': s->type = TOK_INFIX; s->function = pow; break;
                    case '%': s->type = TOK_INFIX; s->function = fmod; break;
                    case '(': s->type = TOK_OPEN; break;
                    case ')': s->type = TOK_CLOSE; break;
                    case ',': s->type = TOK_SEP; break;
                    case ' ': case '\t': case '\n': case '\r': break;
                    default: s->type = TOK_ERROR; break;
                }
            }
        }
    } while (s->type == TOK_NULL);
}
static te_expr *list(state *s);
static te_expr *expr(state *s);
static te_expr *power(state *s);
static te_expr *base(state *s) {
    te_expr *ret;
    int arity;
    switch (((s->type)&0x0000001F)) {
        case TOK_NUMBER:
            ret = new_expr(TE_CONSTANT, 0);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            ret->value = s->value;
            next_token(s);
            break;
        case TOK_VARIABLE:
            ret = new_expr(TE_VARIABLE, 0);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            ret->bound = s->bound;
            next_token(s);
            break;
        case TE_FUNCTION0:
        case TE_CLOSURE0:
            ret = new_expr(s->type, 0);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            ret->function = s->function;
            if ((((s->type) & TE_CLOSURE0) != 0)) ret->parameters[0] = s->context;
            next_token(s);
            if (s->type == TOK_OPEN) {
                next_token(s);
                if (s->type != TOK_CLOSE) {
                    s->type = TOK_ERROR;
                } else {
                    next_token(s);
                }
            }
            break;
        case TE_FUNCTION1:
        case TE_CLOSURE1:
            ret = new_expr(s->type, 0);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            ret->function = s->function;
            if ((((s->type) & TE_CLOSURE0) != 0)) ret->parameters[1] = s->context;
            next_token(s);
            ret->parameters[0] = power(s);
            if ((ret->parameters[0]) == ((void *)0)) { te_free(ret); return ((void *)0); };
            break;
        case TE_FUNCTION2: case TE_FUNCTION3: case TE_FUNCTION4:
        case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
        case TE_CLOSURE2: case TE_CLOSURE3: case TE_CLOSURE4:
        case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
            arity = ( ((s->type) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((s->type) & 0x00000007) : 0 );
            ret = new_expr(s->type, 0);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            ret->function = s->function;
            if ((((s->type) & TE_CLOSURE0) != 0)) ret->parameters[arity] = s->context;
            next_token(s);
            if (s->type != TOK_OPEN) {
                s->type = TOK_ERROR;
            } else {
                int i;
                for(i = 0; i < arity; i++) {
                    next_token(s);
                    ret->parameters[i] = expr(s);
                    if ((ret->parameters[i]) == ((void *)0)) { te_free(ret); return ((void *)0); };
                    if(s->type != TOK_SEP) {
                        break;
                    }
                }
                if(s->type != TOK_CLOSE || i != arity - 1) {
                    s->type = TOK_ERROR;
                } else {
                    next_token(s);
                }
            }
            break;
        case TOK_OPEN:
            next_token(s);
            ret = list(s);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            if (s->type != TOK_CLOSE) {
                s->type = TOK_ERROR;
            } else {
                next_token(s);
            }
            break;
        default:
            ret = new_expr(0, 0);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            s->type = TOK_ERROR;
            ret->value = nanf("");
            break;
    }
    return ret;
}
static te_expr *power(state *s) {
    int sign = 1;
    while (s->type == TOK_INFIX && (s->function == add || s->function == sub)) {
        if (s->function == sub) sign = -sign;
        next_token(s);
    }
    te_expr *ret;
    if (sign == 1) {
        ret = base(s);
    } else {
        te_expr *b = base(s);
        if ((b) == ((void *)0)) { ; return ((void *)0); };
        ret = new_expr((TE_FUNCTION1 | TE_FLAG_PURE), (const te_expr*[]){b});
        if ((ret) == ((void *)0)) { te_free(b); return ((void *)0); };
        ret->function = negate;
    }
    return ret;
}
static te_expr *factor(state *s) {
    te_expr *ret = power(s);
    if ((ret) == ((void *)0)) { ; return ((void *)0); };
    while (s->type == TOK_INFIX && (s->function == pow)) {
        te_fun2 t = s->function;
        next_token(s);
        te_expr *p = power(s);
        if ((p) == ((void *)0)) { te_free(ret); return ((void *)0); };
        te_expr *prev = ret;
        ret = new_expr((TE_FUNCTION2 | TE_FLAG_PURE), (const te_expr*[]){ret, p});
        if ((ret) == ((void *)0)) { te_free(p), te_free(prev); return ((void *)0); };
        ret->function = t;
    }
    return ret;
}
static te_expr *term(state *s) {
    te_expr *ret = factor(s);
    if ((ret) == ((void *)0)) { ; return ((void *)0); };
    while (s->type == TOK_INFIX && (s->function == mul || s->function == divide || s->function == fmod)) {
        te_fun2 t = s->function;
        next_token(s);
        te_expr *f = factor(s);
        if ((f) == ((void *)0)) { te_free(ret); return ((void *)0); };
        te_expr *prev = ret;
        ret = new_expr((TE_FUNCTION2 | TE_FLAG_PURE), (const te_expr*[]){ret, f});
        if ((ret) == ((void *)0)) { te_free(f), te_free(prev); return ((void *)0); };
        ret->function = t;
    }
    return ret;
}
static te_expr *expr(state *s) {
    te_expr *ret = term(s);
    if ((ret) == ((void *)0)) { ; return ((void *)0); };
    while (s->type == TOK_INFIX && (s->function == add || s->function == sub)) {
        te_fun2 t = s->function;
        next_token(s);
        te_expr *te = term(s);
        if ((te) == ((void *)0)) { te_free(ret); return ((void *)0); };
        te_expr *prev = ret;
        ret = new_expr((TE_FUNCTION2 | TE_FLAG_PURE), (const te_expr*[]){ret, te});
        if ((ret) == ((void *)0)) { te_free(te), te_free(prev); return ((void *)0); };
        ret->function = t;
    }
    return ret;
}
static te_expr *list(state *s) {
    te_expr *ret = expr(s);
    if ((ret) == ((void *)0)) { ; return ((void *)0); };
    while (s->type == TOK_SEP) {
        next_token(s);
        te_expr *e = expr(s);
        if ((e) == ((void *)0)) { te_free(ret); return ((void *)0); };
        te_expr *prev = ret;
        ret = new_expr((TE_FUNCTION2 | TE_FLAG_PURE), (const te_expr*[]){ret, e});
        if ((ret) == ((void *)0)) { te_free(e), te_free(prev); return ((void *)0); };
        ret->function = comma;
    }
    return ret;
}
double te_eval(const te_expr *n) {
    if (!n) return nanf("");
    switch(((n->type)&0x0000001F)) {
        case TE_CONSTANT: return n->value;
        case TE_VARIABLE: return *n->bound;
        case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:
        case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
            switch(( ((n->type) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((n->type) & 0x00000007) : 0 )) {
                case 0: return ((double(*)(void))n->function)();
                case 1: return ((double(*)(double))n->function)(te_eval(n->parameters[0]));
                case 2: return ((double(*)(double, double))n->function)(te_eval(n->parameters[0]), te_eval(n->parameters[1]));
                case 3: return ((double(*)(double, double, double))n->function)(te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]));
                case 4: return ((double(*)(double, double, double, double))n->function)(te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]));
                case 5: return ((double(*)(double, double, double, double, double))n->function)(te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]), te_eval(n->parameters[4]));
                case 6: return ((double(*)(double, double, double, double, double, double))n->function)(te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]), te_eval(n->parameters[4]), te_eval(n->parameters[5]));
                case 7: return ((double(*)(double, double, double, double, double, double, double))n->function)(te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]), te_eval(n->parameters[4]), te_eval(n->parameters[5]), te_eval(n->parameters[6]));
                default: return nanf("");
            }
        case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:
        case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
            switch(( ((n->type) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((n->type) & 0x00000007) : 0 )) {
                case 0: return ((double(*)(void*))n->function)(n->parameters[0]);
                case 1: return ((double(*)(void*, double))n->function)(n->parameters[1], te_eval(n->parameters[0]));
                case 2: return ((double(*)(void*, double, double))n->function)(n->parameters[2], te_eval(n->parameters[0]), te_eval(n->parameters[1]));
                case 3: return ((double(*)(void*, double, double, double))n->function)(n->parameters[3], te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]));
                case 4: return ((double(*)(void*, double, double, double, double))n->function)(n->parameters[4], te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]));
                case 5: return ((double(*)(void*, double, double, double, double, double))n->function)(n->parameters[5], te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]), te_eval(n->parameters[4]));
                case 6: return ((double(*)(void*, double, double, double, double, double, double))n->function)(n->parameters[6], te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]), te_eval(n->parameters[4]), te_eval(n->parameters[5]));
                case 7: return ((double(*)(void*, double, double, double, double, double, double, double))n->function)(n->parameters[7], te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]), te_eval(n->parameters[4]), te_eval(n->parameters[5]), te_eval(n->parameters[6]));
                default: return nanf("");
            }
        default: return nanf("");
    }
}
static void optimize(te_expr *n) {
    if (n->type == TE_CONSTANT) return;
    if (n->type == TE_VARIABLE) return;
    if ((((n->type) & TE_FLAG_PURE) != 0)) {
        const int arity = ( ((n->type) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((n->type) & 0x00000007) : 0 );
        int known = 1;
        int i;
        for (i = 0; i < arity; ++i) {
            optimize(n->parameters[i]);
            if (((te_expr*)(n->parameters[i]))->type != TE_CONSTANT) {
                known = 0;
            }
        }
        if (known) {
            const double value = te_eval(n);
            te_free_parameters(n);
            n->type = TE_CONSTANT;
            n->value = value;
        }
    }
}
te_expr *te_compile(const char *expression, const te_variable *variables, int var_count, int *error) {
    state s;
    s.start = s.next = expression;
    s.lookup = variables;
    s.lookup_len = var_count;
    next_token(&s);
    te_expr *root = list(&s);
    if (root == ((void *)0)) {
        if (error) *error = -1;
        return ((void *)0);
    }
    if (s.type != TOK_END) {
        te_free(root);
        if (error) {
            *error = (s.next - s.start);
            if (*error == 0) *error = 1;
        }
        return 0;
    } else {
        optimize(root);
        if (error) *error = 0;
        return root;
    }
}
double te_interp(const char *expression, int *error) {
    te_expr *n = te_compile(expression, 0, 0, error);
    double ret;
    if (n) {
        ret = te_eval(n);
        te_free(n);
    } else {
        ret = nanf("");
    }
    return ret;
}
static void pn (const te_expr *n, int depth) {
    int i, arity;
    printf("%*s", depth, "");
    switch(((n->type)&0x0000001F)) {
    case TE_CONSTANT: printf("%f\n", n->value); break;
    case TE_VARIABLE: printf("bound %p\n", n->bound); break;
    case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:
    case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
    case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:
    case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
         arity = ( ((n->type) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((n->type) & 0x00000007) : 0 );
         printf("f%d", arity);
         for(i = 0; i < arity; i++) {
             printf(" %p", n->parameters[i]);
         }
         printf("\n");
         for(i = 0; i < arity; i++) {
             pn(n->parameters[i], depth + 1);
         }
         break;
    }
}
void te_print(const te_expr *n) {
    pn(n, 0);
}
