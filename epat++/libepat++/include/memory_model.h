// memory_model.h: 头文件
// 定义了内存建模类
#pragma once
#ifndef _EPAT_MEMORY_MODEL_H_
#define _EPAT_MEMORY_MODEL_H_
#include "smt_expr.h"
#include "stmt.h"
#include <iostream>
#include <map>
#include <memory>

namespace epat {
    template <typename LValue> class MemoryBase {
    public:
        using ptr = std::unique_ptr<MemoryBase>;
        using lvalue = LValue;
        using rvalue = smt::expr;

        // explicit MemoryBase() = default;
        // virtual ~MemoryBase() = default;

        // // api
        // std::string hello_world() { return "Hello World!"; }
    };

    // using LinearMemoryLValue = smt::expr;
    struct LinearMemoryLv {
        smt::expr e_;
        explicit LinearMemoryLv() : e_(gc.int_const(0)) {}
        explicit LinearMemoryLv(smt::expr const& e) : e_(e) {}
        LinearMemoryLv(LinearMemoryLv const&) = default;
        LinearMemoryLv(LinearMemoryLv&&) = default;
        LinearMemoryLv& operator=(LinearMemoryLv const&) = default;
        LinearMemoryLv& operator=(LinearMemoryLv&&) = default;
        bool operator==(LinearMemoryLv const& other) const
        {
            return e_.id() == other.e_.id();
        }
        struct less {
            bool operator()(LinearMemoryLv const& lhs, LinearMemoryLv const& rhs) const
            {
                return lhs.e_.id() < rhs.e_.id();
            }
        };
        smt::expr to_rv() const { return e_; }
        static LinearMemoryLv from_rv(smt::expr const& e) { return LinearMemoryLv(e); }
        LinearMemoryLv& operator+=(smt::expr rv)
        {
            e_ = e_ + rv;
            return *this;
        }
        friend LinearMemoryLv operator+(LinearMemoryLv const& lhs, smt::expr const& rhs)
        {
            auto ret = LinearMemoryLv(lhs);
            ret += rhs;
            return ret;
        }
        friend LinearMemoryLv operator+(LinearMemoryLv const& lhs, int rhs)
        {
            auto ret = LinearMemoryLv(lhs);
            ret.e_ = ret.e_ + rhs;
            return ret;
        }
        LinearMemoryLv simplify() { return LinearMemoryLv(e_.simplify()); }
        friend std::ostream& operator<<(std::ostream& os, LinearMemoryLv& self)
        {
            // XXX: 打印更多信息
            return os << self.e_;
        }
    };

    template <> class MemoryBase<LinearMemoryLv> {
    public:
        using ptr = std::unique_ptr<MemoryBase>;
        using lv = LinearMemoryLv;
        using rv = smt::expr;

        explicit MemoryBase() = default;
        virtual ~MemoryBase() = default;

        // data
        rv len_ = gc.bv_val(0, width);
        using assign_map = std::map<lv, rv, lv::less>;
        assign_map map_;
        z3::expr array_ = smt::expr(gc);
        void array_init()
        {
            if (array_)
                return; // array的!被重载，不适用
            epat_log("array_init");
            // auto array_sort = gc.array_sort(gc.int_sort(), gc.bv_sort(width));
            auto array_sort = gc.array_sort(gc.bv_sort(width), gc.bv_sort(width));
            array_ = gc.constant("%a", array_sort);
            // TODO: 根据赋值初始化，以及后续同步
            for (auto i : map_) {
                auto tmp = smt::to_tag(i.second, gc.bv_sort(width));
                array_ = z3::store(array_, i.first.e_, tmp);
            }
        }

        // api
        // lv rv2lv(rv r) { return lv(r); }
        lv alloc(rv size) // XXX: 究竟应该返回左值还是右值？
        {
            // std::cout << size << std::endl;
            epat_log("alloc ", size);
            auto tmp = len_;
            len_ = (len_ + size).simplify();
            return lv(tmp);
        }

        rv malloc(rv size) { return alloc(size).e_; }

        rv get(lv l, smt::sort sort)
        {
            if (array_) // 开启数组后
                return select(l, sort);
            l = l.simplify();
            epat_log("get ", l, " ", sort);
            // 如果左值能找到，直接返回，否则视为数组读写
            auto i = map_.find(l);
            if (i != map_.end()) {
                // return smt::to_tag(i->second, sort);
                return i->second;
            }
            return select(l, sort);
        }
        rv get(lv l, Expr const& e) { return get(l, smt::type2sort(e.getType())); }

        void set(lv l, rv v)
        {
            if (array_) // 开启数组后
                store(l, v);
            l = l.simplify();
            epat_log("set ", l, " ", v);
            // TODO: 与select和store交互
            // TODO: 确定类型
            // map_.insert_or_assign(l, smt::to_bv(v));
            map_.insert_or_assign(l, v);
        }

        rv select(lv l, smt::sort sort)
        {
            // if (!array_)
            array_init();
            epat_log("select ", l, " ", sort);
            return smt::to_tag(z3::select(array_, l.e_), sort);
        }
        rv select(lv l, Expr const& e) { return select(l, smt::type2sort(e.getType())); }

        void store(lv l, rv v)
        {
            epat_log("store ", l, " ", v);
            // if (!array_)
            array_init();
            array_ = z3::store(array_, l.e_, smt::to_bv(v));
        }
    };

    using LinearMemory = MemoryBase<LinearMemoryLv>;
}

#endif // !_EPAT_MEMORY_MODEL_H_
