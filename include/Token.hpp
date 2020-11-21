#if !defined(__TOKEN__)
#define __TOKEN__

#include <iostream>

enum TokenType
{
    INTEGER_NUM,
    FLOAT_NUM,
    PLUS_OP,
    MINUS_OP,
    MULT_OP,
    DIV_OP,
    MOD_OP,
    _EOF_,
};

struct Location
{
    int line;
    int col;
};

struct Token
{
private:
    TokenType type_;
    std::string value_;
    Location location_;

public:
    Token() {}

    Token(TokenType const(&type), std::string const(&value), Location const(&location))
    {
        type_ = type;
        value_ = value;
        location_ = location;
    }

    Token(TokenType const(&type), char const(&value), Location const(&location))
        : type_(type), value_{value}, location_(location) {}

    const auto type() const
    {
        return type_;
    }

    const auto value() const
    {
        return value_;
    }

    const auto location() const
    {
        return location_;
    }
};

inline std::ostream &operator<<(std::ostream &out, Location const(&token))
{
    out << '{'
        << "line: "
        << token.line
        << ", "
        << "column: "
        << token.col
        << '}';

    return out;
};

inline std::ostream &operator<<(std::ostream &out, Token const(&token))
{
    out << '{'
        << "type: "
        << token.type()
        << ", "
        << "value: "
        << token.value()
        << ", location: "
        << token.location()
        << '}'
        << std::endl;

    return out;
};

#endif