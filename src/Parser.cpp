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

float Parser::factor()
{
    if (currentToken_.type() == TokenType::INTEGER_NUM ||
        currentToken_.type() == TokenType::FLOAT_NUM)
    {
        const auto val{currentToken_.value()};
        if (currentToken_.type() == TokenType::INTEGER_NUM)
            consume(TokenType::INTEGER_NUM);
        else
            consume(TokenType::FLOAT_NUM);
        return std::stoi(val);
    }
    else if (currentToken_.type() == TokenType::LPAREN_SYM)
    {
        consume(TokenType::LPAREN_SYM);
        const auto val{exp()};
        consume(TokenType::RPAREN_SYM);
        return val;
    }
    throw error();
}

float Parser::term()
{
    auto result{factor()};

    while (currentToken_.type() == TokenType::MULT_OP ||
           currentToken_.type() == TokenType::DIV_OP)
    {
        if (currentToken_.type() == TokenType::MULT_OP)
        {
            consume(TokenType::MULT_OP);
            result *= factor();
        }
        else if (currentToken_.type() == TokenType::DIV_OP)
        {
            consume(TokenType::DIV_OP);
            result /= factor();
        }
    }
    return result;
}

float Parser::exp()
{
    auto result{term()};

    while (currentToken_.type() == TokenType::PLUS_OP ||
           currentToken_.type() == TokenType::MINUS_OP)
    {
        if (currentToken_.type() == TokenType::PLUS_OP)
        {
            consume(TokenType::PLUS_OP);
            result += term();
        }
        else if (currentToken_.type() == TokenType::MINUS_OP)
        {
            consume(TokenType::MINUS_OP);
            result -= term();
        }
    }

    return result;
}

Parser::~Parser()
{
}