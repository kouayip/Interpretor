#if !defined(__TOKEN__)
#define __TOKEN__

#include <iostream>

enum TokenType
{
    //? Identifiers and literals
    ID,   // (identify)
    INUM, // (Integer number)
    FNUM, // (float number)

    //? Identity type of var
    INTEGER, // (int)
    REAL,    // (float)
    STRING,  // (string)
    BOOL,    // (boolean)
    AUTO,    // (auto)

    //? Identity type function
    FUNC, // (func)

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
    COMMA,  // <,>
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

//! Helper print token type
inline std::ostream &operator<<(std::ostream &op, TokenType type)
{
    switch (type)
    {
    case TokenType::ID:
        op << "ID";
        break;
    case TokenType::INUM:
        op << "INUM";
        break;
    case TokenType::FNUM:
        op << "FNUM";
        break;
    case TokenType::STRING:
        op << "STRING";
        break;
    case TokenType::INTEGER:
        op << "INTEGER";
        break;
    case TokenType::REAL:
        op << "REAL";
        break;
    case TokenType::BOOL:
        op << "BOOL";
        break;
    case TokenType::AUTO:
        op << "AUTO";
        break;
    case TokenType::FUNC:
        op << "FUNC";
        break;
    case TokenType::PLUS:
        op << "PLUS";
        break;
    case TokenType::MINUS:
        op << "MINUS";
        break;
    case TokenType::MULT:
        op << "MULT";
        break;
    case TokenType::DIV:
        op << "DIV";
        break;
    case TokenType::LPAREN:
        op << "LPAREN";
        break;
    case TokenType::RPAREN:
        op << "RPAREN";
        break;
    case TokenType::LCURLY:
        op << "LCURLY";
        break;
    case TokenType::RCURLY:
        op << "RCURLY";
        break;
    case TokenType::COMMA:
        op << "COMMA";
        break;
    case TokenType::SEMI:
        op << "SEMI";
        break;
    case TokenType::LTHAN:
        op << "LTHAN";
        break;
    case TokenType::GTHAN:
        op << "GTHAN";
        break;
    case TokenType::LASSIGN:
        op << "LASSIGN";
        break;
    case TokenType::VAL:
        op << "VAL";
        break;
    case TokenType::CONST:
        op << "CONST";
        break;
    case TokenType::PRINT:
        op << "PRINT";
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