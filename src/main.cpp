#include <iostream>
// #include <chrono>
// #include <ctime>

#include "../include/Parser.hpp"
#include "../include/Interpretor.hpp"

//TODO: Geret la gestion de la memoire des tree AST
int main(int argc, char **argv)
{
    try
    {
        if (argc < 2)
            return 0;

        // auto start = std::chrono::system_clock::now();

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

        std::cout << std::endl;

        inter.interpret(ast);

        Tools::freeTree(ast);

        // auto end = std::chrono::system_clock::now();

        // std::chrono::duration<double> elapsed_seconds = end - start;
        // std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        // std::cout << "finished compilation at " << std::ctime(&end_time)
        //           << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // auto elem = (*block)[0];

    return 0;
}