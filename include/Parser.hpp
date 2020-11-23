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
    float factor();
    float term();

public:
    Parser(std::string const(&buff)) throw();
    ~Parser();

    float exp();
    auto parse(); //? Change return type
};

#endif