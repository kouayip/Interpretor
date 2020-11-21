#include "../include/Parser.hpp"

Parser::Parser(std::string const(&buff)) throw() : lexer_{buff} {}

Parser::~Parser()
{
}