#ifndef __PARSER__
#define __PARSER__

#include <iostream>
#include "./Lexer.hpp"

class Parser
{
private:
    const Lexer lexer_;

public:
    Parser(std::string const(&buff)) throw();
    ~Parser();

    const auto parse();
};

#endif