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
    const TokenType type;
    const std::string value;
    const Location location;
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
        << token.type
        << ", "
        << "value: "
        << token.value
        << ", location: "
        << token.location
        << '}'
        << std::endl;

    return out;
};

#endif