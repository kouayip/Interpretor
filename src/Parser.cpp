#include "../include/Parser.hpp"

Parser::Parser(std::string const(&buff)) throw() : lexer_{buff}
{
    currentToken_ = lexer_.getNextToken();
}

auto Parser::error()
{
    // return std::string("Type error"); //TODO: Refactor code to create a generic class Error
    return std::runtime_error("Type error");
}

void Parser::consume(TokenType const(&type))
{
    Utils::print(currentToken_); //! Test

    if (currentToken_.type() == type)
    {
        currentToken_ = lexer_.getNextToken();
    }
    else
    {
        throw error();
    }
}

Node *Parser::variable()
{
    auto token{currentToken_};
    consume(TokenType::ID);
    return new Var(token);
}

Node *Parser::program()
{
    //? Consume a declaration start program
    consume(TokenType::LPAREN_SYM);
    consume(TokenType::LPAREN_SYM);

    auto condition = true;
    while (condition)
    {
        switch (currentToken_.type())
        {
        case TokenType::SET_KWD:
            consume(TokenType::SET_KWD);
            break;

        default:
            condition = false;
            break;
        }
    }

    //? Consume a declaration end program
    consume(TokenType::RPAREN_SYM);
    consume(TokenType::RPAREN_SYM);

    //! Program content a block intructions
    return new Program();
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
    else if (currentToken_.type() == TokenType::PLUS_OP ||
             currentToken_.type() == TokenType::MINUS_OP)
    {
        const auto token{currentToken_};
        if (currentToken_.type() == TokenType::PLUS_OP)
            consume(TokenType::PLUS_OP);
        else
            consume(TokenType::MINUS_OP);
        return new UnaryOp{token, expr()};
    }
    else if (currentToken_.type() == TokenType::LPAREN_SYM)
    {
        consume(TokenType::LPAREN_SYM);
        const auto node{expr()};
        consume(TokenType::RPAREN_SYM);
        return node;
    }
    else
    {
        return variable();
    }
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

Node *Parser::expr()
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

Node *Parser::parse()
{
    auto tree{program()};
    if (currentToken_.type() != TokenType::_EOF_)
        throw error();
    return tree;
}

Parser::~Parser()
{
}