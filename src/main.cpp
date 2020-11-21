#include <iostream>

#include "../include/Lexer.hpp"
#include "../include/Asset.hpp"

void lexerTestValue()
{
    auto source{" 12.24  \n   \n+  \n 23"};
    Lexer lex{source};
    Asset::equals(lex.getNextToken().value, std::string("12.24"));
    Asset::equals(lex.getNextToken().value, std::string("+"));
    Asset::equals(lex.getNextToken().value, std::string("23"));
}

void lexerTestLocationLine()
{
    auto source{" 12.24  \n   \n+  \n 23"};
    Lexer lex{source};
    Asset::equals(lex.getNextToken().location.line, 1);
    Asset::equals(lex.getNextToken().location.line, 3);
    Asset::equals(lex.getNextToken().location.line, 4);
}

void lexerTestLocationCol()
{
    auto source{" 12.24  \n   \n+  \n 23"};
    Lexer lex{source};
    Asset::equals(lex.getNextToken().location.col, 1);
    Asset::equals(lex.getNextToken().location.col, 0);
    Asset::equals(lex.getNextToken().location.col, 1);
}

int main()
{
    //? Run Assertion test
    lexerTestValue();
    lexerTestLocationLine();
    lexerTestLocationCol();

    auto source{" 12.24  \n   \n+  \n 23"};

    Lexer lex{source};

    Utils::print(lex.getNextToken());
    Utils::print(lex.getNextToken());
    Utils::print(lex.getNextToken());
    Utils::print(lex.getNextToken());
}