#include "../include/Lexer.hpp"

#include "../include/Utils.hpp"

Lexer::Lexer(const std::string buff) throw() : buff_(buff), cursor_(0), ligne_(1)
{
    currentChar_ = buff[cursor_];
    buffSize_ = buff.size() - 1;
}

void Lexer::advance()
{
    cursor_ += 1;
    if (cursor_ > buffSize_)
    {
        currentChar_ = '\0';
    }
    else
    {
        currentChar_ = buff_[cursor_];
        if (currentChar_ == '\n')
            ligne_ += 1;
    }
}

const char Lexer::getCurrentChar() const
{
    return currentChar_;
}

const char Lexer::look() const
{
    auto cursorLook(cursor_ + 1);
    if (cursorLook > buffSize_)
    {
        return '\0';
    }
    return buff_[cursorLook];
}

void Lexer::skipWhitespace()
{
    while (currentChar_ != '\0' && std::isspace(currentChar_))
    {
        advance();
    }
}

auto Lexer::integer()
{
    std::string result("");
    while (currentChar_ != '\0' && std::isdigit(currentChar_))
    {
        result += currentChar_;
        advance();
    }
    //// return std::stoi(result);
    return result;
}

auto Lexer::number()
{
    const Location loc{ligne_, cursor_};
    std::string result(integer());
    if (currentChar_ == '.')
    {
        result += currentChar_;
        advance();
        result += integer();
        return Token{TokenType::FLOAT_NUM, result, loc};
    }
    return Token{TokenType::INTEGER_NUM, result, loc};
}

Token Lexer::getNextToken() //? Update laster
{
    while (currentChar_ != '\0')
    {
        //* Check a current char is white-space characters
        if (std::isspace(currentChar_))
        {
            advance();
            skipWhitespace();
            continue;
        }

        const Location loc{ligne_, cursor_};

        //* Check a current char is digit
        if (std::isdigit(currentChar_))
        {
            return number();
        }

        /**
         * Literals
         * * Op {+,-,*,/,%}
         */

        switch (currentChar_)
        {
        case '+':
            advance();
            return Token{TokenType::PLUS_OP, "+", loc};
        case '-':
            advance();
            return Token{TokenType::MINUS_OP, "-", loc};
        case '*':
            advance();
            return Token{TokenType::MULT_OP, "*", loc};
        case '/':
            advance();
            return Token{TokenType::DIV_OP, "/", loc};
        case '%':
            advance();
            return Token{TokenType::MOD_OP, "%", loc};
        default:
            throw "Syntax error";
            break;
        }
    }
    return Token{TokenType::_EOF_, "\0", Location{ligne_, cursor_}};
}

Lexer::~Lexer()
{
}