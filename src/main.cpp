#include <iostream>

#include "../include/Parser.hpp"
#include "../include/Interpretor.hpp"

//TODO: Geret la gestion de la memoire des tree AST
int main(int argc, char **argv)
{
    if (argc < 2)
        return 0;

    try
    {
        // //? Test Lexer
        // Lexer lex{Tools::readFile(argv[1])};
        // while (true)
        // {
        //     auto token = lex.getNextToken();

        //     token.print();
        //     if (token.type() == TokenType::_EOF_)
        //         break;
        // }

        // return 0; //! test

        Parser parse{Tools::readFile(argv[1])};

        auto ast{parse.parse()};

        auto inter = Interpretor{};

        ast->printNode();

        inter.interpret(ast);

        Tools::freeTree(ast);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // auto elem = (*block)[0];

    return 0;
}