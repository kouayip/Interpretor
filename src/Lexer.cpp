#include "../include/Lexer.hpp"

#include "../include/Utils.hpp"

Lexer::Lexer(const std::string buff) throw() : buff_(buff), cursor_(0)
{
    currentChar_ = buff[cursor_];
    buffSize_ = buff.size() - 1;
}

void Lexer::skipWhitespace()
{
    while (currentChar_ != '\0' && std::isspace(currentChar_))
    {
        advance();
    }
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

void Lexer::getNextToken() //? Update laster
{
    while (currentChar_ != '\0')
    {
        if (std::isspace(currentChar_))
        {
            advance();
            skipWhitespace();
            continue;
        }
        Utils::print(currentChar_);
        advance();
    }
}

Lexer::~Lexer()
{
}