#ifndef __PARSER__
#define __PARSER__

#include <iostream>
#include "Lexer.hpp"
#include "./Utils.hpp"

class Parser
{
private:
    Lexer lexer_;
    Token currentToken_;

    auto error();
    void consume(TokenType const(&type));
    auto factor();
    auto term();

public:
    Parser(std::string const(&buff)) throw();
    ~Parser();

    bool exp();
    auto parse(); //? Change return type
};

#endif