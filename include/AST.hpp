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
    BLOCK,
    VAR,
    VARDECL,
    CONSTDECL,
    VALDECL,
    VARTYPE,
    DECL,
    ASSIGN,
    MULTASSIGN,
    COMPOUNDDECL,
    EMPTY,
};

/**
 * AST node
 */
class Node
{
public:
    Node() : type_(NodeType::AST) {}

    Node(NodeType const(&type)) : type_(type) {}

    ~Node()
    {
        // std::cout << "(-) Node" << std::endl;
    }

    virtual std::string print() = 0;

    /**
     * Print Node for genered a AST Tree view
     */
    virtual void printNode(std::string space = "", std::string prefix = "") const = 0;

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

class Empty : public Node
{
public:
    Empty()
    {
        type_ = NodeType::EMPTY;
    }

    virtual std::string print()
    {
        return "Empty";
    }

    virtual void printNode(std::string space, std::string prefix) const
    {
        std::cout << space << "└── "
                  << "Empty" << std::endl;
    }
};

/**
 * Num node
 */
class Num : public Node
{
public:
    Num(Token const(&token)) : token_(token), Node(NodeType::NUM)
    {
        value_ = std::stod(token.value());
    }

    ~Num()
    {
        // std::cout << "(-) Num" << std::endl;
    }

    virtual std::string print()
    {
        return "Num";
    }

    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << space << prefix << "Num<" << token_.value() << ">" << std::endl;
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
class BinOp : public Node
{
public:
    BinOp(Node *left, Token const(&op), Node *right) : left_(left), op_(op), right_(right)
    {
        type_ = NodeType::BINOP;
    }

    ~BinOp()
    {
        // std::cout << "(-) BinOp" << std::endl;
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

    virtual std::string print()
    {
        return "BinOp";
    }

    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << space << prefix << "BinOp<" << op_.value() << ">" << std::endl;
        left_->printNode(space + "│    ", "├── ");
        right_->printNode(space + "│    ", "├── ");
    }

private:
    Node *left_;
    Token op_;
    Node *right_;
};

/**
 * Unary operator
 */
class UnaryOp : public Node
{
public:
    UnaryOp(Token const(&token), Node *expr) : op_(token), expr_(expr)
    {
        type_ = NodeType::UNARYOP;
    }

    ~UnaryOp()
    {
        // std::cout << "(-) UnaryOp" << std::endl;
    }

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

    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << space << prefix << "Unary<" << op_.value() << ">" << std::endl;
        expr_->printNode(space + "│    ", "├── ");
    }

private:
    Token op_;
    Node *expr_;
};

/**
 * Compound instructions
 * Represents an instruction group
 */
class Block : public Node
{
private:
    std::vector<Node *> children_;

public:
    Block()
    {
        this->type_ = NodeType::BLOCK;
    }

    Block(std::vector<Node *> children) : children_(children)
    {
        this->type_ = NodeType::BLOCK;
    }

    ~Block()
    {
        // std::cout << "(-) Block" << std::endl;
        // for (size_t i = 0; i < children_.size(); i++)
        // {
        //     delete children_[i];
        //     children_[i] = nullptr;
        // }

        children_.clear();
    }

    void append(Node *const &child)
    {
        children_.push_back(child);
    }

    inline Node *operator[](std::size_t idx) noexcept
    {
        return children_[idx];
    }

    const int size() noexcept
    {
        return children_.size();
    }

    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << space << prefix << "Block" << std::endl;
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->printNode(space + "│    ", "├── ");
        }
    }

    virtual std::string print()
    {
        return "Block";
    }
};

/**
 * Compound instructions
 * Represents an instruction group
 */
class CompoundBlock : public Node
{
};

/**
 * Program root
 */
class Program : public Node
{
private:
    std::string name_;
    Node *block_;

public:
    /**
     * @param name string
     * @param block Compound
     */
    Program(std::string const(&name), Node *const &block) : name_(name), block_(block)
    {
        type_ = NodeType::PROGRAM;
    }

    ~Program()
    {
        // std::cout << "(-) Program" << std::endl;
    }

    virtual std::string print()
    {
        return "Program";
    }

    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << "Program" << std::endl;
        block_->printNode(space, "├── ");
    }

    std::string name() noexcept
    {
        return name_;
    }

    /**
     * @return Compound
     */
    const auto block() noexcept
    {
        return block_;
    }
};

/**
 * Assign assignment
 */
class Assign : public Node
{
public:
    /**
     * @param left Var
     * @param op Token
     * @param right BinOp
     */
    Assign(Node *left, Token const(&op), Node *right) : left_(left), op_(op), right_(right)
    {
        type_ = NodeType::ASSIGN;
    }

    ~Assign()
    {
        // std::cout << "(-) Assign" << std::endl;
    }

    virtual std::string print()
    {
        return "Assign";
    }

    //├──
    //└──
    //│
    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << space << prefix << "Assign" << std::endl;
        left_->printNode(space + "│    ", "├── ");
        right_->printNode(space + "│    ", "├── ");
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
class MultAssign : public Node
{
private:
    std::vector<Node *> left_;
    Token op_;
    Node *right_;

public:
    /**
     * @param left Vector
     * @param op Token
     * @param right BinOp
     */
    MultAssign(Token const(&op), Node *right) : op_(op), right_(right)
    {
        type_ = NodeType::MULTASSIGN;
    }

