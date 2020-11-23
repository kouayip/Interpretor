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
    if (node->type() == NodeType::OP)
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
    else if (node->type() == NodeType::Unary)
    {
        const auto result = visitUnaryOp(static_cast<UnaryOp *>(node));
        close(node); //! Create Asyn delete;
        return result;
    }
    throw "Error type node";
}

double Interpretor::visitUnaryOp(UnaryOp *node)
{
    if (node->op().type() == TokenType::PLUS_OP)
        return +visitNode(node->expr());
    else
        return -visitNode(node->expr());
}

double Interpretor::visitNodeBinOp(BinOp *node)
{
    switch (node->op().type())
    {
    case TokenType::PLUS_OP:
        return visitNode(node->left()) + visitNode(node->right());
        break;

    case TokenType::MINUS_OP:
        return visitNode(node->left()) - visitNode(node->right());
        break;

    case TokenType::MULT_OP:
        return visitNode(node->left()) * visitNode(node->right());
        break;

    case TokenType::DIV_OP:
        return visitNode(node->left()) / visitNode(node->right());
        break;

    case TokenType::MOD_OP:
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