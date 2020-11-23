#include <iostream>
#include <vector>

#include "../include/Parser.hpp"
#include "../include/Asset.hpp"
#include "../include/Type.hpp"
#include "../include/AST.hpp"

template <typename T>
class Cache
{
private:
    const std::vector<T *> values_;

public:
    void add(T const(*elem))
    {
        values_.push_back(elem);
    }

    void clean()
    {
        for (auto elem : values_)
        {
            delete elem;
            elem = nullptr;
        }
        values_.clear();
    }
};

struct Interpretor
{
    auto visitNum(Num *num)
    {
        Utils::print(num->print());
        Utils::print(num->value());

        return num->value();
    }

    auto visit(Node *node)
    {
        cache_.add(node);

        if (node->type() == NodeType::OP)
        {
            BinOp *op = static_cast<BinOp *>(node);
            Utils::print(node->print());
            return visitBinOp(op);
        }
        else if (node->type() == NodeType::NUM)
        {
            Num *num = static_cast<Num *>(node);
            return visitNum(num);
        }
        throw "Error type node";
    }

    double visitBinOp(BinOp *node)
    {
        Utils::print(node->print());

        if (node->op().type() == TokenType::PLUS_OP)
            return visit(node->left()) + visit(node->right());
        else if (node->op().type() == TokenType::MINUS_OP)
            return visit(node->left()) - visit(node->right());
        else if (node->op().type() == TokenType::MULT_OP)
            return visit(node->left()) * visit(node->right());
        else if (node->op().type() == TokenType::DIV_OP)
            return visit(node->left()) / visit(node->right());
        else if (node->op().type() == TokenType::MOD_OP)
            return (int)visit(node->left()) % (int)visit(node->right());
        else
            throw "Error Bin Op";
    }

    void clearRes()
    {
        cache_.clean();
    }

private:
    Cache<Node> cache_;
};

void remove(Node *node)
{
    if (node->type() == NodeType::NUM)
    {
        delete node;
        node = nullptr;
    }
    else
    {
        BinOp *op = static_cast<BinOp *>(node);
        remove(op->left());
        remove(op->right());
        delete node;
        node = nullptr;
    }
}

//TODO: Geret la gestion de la memoire des tree AST
int main()
{
    //? 7 + (((3 + 2))) = 12
    auto source{"7 + 3 * (10 / (12 / (3 + 1) - 1)) / (2 + 3) - 5 - 3 + (8)"}; // 10

    Parser parse{source};

    auto ast{parse.exp()};

    auto inter = Interpretor{};

    Utils::print(inter.visit(ast));

    // remove(ast);
    inter.clearRes();

    return 0;
}