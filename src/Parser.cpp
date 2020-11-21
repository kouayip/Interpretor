#include "../include/Parser.hpp"

Parser::Parser(std::string const(&buff)) throw() : lexer_{buff}
{
    currentToken_ = lexer_.getNextToken();
}

auto Parser::error()
{
    return std::string("Type error"); //TODO: Refactor code to create a generic class Error
}

void Parser::consume(TokenType const(&type))
{
    if (currentToken_.type() == type)
    {
        currentToken_ = lexer_.getNextToken();
    }
    else
    {
        throw error();
    }
}

auto Parser::factor()
{
    if (currentToken_.type() == TokenType::INTEGER_NUM)
    {
        auto val{currentToken_.value()};
        consume(TokenType::INTEGER_NUM);
        return val;
    }
    else if (currentToken_.type() == TokenType::FLOAT_NUM)
    {
        auto val{currentToken_.value()};
        consume(TokenType::FLOAT_NUM);
        return val;
    }
    throw error();
}

bool Parser::exp()
{
    auto left{factor()};

    consume(TokenType::PLUS_OP);

    auto right{factor()};

    Utils::print(left);
    Utils::print(right);

    return false;
}

Parser::~Parser()
{
}