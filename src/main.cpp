#include <iostream>

#include "../include/Parser.hpp"
#include "../include/Asset.hpp"
#include "../include/Type.hpp"

auto glambda = [](auto a, auto &&b) { return a < b; };

void lexerTestValue()
{
    auto source{" 12.24  \n   \n+  \n 23"};
    Lexer lex{source};
    Asset::equals(lex.getNextToken().value(), std::string("12.24"));
    Asset::equals(lex.getNextToken().value(), std::string("+"));
    Asset::equals(lex.getNextToken().value(), std::string("23"));
}

template <typename T, typename V>
constexpr auto sum(T a, V b) -> decltype(a + b)
{
    return a + b;
}

int main()
{
    //? Test

    //? 7 + (((3 + 2))) = 12
    auto source{"7 + (((3 + 2)))"}; // 10

    Parser parse{source};

    Utils::print(parse.exp());

    return 0;
}