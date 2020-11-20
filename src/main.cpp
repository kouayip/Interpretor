#include <iostream>

#include "../include/Lexer.hpp"
#include "../include/Asset.hpp"

int main()
{
    auto source{"12  \n   \n+  \n 23"};

    Lexer lex{source};

    Asset::equals(lex.getCurrentChar(), '1');
    Asset::equals(lex.look(), '2');
    Utils::print(lex.getNextToken());
    auto token{lex.getNextToken()};
    Utils::print(token);
}