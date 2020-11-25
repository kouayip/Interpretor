#ifndef __AST__
#define __AST__

#include <iostream>
#include <typeinfo>
#include <vector>
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
    MULTASSIGN,
};

/**
 * AST node
 */
struct Node
{
    Node() : type_(NodeType::AST) {}

    Node(NodeType const(&type)) : type_(type) {}

    virtual std::string print() = 0;

    /**
     * Use to reveal real Node class
     */
    template <typename T>
    auto reveal()
    {
        return dynamic_cast<T>(this); //TODO: change afta to static_cast more booste perform
    };

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
 * Compound instructions
 * Represents an instruction group
 */
struct Block : Node
{
    virtual std::string print()
    {
        return "Block";
    }

    std::vector<Node *> children;
};

/**
 * Compound instructions
 * Represents an instruction group
 */
struct CompoundBlock : Node
{
};

/**
 * Program root
 */
struct Program : Node
{
    /**
     * @param name string
     * @param block Compound
     */
    Program(std::string const(&name), Node *block) : Node(NodeType::PROGRAM)
    {
    }

    virtual std::string print()
    {
        return "Program";
    }

    std::string name() const
    {
        return name_;
    }

    /**
     * @return Compound
     */
    Node *block() const
    {
        return block_;
    }

private:
    std::string name_;
    Node *block_;
};

/**
 * Assign assignment
 */
struct Assign : Node
{
    /**
     * @param left Var
     * @param op Token
     * @param right BinOp
     */
    Assign(Node *left, Token const(&op), Node *right) : left_(left), op_(op), right_(right), Node(NodeType::ASSIGN)
    {
    }

    virtual std::string print()
    {
        return "Assign";
    }

    /**
     * @return Token
     */
    const auto op() const
    {
        return op_;
    }

    /**
     * @return Var
     */
    const auto left() const
    {
        return left_;
    }

    /**
     * @return BinOp
     */
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
 * Multiple Assign assignment
 */
struct MultAssign : Node
{
    /**
     * @param left Vector
     * @param op Token
     * @param right BinOp
     */
    MultAssign(Token const(&op), Node *right) : op_(op), right_(right), Node(NodeType::MULTASSIGN)
    {
    }

    virtual std::string print()
    {
        return "Assign";
    }

    /**
     * @return Token
     */
    const auto op() const
    {
        return op_;
    }

    /**
     * @return Var
     */
    const auto pushVar(Node *const(&node))
    {
        return left_.push_back(node);
    }

    /**
     * @return BinOp
     */
    const auto right() const
    {
        return right_;
    }

private:
    std::vector<Node *> left_;
    Token op_;
    Node *right_;
};

/**
 * Variable {val<type> and const<type>}
 */
struct Var : Node
{
    /**
     * @param token Token
     */
    Var(Token const(&token)) : token_(token), Node(NodeType::VAR)
    {
    }

    virtual std::string print()
    {
        return "Var";
    }

    // ? Return name of variable
    /**
     * @return string
     */
    const auto name()
    {
        return token_.value();
    }

    /**
     * @return string
     */
    const auto token()
    {
        return token_;
    }

private:
    Token token_;
};

struct VarType : Node
{
    /**
     * @param token Token
     */
    VarType(Token const(&token)) : token_(token), Node(NodeType::VARTYPE) {}

    // ? Return type of variable
    /**
     * @return string
     */
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
 * Variable Declaration <type>{x <- number,}
 * And define a type of variable
 */
struct VarDecl : Node
{
    /**
     * @param var VarType
     * @param type Var
     */
    VarDecl(Node *var, Node *type) : var_(var), type_(type), Node(NodeType::VARDECL) {}

    VarDecl(Node *var, Node *type, NodeType const(&nodeType)) : var_(var), type_(type), Node(nodeType) {}

    virtual std::string print()
    {
        return "VarDecl";
    }

    virtual Node *var() const
    {
        return this->var_;
    }

    virtual Node *type() const
    {
        return this->type_;
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
    /**
     * @param var VarType
     * @param type Var
     */
    ConstDecl(Node *var, Node *type) : VarDecl(var, type, NodeType::CONSTDECL) {}

    virtual std::string print()
    {
        return "VarDecl";
    }
};

/**
 * Value variable Declaration
 * Resove type of var afta affectation
 */
struct ValDecl : VarDecl
{
    /**
     * @param var VarType
     * @param type Var
     */
    ValDecl(Node *var, Node *type) : VarDecl(var, type, NodeType::AUTODECL) {}

    virtual std::string print()
    {
        return "AutoDecl";
    }
};

/**
 * Compound Declaration or Assignement;
 */
struct CompoundDecl : Node
{
    virtual std::string print()
    {
        return "Block";
    }

    std::vector<Node *> children;
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