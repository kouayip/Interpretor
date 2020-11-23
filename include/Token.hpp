#if !defined(__TOKEN__)
#define __TOKEN__

#include <iostream>

enum TokenType
{
    INTEGER_NUM,
    FLOAT_NUM,
    //?Operator
    PLUS_OP,
    MINUS_OP,
    MULT_OP,
    DIV_OP,
    MOD_OP,
    //?Special symbols
    LPAREN_SYM,
    RPAREN_SYM,
    _EOF_,
};

struct Location
{
    int line = -1;
    int col = -1;
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