    MultAssign(std::vector<Node *> left, Token const(&op), Node *right) : left_(left), op_(op), right_(right)
    {
        type_ = NodeType::MULTASSIGN;
    }

    ~MultAssign()
    {
        // std::cout << "(-) MultAssign" << std::endl;
        left_.clear();
    }

    void append(Node *const &child)
    {
        left_.push_back(child);
    }

    inline Node *operator[](std::size_t idx) noexcept
    {
        return left_[idx];
    }

    const int size() noexcept
    {
        return left_.size();
    }

    virtual std::string print()
    {
        return "Assign";
    }

    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << space << prefix << "MultAssign" << std::endl;
        for (size_t i = 0; i < left_.size(); i++)
        {
            left_[i]->printNode(space + "│    ", "├── ");
        }
        right_->printNode(space + "│    ", "├── ");
    }

    /**
     * @return Token
     */
    const auto op() const
    {
        return op_;
    }

    /**
     * @return Token
     */
    auto left() const
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
};

/**
 * Variable {val<type> and const<type>}
 */
class Var : public Node
{
private:
    Token token_;

public:
    /**
     * @param token Token
     */
    Var(Token const(&token)) : token_(token)
    {
        type_ = NodeType::VAR;
    }

    ~Var()
    {
        // std::cout << "(-) Var" << std::endl;
    }

    virtual std::string print()
    {
        return "Var";
    }

    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << space << prefix << "Var<" << token_.value() << ">" << std::endl;
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
};

/**
 * VarType
 */
class VarType : public Node
{
public:
    /**
     * @param token Token
     */
    VarType(Token const(&token)) : token_(token)
    {
        type_ = NodeType::VARTYPE;
    }

    ~VarType()
    {
        // std::cout << "(-) VarType" << std::endl;
    }

    // ? Return type of variable
    /**
     * @return string
     */
    const auto type()
    {
        return token_.value();
    }

    const auto token()
    {
        return token_;
    }

    virtual std::string print()
    {
        return "VarType";
    }

    //├──
    //└──
    //│
    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << space << prefix << "VarType<" << token_.value() << ">" << std::endl;
    }

private:
    Token token_;
};

/**
 * Variable Declaration <type>{x <- number,}
 * And define a type of variable
 */
class VarDecl : public Node
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

    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << prefix << "VarDecl" << std::endl;
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
class ConstDecl : public Node
{
public:
    /**
     * @param var VarType
     * @param type Var
     */
    ConstDecl(Node *var, Node *type) : var_(var), type_(type)
    {
        Node::type_ = NodeType::CONSTDECL;
    }

    virtual std::string print()
    {
        return "ConstDecl";
    }

    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << space << prefix << "ConstDecl" << std::endl;
        var_->printNode(space + "│    ", "├── ");
        type_->printNode(space + "│    ", "└── ");
    }

    auto *var() const
    {
        return this->var_;
    }

    auto *type() const
    {
        return this->type_;
    }

private:
    Node *var_;
    Node *type_;
};

/**
 * Value variable Declaration
 * Resove type of var afta affectation
 */
class ValDecl : public Node
{
private:
    Node *var_;
    Node *type_;

public:
    /**
     * @param var VarType
     * @param type Var
     */
    ValDecl(Node *var, Node *type) : var_(var), type_(type)
    {
        Node::type_ = NodeType::VALDECL;
    }

    ~ValDecl()
    {
        // std::cout << "(-) ValDecl" << std::endl;
    }

    virtual std::string print()
    {
        return "ValDecl";
    }

    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << space << prefix << "ValDecl" << std::endl;
        var_->printNode(space + "│    ", "├── ");
        type_->printNode(space + "│    ", "└── ");
    }

    const auto var() noexcept
    {
        return this->var_;
    }

    const auto type() noexcept
    {
        return this->type_;
    }
};

/**
 * Compound Declaration or Assignement;
 */
class CompoundDecl : public Node
{
public:
    CompoundDecl()
    {
        type_ = NodeType::COMPOUNDDECL;
    }

    CompoundDecl(std::vector<Node *> children) : children_(children)
    {
        this->type_ = NodeType::COMPOUNDDECL;
    }

    ~CompoundDecl()
    {
        // std::cout << "(-) CompoundDecl" << std::endl;
        children_.clear();
    }

    void append(Node *const &child)
    {
        children_.push_back(child);
    }

    inline Node *operator[](std::size_t idx) noexcept
    {
        return children_[idx];
    }

    const int size() noexcept
    {
        return children_.size();
    }

    virtual std::string print()
    {
        return "CompoundDecl";
    }

    virtual void printNode(std::string space = "", std::string prefix = "") const
    {
        std::cout << space << prefix << "CompoundDecl" << std::endl;
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->printNode(space + "│    ", "├── ");
        }
    }

private:
    std::vector<Node *> children_;
};

#endif