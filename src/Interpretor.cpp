#include "../include/Interpretor.hpp"

void Interpretor::close(Node *node)
{
    delete node;
    node = nullptr;
}

auto Interpretor::visitNodeNum(Num *num)
{
    return num->value();
}

auto Interpretor::visitNode(Node *node)
{
    if (node->type() == NodeType::BINOP)
    {
        const auto result = visitNodeBinOp(static_cast<BinOp *>(node));
        close(node); //! Create Asyn delete;
        return result;
    }
    else if (node->type() == NodeType::NUM)
    {
        const auto result = visitNodeNum(static_cast<Num *>(node));
        close(node); //! Create Asyn delete;
        return result;
    }
    else if (node->type() == NodeType::UNARYOP)
    {
        const auto result = visitUnaryOp(static_cast<UnaryOp *>(node));
        close(node); //! Create Asyn delete;
        return result;
    }
    throw "Error type node";
}

double Interpretor::visitUnaryOp(UnaryOp *node)
{
    if (node->op().type() == TokenType::PLUS)
        return +visitNode(node->expr());
    else
        return -visitNode(node->expr());
}

double Interpretor::visitNodeBinOp(BinOp *node)
{
    switch (node->op().type())
    {
    case TokenType::PLUS:
        return visitNode(node->left()) + visitNode(node->right());
        break;

    case TokenType::MINUS:
        return visitNode(node->left()) - visitNode(node->right());
        break;

    case TokenType::MULT:
        return visitNode(node->left()) * visitNode(node->right());
        break;

    case TokenType::DIV:
        return visitNode(node->left()) / visitNode(node->right());
        break;

    case TokenType::MOD:
        return (int)visitNode(node->left()) % (int)visitNode(node->right());
        break;

    default:
        throw "Error Bin Op";
        break;
    }
}

double Interpretor::interpret(Node *node)
{
    return visitNode(node);
}

Interpretor::~Interpretor()
{
}