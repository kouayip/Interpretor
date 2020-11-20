#ifndef __LEXER__
#define __LEXER__

#include <iostream>
#include "./Token.hpp"

class Lexer
{
private:
    const std::string buff_; //? Is a buffer content all input source code
    int buffSize_;           //? Is a size of the buffer
    int cursor_;             //? Cursor to define a position to a buffer
    int ligne_;              //? Current line to cusor in buffer
    char currentChar_;       //? Is a current char of cursor to a buffer

    /**
     * Skip all occurence of space to buff in cursor position
     */
    void skipWhitespace();

    /**
     * Advance the cursor to the buffer
     * * Advance cursor and change a current position char to buffer
     * ? The methode update property {currentChar_, cursor_}
     */
    void advance();

    /**
     * The integer corresponds to all the digits
     * in the buffer at the cursor position up 
     * to a value other than one digit.
     * ? The methode update property {currentChar_, cursor_}
     */
    auto integer();

    /**
     * The Number allows the generation of a token of
     * {integer, float, double}
     */
    auto number();

public:
    //
    Lexer(const std::string buff) throw();
    ~Lexer();

    // Get current char to cursor position
    const char getCurrentChar() const;

    // Get next char to the next cursor position
    const char look() const;

    // Genered next token
    Token getNextToken(); // ? TODO: Change return type to Token type
};

#endif