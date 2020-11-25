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
    consume(TokenType::LPAREN);
    consume(TokenType::LPAREN);

    auto condition = true;
    while (condition)
    {
        switch (currentToken_.type())
        {
        case TokenType::VAL:
            consume(TokenType::VAL);
            break;

        default:
            condition = false;
            break;
        }
    }

    //? Consume a declaration end program
    consume(TokenType::RPAREN);
    consume(TokenType::RPAREN);

    //! Program content a block intructions
    return new Program();
}

Node *Parser::factor()
{
    if (currentToken_.type() == TokenType::INUM ||
        currentToken_.type() == TokenType::FNUM)
    {
        const auto token{currentToken_};
        if (currentToken_.type() == TokenType::INUM)
            consume(TokenType::INUM);
        else
            consume(TokenType::FNUM);

        return new Num(token);
    }
    else if (currentToken_.type() == TokenType::PLUS ||
             currentToken_.type() == TokenType::MINUS)
    {
        const auto token{currentToken_};
        if (currentToken_.type() == TokenType::PLUS)
            consume(TokenType::PLUS);
        else
            consume(TokenType::MINUS);
        return new UnaryOp{token, expr()};
    }
    else if (currentToken_.type() == TokenType::LPAREN)
    {
        consume(TokenType::LPAREN);
        const auto node{expr()};
        consume(TokenType::RPAREN);
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

    while (currentToken_.type() == TokenType::MULT ||
           currentToken_.type() == TokenType::DIV ||
           currentToken_.type() == TokenType::MOD)
    {
        auto token = currentToken_;
        if (currentToken_.type() == TokenType::MULT)
            consume(TokenType::MULT);
        else if (currentToken_.type() == TokenType::DIV)
            consume(TokenType::DIV);
        else if (currentToken_.type() == TokenType::MOD)
            consume(TokenType::MOD);
        node = new BinOp(node, token, factor());
    }
    return node;
}

Node *Parser::expr()
{
    auto node{term()};

    while (currentToken_.type() == TokenType::PLUS ||
           currentToken_.type() == TokenType::MINUS)
    {
        auto token = currentToken_;
        if (currentToken_.type() == TokenType::PLUS)
            consume(TokenType::PLUS);
        else if (currentToken_.type() == TokenType::MINUS)
            consume(TokenType::MINUS);

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