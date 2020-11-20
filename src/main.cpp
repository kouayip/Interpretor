#include <iostream>

#include "../include/Lexer.hpp"
#include "../include/Asset.hpp"

int main()
{
    auto source{" 12.24  \n   \n+  \n 23"};

    Lexer lex{source};

    Asset::equals(lex.getNextToken().value, "12.24");
    Asset::equals(lex.getNextToken().value, "+");
    Asset::equals(lex.getNextToken().value, "23");
    Asset::equals(lex.getNextToken().value, "\0");
}