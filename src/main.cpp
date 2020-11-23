#include <iostream>
#include <vector>

#include "../include/Parser.hpp"
#include "../include/Interpretor.hpp"
#include "../include/Asset.hpp"
#include "../include/Type.hpp"

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
    //? 5 - - - + - (3 + 4) - +2 = 10
    auto source{"7 + 3 * (10 / (12 / (3 + 1) - 1)) / (2 + 3) - 5 - 3 + (8)"}; // 10

    Parser parse{source};

    auto ast{parse.parse()};

    auto inter = Interpretor{};

    Utils::print(inter.interpret(ast));

    // remove(ast);
    // inter.clearRes();

    return 0;
}