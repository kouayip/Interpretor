#if !defined(__TOKEN__)
#define __TOKEN__

#include <iostream>

enum TokenType
{
    //? Identifiers and literals
    ID,     // (identify)
    INUM,   // (Integer number)
    FNUM,   // (float number)
    STRING, // (string)

    //? Arithmetic Operator
    PLUS,  // (+)
    MINUS, // (-)
    MULT,  // (*)
    DIV,   // (/)
    MOD,   // (%)

    //? Special symbols
    LPAREN, // <)>
    RPAREN, // <(>
    LCURLY, // <{>
    RCURLY, // <}>
    COLON,  // <:>
    SEMI,   // <;>
    DOT,    // <.>

    //? Conditon operator
    LTHAN,   // (<)
    GTHAN,   // (>)
    EQUAL,   // (==)
    LTEQUAL, // (<=)
    GTEQUAL, // (>=)
    INEQUAL, // (!=)

    //? Assignment operator
    LASSIGN,  // (<-)
    RASSIGN,  // (->)
    LRASSIGN, // (<->)

    //? Keywords
    VAL,    // (val)
    CONST,  // (const)
    STRUCT, // (struct)
    IF,     // (if)
    ELSE,   // (else)
    ELSEIF, // (else if)
    FOR,    // (for)
    PRINT,  // (echo)
    READ,   // (read)

    //? Special tokens
    _EOF_, //* end of input
};

inline std::ostream &operator<<(std::ostream &op, TokenType type)
{
    switch (type)
    {
    case TokenType::ID:
        op << "ID";
        break;
    case TokenType::_EOF_:
        op << "EOF";
        break;
    default:
        op << "!!==!!";
        break;
    }
    return op;
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

    void print()
    {
        std::cout << "[ " << type_ << ":  " << value_ << ", " << location_.line << "::" << location_.col << " ]" << std::endl;
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