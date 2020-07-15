#pragma once

#include <vector>
#include <memory>
#include <string_view>

namespace elephant
{

    /// AST base class
    class AST {
    public:
        virtual ~AST() {}
    };

    /// NumberExprAST - Expression class for numeric literals like "1.0".
    class NumberExprAST : public AST {
        double m_val;

    public:
        NumberExprAST(double val) : m_val(val) {}
    };

    /// VariableExprAST - Expression class for referencing a variable, like "a".
    class VariableExprAST : public AST {
        std::string m_name;

    public:
        VariableExprAST(std::string_view name) : m_name(name) {}
    };

    /// BinaryExprAST - Expression class for a binary operator.
    class BinaryExprAST : public AST {
        char m_op;
        std::unique_ptr<AST> m_lhs, m_rhs;

    public:
        BinaryExprAST(char op, std::unique_ptr<AST> lhs,
            std::unique_ptr<AST> rhs)
            : m_op(op), m_lhs(std::move(lhs)), m_rhs(std::move(rhs)) {}
    };

    /// CallExprAST - Expression class for function calls.
    class CallExprAST : public AST {
        std::string m_callee;
        std::vector<std::unique_ptr<AST>> m_args;

    public:
        CallExprAST(const std::string& callee,
            std::vector<std::unique_ptr<AST>> args)
            : m_callee(callee), m_args(std::move(args)) {}
    };

    /// PrototypeAST - This class represents the "prototype" for a function,
    /// which captures its name, and its argument names (thus implicitly the number
    /// of arguments the function takes).
    class PrototypeAST {
        const std::string_view m_name;
        std::vector<std::string> m_args;

    public:
        PrototypeAST(std::string_view name, std::vector<std::string> args)
            : m_name(name), m_args(std::move(args)) {}

        constexpr const std::string_view get_name() const { return m_name; }
    };

    /// FunctionAST - This class represents a function definition itself.
    class FunctionAST {
        std::unique_ptr<PrototypeAST> m_proto;
        std::unique_ptr<AST> m_body;

    public:
        FunctionAST(std::unique_ptr<PrototypeAST> proto,
            std::unique_ptr<AST> body)
            : m_proto(std::move(proto)), m_body(std::move(body)) {}
    };

}