// node.h: 头文件
// 定义了基类
#pragma once
#ifndef _EPAT_NODE_H_
#define _EPAT_NODE_H_
#include <memory>
#include <string>
#include <vector>

namespace epat {
    // 虚基类
    class Node {
    protected:
        using list = std::vector<Node*>;
        // using str_list = std::vector<std::string>;
        explicit Node();
        // virtual list getChildren() const
        //  辅助函数
        std::string buildAstString(
            list children, std::string parent, std::string prefix
        ) const;
        // std::string buildCode(list children, int indent) const;
    public:
        // 不允许复制
        Node(const Node&) = delete;
        virtual ~Node() = default;
        virtual std::string getAstString(std::string prefix = "") const;
        virtual std::string getCode(int indent = 0) const;
        virtual bool valid() const { return true; }

        friend inline std::ostream& operator<<(std::ostream& os, const Node& n)
        {
            return os << n.getCode();
        }
    };

    // 包装不继承自Node的类
    template <typename _Ty> class WrappedNode : public Node {
    protected:
        std::unique_ptr<_Ty> content_;
    public:
        explicit WrappedNode(_Ty content_)
            : Node(), content_(new _Ty(std::move(content_)))
        {
        }
        virtual std::string getAstString(std::string prefix = "") const
        {
            return content_ ? content_->getAstString(prefix) : ":(";
        }
        virtual bool valid() const { return content_.operator bool(); }
    };
}

#endif // !_EPAT_NODE_H_
