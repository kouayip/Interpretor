#ifndef __AST__
#define __AST__

#include <iostream>
#include "Token.hpp"

enum NodeType
{
    AST = 99,
    NUM,
    BINOP,
    UNARYOP,
    PROGRAM,
    VAR,
    VARDECL,
    CONSTDECL,
    AUTODECL,
    VARTYPE,
    DECL,
    ASSIGN,
};

/**
 * AST node
 */
struct Node
{
    Node() : type_(NodeType::AST) {}

    Node(NodeType const(&type)) : type_(type) {}

    virtual std::string print() = 0;

    NodeType type() const
    {
        return type_;
    }

protected:
    NodeType type_;
};

/**
 * Num node
 * ? Is a node content number
 */
struct Num : Node
{
    Num(Token const(&token)) : token_(token), Node(NodeType::NUM)
    {
        value_ = std::stod(token.value());
    }

    virtual std::string print()
    {
        std::cout << value_ << std::endl;
        return "Num";
    }

    /**
     * Get a value the token
     * ? Return tokekn value convert 
     */
    auto value() const
    {
        return value_;
    }

    /**
     * Get a token
     * ? Return a current token use
     */
    const auto token() const
    {
        return token_;
    }

private:
    Token token_;
    double value_;
};

/**
 * Binary operator
 */
struct BinOp : Node
{
    BinOp(Node *left, Token const(&op), Node *right) : left_(left), op_(op), right_(right), Node(NodeType::BINOP) {}

    const auto op() const
    {
        return op_;
    }

    const auto left() const
    {
        return left_;
    }

    const auto right() const
    {
        return right_;
    }

    virtual std::string print()
    {
        return "BinOp";
    }

private:
    Node *left_;
    Token op_;
    Node *right_;
};

/**
 * Unary operator
 */
struct UnaryOp : Node
{
    UnaryOp(Token const(&token), Node *expr) : op_(token), expr_(expr), Node(NodeType::UNARYOP) {}

    const auto op() const
    {
        return op_;
    }

    const auto expr() const
    {
        return expr_;
    }

    virtual std::string print()
    {
        return "Unary";
    }

private:
    Token op_;
    Node *expr_;
};

/**
 * Program root
 */
struct Program : Node
{
    Program() : Node(NodeType::PROGRAM)
    {
    }

    virtual std::string print()
    {
        return "Program";
    }
    //! Programme content Node Block
};

/**
 * Assign affectection
 */
struct Assign : Node
{
    Assign(Node *left, Token const(&op), Node *right) : left_(left), op_(op), right_(right), Node(NodeType::ASSIGN)
    {
    }

    virtual std::string print()
    {
        return "Assign";
    }

    const auto op() const
    {
        return op_;
    }

    const auto left() const
    {
        return left_;
    }

    const auto right() const
    {
        return right_;
    }

private:
    Node *left_;
    Token op_;
    Node *right_;
};

/**
 * Variable {val<type> and const<type>}
 */
struct Var : Node
{
    Var(Token const(&token)) : token_(token), Node(NodeType::VAR)
    {
    }

    virtual std::string print()
    {
        return "Var";
    }

    // ? Return name of variable
    const auto name()
    {
        return token_.value();
    }

private:
    Token token_;
};

struct VarType : Node
{
    VarType(Token const(&token)) : token_(token), Node(NodeType::VARTYPE) {}

    // ? Return type of variable
    const auto type()
    {
        return token_.value();
    }

    virtual std::string print()
    {
        return "VarDecl";
    }

private:
    Token token_;
};

/**
 * Variable Declaration {x <- number,}
 * And define a type of variable
 */
struct VarDecl : Node
{
    VarDecl(Node *type, Node *var) : type_(type), var_(var), Node(NodeType::VARDECL) {}

    VarDecl(Node *type, Node *var, NodeType const(&nodeType)) : Node(nodeType) {}

    virtual std::string print()
    {
        return "VarDecl";
    }

    virtual const Node *type()
    {
        return this->type_;
    }

    virtual const Node *var()
    {
        return this->var_;
    }

protected:
    Node *type_;
    Node *var_;
};

/**
 * Constant variable Declaration
 */
struct ConstDecl : VarDecl
{
    ConstDecl(Node *type, Node *var) : VarDecl(type, var, NodeType::CONSTDECL) {}

    virtual std::string print()
    {
        return "VarDecl";
    }
};

/**
 * Automatique variable Declaration
 * Resove type of var afta affectation
 */
struct AutoDecl : VarDecl
{
    AutoDecl(Node *type, Node *var) : VarDecl(type, var, NodeType::AUTODECL) {}

    virtual std::string print()
    {
        return "VarDecl";
    }
};

//├──
//└──
//│
inline void
printTree(Node *node, const std::string &prefix)
{
    if (node == nullptr)
    {
        return;
    }
}

#endif