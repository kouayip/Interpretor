#if !defined(__TOKEN__)
#define __TOKEN__

#include <iostream>

enum TokenType
{
    //?Identifier
    ID, //* [a-bA-B]+[a-bA-B-0-9]

    //?Number
    INTEGER_NUM, //* [0-9]+
    FLOAT_NUM,   //* [0-9]+.[0-9]+

    //?Operator
    PLUS_OP,  //* +
    MINUS_OP, //* -
    MULT_OP,  //**
    DIV_OP,   //* /
    MOD_OP,   //* %

    //?Special symbols
    LPAREN_SYM, //* )
    RPAREN_SYM, //* (
    LCURLY_SYM, //* {
    RCURLY_SYM, //* }
    ASSIGN_SYM, //* =
    COLON_SYM,  //* :
    SEMI_SYM,   //* ;
    DOT_SYM,    //* .

    //? Keywords
    SET_KWD,  //* set
    ECHO_KWD, //* echo
    READ_KWD, //* read

    //? HTML Keywords
    DIV, //* <div>

    //?
    _EOF_, //* end line
};

inline std::ostream &operator<<(std::ostream &op, TokenType type)
{
    switch (type)
    {
    case TokenType::ID:
        op << "ID";
        break;
    case TokenType::INTEGER_NUM:
        op << "INTEGER";
        break;
    case TokenType::FLOAT_NUM:
        op << "FLOAT";
        break;
    case TokenType::PLUS_OP:
        op << "PLUS";
        break;
    case TokenType::MINUS_OP:
        op << "MINUS";
        break;
    case TokenType::MULT_OP:
        op << "MULT";
        break;
    case TokenType::DIV_OP:
        op << "DIV";
        break;
    case TokenType::MOD_OP:
        op << "MOD";
        break;
    case TokenType::LPAREN_SYM:
        op << "LPAREN";
        break;
    case TokenType::RPAREN_SYM:
        op << "RPAREN";
        break;
    case TokenType::LCURLY_SYM:
        op << "LCURLY";
        break;
    case TokenType::RCURLY_SYM:
        op << "RCURLY";
        break;
    case TokenType::SET_KWD:
        op << "SET";
        break;
    case TokenType::READ_KWD:
        op << "READ";
        break;
    case TokenType::ECHO_KWD:
        op << "ECHO";
        break;
    case TokenType::SEMI_SYM:
        op << "SEMI";
        break;
    case TokenType::ASSIGN_SYM:
        op << "ASSIGN";
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