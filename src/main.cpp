#include <iostream>

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
    try
    {
        //? 7 + (((3 + 2))) = 12
        //? 5 - - - + - (3 + 4) - +2 = 10
        auto source{"((\n    const<int>\n{ x <- 10.8 + 9,\n y <- 3,};\n))\n"}; // 10

        //? Test Lexer
        Lexer lex{source};
        while (true)
        {
            auto token = lex.getNextToken();

            token.print();
            if (token.type() == TokenType::_EOF_)
                break;
        }

        return 0; //! test

        Parser parse{source};

        auto ast{parse.parse()};

        auto inter = Interpretor{};

        // Utils::print(inter.interpret(ast));

        // remove(ast);
        // inter.clearRes();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}