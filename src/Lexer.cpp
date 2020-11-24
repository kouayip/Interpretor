#include "../include/Lexer.hpp"

#include "../include/Utils.hpp"

Lexer::Lexer(std::string const(&buff)) noexcept : buff_(buff), cursor_(0), ligne_(1), col_(1)
{
    currentChar_ = buff[cursor_];
    buffSize_ = buff.size() - 1;
}

void Lexer::throwError()
{
    auto l = std::to_string(ligne_);
    auto c = std::to_string(col_);
    throw std::runtime_error("Syntax error to the line:" + l + "::" + c);
}

auto Lexer::getLocation()
{
    return Location{ligne_, col_};
}

void Lexer::advance()
{
    cursor_ += 1;
    col_ += 1;
    if (cursor_ > buffSize_)
    {
        currentChar_ = '\0';
    }
    else
    {
        currentChar_ = buff_[cursor_];

        if (currentChar_ == '\n')
        {
            ligne_ += 1;
            col_ = 0;
        }
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

auto Lexer::identifier()
{
    const auto lt = getLocation();
    std::string result("");
    while (currentChar_ != '\0' && std::isalnum(currentChar_))
    {
        result += currentChar_;
        advance();
    }
    auto iter = keywords_.find(result);
    auto type = (iter != keywords_.end() ? iter->second : TokenType::ID);
    return Token{type, result, lt};
}

auto Lexer::integer()
{
    std::string result("");
    while (currentChar_ != '\0' && std::isdigit(currentChar_))
    {
        result += currentChar_;
        advance();
    }
    return result;
}

auto Lexer::number()
{
    const auto lt = getLocation();
    std::string result(integer());
    if (currentChar_ == '.')
    {
        result += currentChar_;
        advance();
        result += integer();
        return Token{TokenType::FLOAT_NUM, result, lt};
    }
    return Token{TokenType::INTEGER_NUM, result, lt};
}

const Token Lexer::getNextToken() //? Update laster
{
    while (currentChar_ != '\0')
    {
        //* Check a current char is white-space characters
        if (std::isspace(currentChar_))
        {
            advance();
            if (std::isspace(look()))
                skipWhitespace();
            continue;
        }

        //* Check a current char is digit
        if (std::isdigit(currentChar_))
        {
            return number();
        }

        //* Check a current char is alfa
        if (std::isalpha(currentChar_))
        {
            return identifier();
        }

        const auto lt = getLocation();

        /**
         * Literals
         * * Op {+,-,*,/,%}
         */

        switch (currentChar_)
        {
        case '+':
            advance();
            return Token{TokenType::PLUS_OP, '+', lt};
        case '-':
            advance();
            return Token{TokenType::MINUS_OP, '-', lt};
        case '*':
            advance();
            return Token{TokenType::MULT_OP, '*', lt};
        case '/':
            advance();
            return Token{TokenType::DIV_OP, '/', lt};
        case '%':
            advance();
            return Token{TokenType::MOD_OP, '%', lt};
        case '(':
            advance();
            return Token{TokenType::LPAREN_SYM, '(', lt};
        case ')':
            advance();
            return Token{TokenType::RPAREN_SYM, ')', lt};
        case '=':
            advance();
            return Token{TokenType::ASSIGN_SYM, '=', lt};
        case ';':
            advance();
            return Token{TokenType::SEMI_SYM, ';', lt};
        default:
            throwError();
            break;
        }
    }
    return Token{TokenType::_EOF_, "\0", getLocation()};
}

Lexer::~Lexer()
{
    keywords_.clear();
}