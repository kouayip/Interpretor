#include <iostream>

#include "../include/Lexer.hpp"
#include "../include/Asset.hpp"

int main()
{
    auto source{"12     +   23"};

    Lexer lex{source};

    Asset::equals(lex.getCurrentChar(), '1');
    Asset::equals(lex.look(), '2');
    lex.getNextToken();
    Asset::equals(lex.getCurrentChar(), '\0');
}