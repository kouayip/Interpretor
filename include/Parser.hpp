#ifndef __PARSER__
#define __PARSER__

#include <iostream>
#include "Lexer.hpp"
#include "./Utils.hpp"
#include "./Tools.hpp"
#include "./AST.hpp"

class Parser
{
private:
    Lexer lexer_;
    Token currentToken_;

    auto error(std::string msg);

    void consume(TokenType const(&type));

    /**
     * Statement
     */
    Node *statement();

    /**
     * Assignement
     */
    Node *assignStatement(Node *&var);

    Node *assignStatement();

    //
    Node *declarations();

    /**
     * Declaration val 
     */
    template <typename T>
    Node *varDeclaration(Node *&type);

    /**
     * Declaration const 
     */
    Node *constDeclaration();

    /**
     * Function declaration 
     */
    Node *funcDeclaration();

    /**
     * Function declaration 
     */
    Node *funcParameters();

    /**
     * Variable
     */
    Node *variable();

    /**
     * Variable
     */
    Node *typeSpec();

    /**
     * 
     */
    Node *block();

    /**
     * Programme root
     */
    Node *program();

    //? Calculator Node ?//

    /**
     * 
     */
    Node *factor();

    /**
     * 
     */
    Node *term();

    /**
     * Expression Calculator
     */
    Node *expr();

public:
    Parser(std::string const(&buff)) throw();
    ~Parser();
    Node *parse(); //? Change return type
};

#endif