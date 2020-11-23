#ifndef __PARSER__
#define __PARSER__

#include <iostream>
#include "Lexer.hpp"
#include "./Utils.hpp"
#include "./AST.hpp"

class Parser
{
private:
    Lexer lexer_;
    Token currentToken_;

    auto error();
    void consume(TokenType const(&type));
    Node *factor();
    Node *term();

public:
    Parser(std::string const(&buff)) throw();
    ~Parser();

    Node *exp();
    auto parse(); //? Change return type
};

#endif