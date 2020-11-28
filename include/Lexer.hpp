#ifndef __LEXER__
#define __LEXER__

#include <iostream>
#include "./Token.hpp"
#include <map>
#include <stdexcept>

class Lexer
{
private:
    const std::string buff_; //? Is a buffer content all input source code
    int buffSize_;           //? Is a size of the buffer
    int cursor_;             //? Cursor to define a position to a buffer
    int ligne_;              //? Current line to cusor in buffer
    int col_;                //? Current col to cursor in buffor
    char currentChar_;       //? Is a current char of cursor to a buffer
    std::map<std::string, TokenType> keywords_ = {
        {"const", TokenType::CONST},
        {"val", TokenType::VAL},
        {"int", TokenType::INTEGER},
        {"string", TokenType::STRING},
        {"float", TokenType::REAL},
        {"auto", TokenType::AUTO},
    }; //? Is Defaut reserve keywords

    /**
     * Use to throw exception
     */
    void throwError();

    /**
     */
    auto getLocation();

    /**
     * Skip all occurence of space to buff in cursor position
     */
    void skipWhitespace();

    /**
     * Skip comment
     */
    void skipComment();

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
     * The identifier corresponds to value match to /[a-b][a-b0-9]/i
     */
    auto identifier();

    /**
     * The Number allows the generation of a token of
     * {integer, float, double}
     */
    auto number();

public:
    //
    Lexer(std::string const(&buff)) noexcept;
    ~Lexer();

    // Get current char to cursor position
    const char getCurrentChar() const;

    // Get next char to the next cursor position
    const char look() const;

    // Genered next token
    const Token getNextToken();

    // Get list of all token
    const auto tokenize();
};

#endif