// c1_visitor.h: 头文件
// 定义了C1语法树遍历类
#pragma once
#ifndef _EPAT_C1_VISITOR_H_
#define _EPAT_C1_VISITOR_H_
#include "my_stack.h"
#include "solver_base.h"
#include "stmt.h"

namespace epat {
    template <typename T> class C1Solver : public SolverBase<T> {
    public:
        explicit C1Solver(CompoundStmt const& ast) : SolverBase<T>(ast) {}
        // virtual result feasible() {
        //      return result::unknown; }
        // virtual std::string getModel() { return default_model_; }
        // virtual std::string getSMT2() { return default_smt2_; }
    protected:
        using lv = typename SolverBase<T>::lv;
        using rv = typename SolverBase<T>::rv;
        MyStack<rv> rvs_;
        MyStack<lv> lvs_;
        std::map<void*, lv> lv_map_;
        lv getLValue(ValueDecl const& vd)
        {
            auto i = lv_map_.find((void*)&vd);
            if (i != lv_map_.end())
                return i->second;
            epat_error("no lvalue for " + vd.getName());
        }
        void setLValue(ValueDecl const& vd, lv l)
        {
            lv_map_.insert_or_assign((void*)&vd, l);
        }
        struct type_record {
            rv size, length;
            explicit type_record() : size(_1), length(_1) {}
            explicit type_record(rv s, rv l) : size(s), length(l) {}
        };
        using type_record_map = std::map<Type::ptr, type_record>;
        type_record_map type_record_map_;
        rv getTypeSize(QualType const& qt)
        {
            if (qt.isComplete())
                // return gc.int_val(qt.getSize());
                return gc.bv_val(qt.getSize(), width);
            return getTypeRecord(qt).size;
        }
        rv getTypeLength(QualType const& qt)
        {
            if (qt.isComplete()) {
                auto ele_size = qt.getElement().getSize();
                auto size = qt.getSize();
                return gc.bv_val(size / ele_size, width);
            }
            return getTypeRecord(qt).length;
        }
        type_record getTypeRecord(QualType const& qt) { return getTypeRecord(qt.get()); }
        type_record getTypeRecord(Type::ptr const& t)
        {
            if (t->isComplete())
                return type_record{_1, _1};
            auto i = type_record_map_.find(t);
            if (i != type_record_map_.end())
                return i->second;
            return visitType(t);
        }
        type_record visitType(QualType const& qt) { return visitType(qt.get()); }
        type_record visitType(Type::ptr const& t)
        {
            switch (t->getKind()) {
                using TypeKind = Type::TypeKind;
            case TypeKind::Array: {
                auto at = std::static_pointer_cast<ArrayType>(t);
                auto& len_expr = at->getLength();
                this->visit(len_expr);
                auto len = rvs_.pop();
                const auto& elem_type = at->getElement();
                auto elem_size = getTypeSize(elem_type);
                auto size = (elem_size * len).simplify();
                return type_record_map_[t] = type_record();
            }
            case TypeKind::Typedef: {
                auto tdt = std::static_pointer_cast<TypedefType>(t);
                return type_record_map_[t] = getTypeRecord(tdt->getType());
            }
            case TypeKind::Pointer:
                // TODO: 把指针作为数组处理
                return type_record_map_[t] = type_record();
            default:
                epat_error(std::string("visit unknown type: ") +
                           Type::typeKind2Str(t->getKind()));
            }
        }
        using field_record_map = std::map<FieldDecl const*, int>;
        field_record_map field_record_map_;
        int getOffset(FieldDecl const& fd)
        {
            // XXX: 效率优化
            auto i = field_record_map_.find(&fd);
            if (i != field_record_map_.end())
                return i->second;
            auto& sd = fd.getParent();
            for (int i = 0, n = sd.getFieldCount(), off = 0; i < n; ++i) {
                auto& f = sd.getField(i);
                field_record_map_[&f] = off;
                off += f.getType().getSize();
            }
            return field_record_map_[&fd];
        }
        virtual void visitArraySubscript(const epat::ArraySubscript& ary) override
        {
            auto& base = ary.getBase();
            auto& subscript = ary.getSubscript();
            this->visit(base);
            // 应当是右值，指针或是弱化指针
            epat_assert(base.isRValue());
            // 无论是不是弱化指针，此处都是表示地址的右值
            // if (base.isDecay())
            rv bs = rvs_.pop();
            // lv bs = base.isLValue() ? lvs_.pop() : lv(rvs_.pop());
            this->visit(subscript);
            rv ss = rvs_.pop();
            auto size = getTypeSize(ary.getType());
            // TODO: base是指针的情况
            // XXX: 目前仅当是数组的弱化指针时限制下标
            if (base.isDecay()) {
                auto& array_ref = CastExpr::removeCast(base);
                auto length = getTypeLength(array_ref.getType());
                this->smt_.pushCond(0 <= ss && ss < length);
            }
            rv ret = (bs + ss * size).simplify();
            lvs_.push(lv::from_rv(ret));
        }
        virtual void visitBinaryOperator(const epat::BinaryOperator& bop) override
        {
            // 区分赋值操作符和非赋值操作符
            auto op = bop.getOperator();
            if (BinaryOperator::isAssignOp(op)) { // TODO: 赋值类二元操作符
                // 左操作数为左值，表达式右结合
                // TODO: 结构体赋值！
                this->visit(bop.getRightOperand());
                auto rop = rvs_.pop();
                this->visit(bop.getLeftOperand());
                auto l = lvs_.pop();
                auto lop = BinaryOperator::Bop::Asgn == op
                               ? _0
                               : this->mem_.get(l, bop.getLeftOperand());
                auto do_cal = [&]() {
                    switch (op) {
                        using Bop = BinaryOperator::Bop;
                    case Bop::Asgn:
                        return rop;
                    case Bop::AddAsgn:
                        return lop + rop;
                    case Bop::SubAsgn:
                        return lop - rop;
                    case Bop::MulAsgn:
                        return lop * rop;
                    case Bop::DivAsgn:
                        return lop / rop;
                    case Bop::ModAsgn:
                        return lop % rop;
                    // TODO: 位操作符处理
                    case Bop::ShlAsgn:
                        return z3::shl(smt::to_bv(lop), smt::to_bv(rop));
                    case Bop::ShrAsgn: // 算术右移
                        return z3::ashr(smt::to_bv(lop), smt::to_bv(rop));
                    case Bop::AndAsgn:
                        return smt::to_bv(lop) & smt::to_bv(rop);
                    case Bop::XorAsgn:
                        return smt::to_bv(lop) ^ smt::to_bv(rop);
                    case Bop::OrAsgn:
                        return smt::to_bv(lop) | smt::to_bv(rop);
                    default:
                        return rop;
                    }
                };
                auto ret = do_cal();
                ret = smt::bool2int(ret);
                this->mem_.set(l, ret);
                rvs_.push(std::move(ret));
            }
            else {
                // 双操作数一定为右值
                // XXX: 求值顺序和运算符优先级有无关？
                this->visit(bop.getLeftOperand());
                auto lop = rvs_.pop();
                this->visit(bop.getRightOperand());
                auto rop = rvs_.pop();
                auto do_cal = [&]() {
                    switch (op) {
                        using Bop = BinaryOperator::Bop;
                    case Bop::Add:
                        return lop + rop;
                    case Bop::Sub:
                        return lop - rop;
                    case Bop::Mul:
                        return lop * rop;
                    case Bop::Div:
                        return lop / rop;
                    case Bop::Mod:
                        return lop % rop;
                    // 逻辑操作符
                    case Bop::Lt:
                        return lop < rop;
                    case Bop::LtEq:
                        return lop <= rop;
                    case Bop::Gt:
                        return lop > rop;
                    case Bop::GtEq:
                        return lop >= rop;
                    case Bop::Eq:
                        return lop == rop;
                    case Bop::Neq:
                        return lop != rop;
                    // TODO: 与或非
                    case Bop::LAnd:
                        return smt::to_bool(lop) && smt::to_bool(rop);
                    case Bop::LOr:
                        return smt::to_bool(lop) || smt::to_bool(rop);
                    // TODO: 位操作符处理
                    case Bop::Shl:
                        return z3::shl(smt::to_bv(lop), smt::to_bv(rop));
                    case Bop::Shr: // 算术右移
                        return z3::ashr(smt::to_bv(lop), smt::to_bv(rop));
                    case Bop::And:
                        return smt::to_bv(lop) & smt::to_bv(rop);
                    case Bop::Xor:
                        return smt::to_bv(lop) ^ smt::to_bv(rop);
                    case Bop::Or:
                        return smt::to_bv(lop) | smt::to_bv(rop);
                        // 逗号表达式
                    case Bop::Comma:
                    default:
                        return rop;
                    }
                };
                auto ret = do_cal();
                ret = smt::bool2int(ret);
                rvs_.push(ret);
            }
        }
        virtual void visitCallExpr(const epat::CallExpr& call) override
        {
            // 现阶段，callee可能是func的declref或是一个指针（右值）。
            // TODO: 但是指针的情况未实现
            // TODO: 处理参数。下面的代码会处理特殊函数的参数
            FunctionDecl::ptr func = {};
            auto& callee = call.getCallee();
            if (auto& orgi = CastExpr::removeCast(callee);
                Stmt::StmtKind::DeclRefExpr == orgi.getKind()) {
                auto& decl = static_cast<const DeclRefExpr&>(orgi);
                func = std::dynamic_pointer_cast<FunctionDecl>(decl.getDeclPtr());
            }
            if (!func)
                epat_error(callee.getCode() + " is not a supported func!");
            auto func_name = func->getName();
            // 库函数
            // XXX: 目前靠函数名称识别
            int opd_num = call.getOperandCount();
            auto do_func = [&]() {
                if ("malloc" == func_name) {
                    // TODO: malloc到指针时，指针没有长度，从而导致分析时认为数组长度为1
                    // TODO: 把指针标记为数组
                    if (opd_num < 1)
                        epat_error("malloc needs 1 operand");
                    auto& _Size = call.getOperand(0);
                    this->visit(_Size);
                    auto size = rvs_.pop();
                    // XXX: bytes计算的size
                    // size = buildSymbExpr("div", {size, std::to_string(sizeof(int))});
                    size = size / sizeof_int;
                    size = size.simplify();
                    rvs_.push(this->mem_.malloc(size));
                    std::cout << "malloc: " << rvs_.top() << std::endl;
                    return;
                }
                else if ("free" == func_name) {
                    // TODO: free
                    return;
                }
                else if ("memcpy" == func_name) {
                    // TODO: memcpy
                    return;
                }
                else if ("memset" == func_name) {
                    // TODO: memcmp
                    return;
                    if (opd_num < 3)
                        epat_error("memset needs 3 operands");
                    auto& _Ptr = call.getOperand(0);
                    auto& _Val = call.getOperand(1);
                    auto& _Size = call.getOperand(2);
                    this->visit(_Ptr);
                    auto ptr = rvs_.pop();
                    this->visit(_Val);
                    auto val = rvs_.pop();
                    this->visit(_Size);
                    auto size = rvs_.pop();
                    // XXX: bytes计算的size
                    size = size / sizeof_int;
                    size = size.simplify();
                    // TODO: modeling memset
                    // rvs_.push(_memset(ptr, val, size));
                    return;
                }
                epat_warning("skip a call to " + func_name);
                // TODO: 处理参数，返回值，默认int
                // TODO: 返回值是结构体
                // ++call_count_; TODO: call_count
                // auto call_ret = getCallRet(func_name);
                // pushConst(call_ret, getSmtType(call.getType()));
                // rv_stack_.push(call_ret);
            };
            do_func();
        }
        virtual void visitCastExpr(const epat::CastExpr& cast) override
        {
            using CastKind = CastExpr::CastKind;
            this->visit(cast.getSubExpr());
            switch (cast.getCastKind()) {
            case CastKind::LValueToRValue: {
                // std::cout << lvs_.top() << std::endl;
                // rvs_.push(this->mem_.get(lvs_.pop(), cast));
                rvs_.push(this->mem_.get(lvs_.pop(), cast));
                // std::cout << rvs_.top() << std::endl;
                break;
            }
            case CastKind::BitCast: { // do nothing for bitcast
                // rvs_.push(this->mem_.get(lvs_.pop(), cast));
                break;
            }
            case CastKind::CStyleCast: // TODO: cstyle cast
                epat_warning("cstyle cast is not supported now");
                break;
            case CastKind::ArrayToPointerDecay:
                rvs_.push(lvs_.pop().to_rv());
                break;
            case CastKind::FunctionToPointerDecay:
                // XXX: 在现版本不会出现
                epat_warning("should not have a func to ptr decay");
                break;
            default:
                epat_error("unsupported cast kind");
            }
        }
        virtual void visitDeclRefExpr(const epat::DeclRefExpr& dref) override
        {
            // TODO: 函数的处理，现在处理函数调用不会触发这个方法
            auto& decl = dref.getDecl();
            switch (decl.getDeclKind()) {
                using DeclKind = Decl::DeclKind;
            case DeclKind::VarDecl: {
                // XXX: 考虑不存在的情形
                auto& vard = static_cast<VarDecl const&>(decl);
                lvs_.push(getLValue(vard));
                break;
            }
            default:
                // 是否直接报错？
                break;
            }
        }
        virtual void visitDeclStmt(const DeclStmt& declstmt) override
        {
            auto& decl = declstmt.getDecl();
            switch (decl.getDeclKind()) {
                using DeclKind = Decl::DeclKind;
            case DeclKind::FieldDecl: // impossible
                epat_error("visit declstmt with fielddecl");
                break;
            case DeclKind::FunctionDecl: // skip
                break;
            case DeclKind::ParmVarDecl: // skip
                break;
            case DeclKind::StructDecl: // XXX: 懒惰处理
                break;
            case DeclKind::TypeDecl: // skip
                break;
            case DeclKind::ValueDecl: // impossible
                epat_error("visit declstmt with valuedecl");
                break;
            case DeclKind::VarDecl: {
                auto& vard = static_cast<const VarDecl&>(decl);
                bool isComplete = vard.getType().isComplete();
                auto size = getTypeSize(vard.getType());
                auto l = this->mem_.alloc(size);
                setLValue(vard, l);
                if (vard.hasInit()) {
                    // TODO: 1.init是{}表达式的情形;2.init是结构体右值的情形
                    // TODO: set和store区分
                    auto pos = rvs_.size();
                    this->visit(vard.getInit());
                    // TODO: init是init_list_expr的情形, init不能覆盖的情形
                    auto init_list = rvs_.pop_from(pos);
                    for (int i = 0, n = (int)init_list.size(); i < n; ++i)
                        this->mem_.set((l + i).simplify(), init_list[i]);
                }
                else {
                    auto name = this->getUniqueName(vard);
                    if (isComplete) {
                        // TODO: 完整类型会赋初值，不完整类型待定
                        auto types = vard.getType().getContents(true);
                        for (int i = 0, n = (int)types.size(); i < n; ++i) {
                            auto const& t = types[i];
                            auto sort = smt::type2sort(t);
                            auto new_name = name + "@" + std::to_string(i);
                            auto v = gc.constant(new_name.c_str(), sort);
                            this->mem_.set((l + i).simplify(), v);
                        }
                    }
                }
                break;
            }
            default:
                epat_error("visit declstmt with unknown declkind");
                break;
            }
        }
        virtual void visitImplicitCastExpr(const epat::ImplicitCastExpr& icast) override
        {
            visitCastExpr(icast);
        }
        virtual void visitInitListExpr(const epat::InitListExpr& init_list) override
        {
            // TODO: {0} {.a=1} 这些情况应该在编译前端处理，此处只求值
            for (int i = 0, n = init_list.getInitExprCount(); i < n; ++i)
                this->visit(init_list.getInitExpr(i));
        }
        virtual void visitChrLiteral(const epat::ChrLiteral& lit) override
        {
            rvs_.push(gc.bv_val((int)lit.getValue(), width)); // XXX: 整数精度
        }
        virtual void visitFltLiteral(const epat::FltLiteral& lit) override
        {
            rvs_.push(gc.fpa_val((float)lit.getValue()));
        }
        virtual void visitIntLiteral(const epat::IntLiteral& lit) override
        {
            rvs_.push(gc.bv_val((int)lit.getValue(), width));
        }
        virtual void visitStrLiteral(const epat::StrLiteral& lit) override
        {
            rvs_.push(gc.string_val(lit.getValue().c_str()));
        }
        virtual void visitMemberExpr(const epat::MemberExpr& mem) override
        {
            auto& field = mem.getMember();
            auto offset = getOffset(field);
            auto& base = mem.getBase();
            this->visit(base);
            if (mem.isArrow()) {
                // base将是右值
                auto l = lv(rvs_.pop());
                lvs_.push((l + offset).simplify());
            }
            else {
                // base将是左值
                auto l = lvs_.pop();
                lvs_.push((l + offset).simplify());
            }
        }
        virtual void visitReturnStmt(const epat::ReturnStmt& ret) override
        {
            epat_warning("return is not supposed to exist in a path");
            if (ret.hasRet()) {
                this->visit(ret.getRet());
                rvs_.pop(); // discard return value
            }
        }
        virtual void visitSignStmt(const epat::SignStmt& sign_stmt) override
        {
            this->visit(sign_stmt.getCondition());
            auto cond = rvs_.pop();
            this->smt_.pushCond(cond);
        }
        virtual void visitSizeofExpr(const epat::SizeofExpr& sizeof_expr) override
        {
            auto size = getTypeSize(sizeof_expr.getType());
            rvs_.push((size * sizeof_int).simplify()); // 适应malloc(x * 4)
        }
        virtual void visitUnaryOperator(const epat::UnaryOperator& uop) override
        {
            // 自增、取地址需要操作数是左值，其余右值
            auto op = uop.getOperator();
            auto& opd = uop.getOperand();
            if (opd.isLValue()) { // 操作数是左值，支持取地址和自增等操作
                this->visit(opd);
                auto l = lvs_.pop();
                auto lop = UnaryOperator::Uop::AddrOf == op ? _0 // discard
                                                            : this->mem_.get(l, opd);
                auto do_cal = [&]() {
                    switch (op) {
                    case UnaryOperator::Uop::PreInc:
                        this->mem_.set(l, lop + 1);
                        return lop + 1;
                    case UnaryOperator::Uop::PreDec:
                        this->mem_.set(l, lop - 1);
                        return lop - 1;
                    case UnaryOperator::Uop::PostInc:
                        this->mem_.set(l, lop + 1);
                        return lop;
                    case UnaryOperator::Uop::PostDec:
                        this->mem_.set(l, lop - 1);
                        return lop;
                    case UnaryOperator::Uop::AddrOf:
                        return l.to_rv();
                    default:
                        epat_error("should not get a left value for unary operator \'",
                                   op, "\'");
                    }
                };
                auto ret = do_cal();
                rvs_.push(ret);
            }
            else if (UnaryOperator::Uop::Deref == op) {
                this->visit(opd);
                auto r = rvs_.pop();
                lvs_.push(lv::from_rv(r));
            }
            else { // 操作数是右值，支持自增等操作
                this->visit(opd);
                auto r = rvs_.pop();
                auto do_cal = [&]() {
                    switch (op) {
                    case UnaryOperator::Uop::Not:
                        return smt::bool2int(!smt::to_bool(r));
                    case UnaryOperator::Uop::Compl:
                        return ~r;
                    case UnaryOperator::Uop::UPlus:
                        return r;
                    case UnaryOperator::Uop::UNeg:
                        return -r;
                    default:
                        epat_error("should not get a right value for unary operator \'",
                                   op, "\'");
                    }
                };
                auto ret = do_cal();
                rvs_.push(ret);
            }
        }
    };
}

#endif // !_EPAT_C1_VISITOR_H_
