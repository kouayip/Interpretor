#include "../include/Lexer.hpp"

#include "../include/Utils.hpp"

Lexer::Lexer(const std::string buff) throw() : buff_(buff), cursor_(0)
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
    return std::stoi(result);
}

void Lexer::getNextToken() //? Update laster
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

        //* Check a current char is digit
        if (std::isdigit(currentChar_))
        {
            Utils::print(integer());
            continue; //TODO: Change continue to return new token
        }

        Utils::print(currentChar_);
        advance();
    }
}

Lexer::~Lexer()
{
}