#include <iostream>

#include "../include/Parser.hpp"
#include "../include/Asset.hpp"

void lexerTestValue()
{
    auto source{" 12.24  \n   \n+  \n 23"};
    Lexer lex{source};
    Asset::equals(lex.getNextToken().value(), std::string("12.24"));
    Asset::equals(lex.getNextToken().value(), std::string("+"));
    Asset::equals(lex.getNextToken().value(), std::string("23"));
}

int main()
{
    //? Run Assertion test

    auto source{" 12.24  \n   \n+  \n 23"};

    Parser parse{source};

    parse.exp();
}