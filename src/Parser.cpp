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

Node *Parser::factor()
{
    if (currentToken_.type() == TokenType::INTEGER_NUM ||
        currentToken_.type() == TokenType::FLOAT_NUM)
    {
        const auto token{currentToken_};
        if (currentToken_.type() == TokenType::INTEGER_NUM)
            consume(TokenType::INTEGER_NUM);
        else
            consume(TokenType::FLOAT_NUM);

        return new Num(token);
    }
    else if (currentToken_.type() == TokenType::LPAREN_SYM)
    {
        consume(TokenType::LPAREN_SYM);
        const auto node{exp()};
        consume(TokenType::RPAREN_SYM);
        return node;
    }
    throw error();
}

Node *Parser::term()
{
    auto node{factor()};

    while (currentToken_.type() == TokenType::MULT_OP ||
           currentToken_.type() == TokenType::DIV_OP ||
           currentToken_.type() == TokenType::MOD_OP)
    {
        auto token = currentToken_;
        if (currentToken_.type() == TokenType::MULT_OP)
            consume(TokenType::MULT_OP);
        else if (currentToken_.type() == TokenType::DIV_OP)
            consume(TokenType::DIV_OP);
        else if (currentToken_.type() == TokenType::MOD_OP)
            consume(TokenType::MOD_OP);
        node = new BinOp(node, token, factor());
    }
    return node;
}

Node *Parser::exp()
{
    auto node{term()};

    while (currentToken_.type() == TokenType::PLUS_OP ||
           currentToken_.type() == TokenType::MINUS_OP)
    {
        auto token = currentToken_;
        if (currentToken_.type() == TokenType::PLUS_OP)
            consume(TokenType::PLUS_OP);
        else if (currentToken_.type() == TokenType::MINUS_OP)
            consume(TokenType::MINUS_OP);

        node = new BinOp(node, token, term());
    }

    return node;
}

Parser::~Parser()
{
}