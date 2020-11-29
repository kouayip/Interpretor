#include "../include/Parser.hpp"

Parser::Parser(std::string const(&buff)) throw() : lexer_{buff}
{
    currentToken_ = lexer_.getNextToken();
}

auto Parser::error(std::string msg = "Type error")
{
    // return std::string("Type error"); //TODO: Refactor code to create a generic class Error
    return std::runtime_error(msg);
}

void Parser::consume(TokenType const(&type))
{
    // Utils::print(currentToken_); //! Test

    if (currentToken_.type() == type)
    {
        currentToken_ = lexer_.getNextToken();
    }
    else
    {
        Utils::print(std::string("Actual: "));
        Utils::print(currentToken_.type());
        Utils::print(std::string("Expected: "));
        Utils::print(type);
        throw error();
    }
}

Node *Parser::program()
{
    //? Consume a declaration start program
    consume(TokenType::LPAREN);
    consume(TokenType::LPAREN);

    auto root = new Program{"Test", block()};

    //? Consume a declaration end program
    consume(TokenType::RPAREN);
    consume(TokenType::RPAREN);

    //! Program content a block intructions
    return root;
}

Node *Parser::block()
{
    auto const block = new Block;

    try
    {
        while (currentToken_.type() != LPAREN)
        {
            //? Complete list of block {If statment ...}
            if (currentToken_.type() == TokenType::VAL ||
                currentToken_.type() == TokenType::CONST)
            {
                auto decl = declarations();
                block->append(decl);
            }
            else if (currentToken_.type() == TokenType::FUNC)
            {
                auto funcDecl = declarations();
                block->append(funcDecl);
            }
            else if (currentToken_.type() == TokenType::ID)
            {
                auto assign = assignStatement();
                consume(TokenType::SEMI);
                block->append(assign);
            }
            else
            {
                block->append(new Empty());
                break;
            }
        }
    }
    catch (const std::exception &e)
    {
        Tools::freeTree(block);
        std::cerr << e.what() << '\n';
    }

    return block;
}

Node *Parser::declarations()
{
    if (currentToken_.type() == TokenType::VAL)
    {
        consume(TokenType::VAL);
        consume(TokenType::LTHAN);
        auto type = typeSpec();
        consume(TokenType::GTHAN);
        auto decs = varDeclaration<ValDecl>(type);
        consume(TokenType::SEMI);
        return decs;
    }
    else if (currentToken_.type() == TokenType::CONST)
    {
        consume(TokenType::CONST);
        consume(TokenType::LTHAN);
        auto type = typeSpec();
        consume(TokenType::GTHAN);
        auto decs = varDeclaration<ConstDecl>(type);
        consume(TokenType::SEMI);
        return decs;
    }
    else if (currentToken_.type() == TokenType::FUNC)
    {
        consume(TokenType::FUNC);
        auto func = funcDeclaration();
        consume(TokenType::SEMI);
        return func;
    }

    throw error();
}

template <typename T>
Node *Parser::varDeclaration(Node *(&type))
{
    if (currentToken_.type() == TokenType::LCURLY)
    {
        consume(TokenType::LCURLY);
        if (currentToken_.type() == TokenType::ID)
        {
            auto nodes = varDeclaration<T>(type);

            consume(TokenType::RCURLY);
            return nodes;
        }
        else if (currentToken_.type() == TokenType::RCURLY)
        {
            consume(TokenType::RCURLY);
            delete type; //? Free resource type to declaration is empty
            type = nullptr;
            return new Empty{};
        }
        throw error();
    }

    auto const nodes = new CompoundDecl{};
    auto prevVarPosLine = -1; //? Save last position line the prev var
    auto index = -1;          //? index frist multy declaration
    auto isMulDecl = false;   //? Check is si Multy declaration or unique declaration
    auto isAssign = false;
    while (currentToken_.type() == TokenType::ID)
    {
        auto pos = currentToken_.location().line;

        if (pos == prevVarPosLine && !isAssign)
        {
            isMulDecl = true;
        }
        else if (isMulDecl)
        {
            isMulDecl = false;
            index = nodes->size();
        }
        else if (isAssign)
        {
            index = nodes->size();
        }
        else
        {
            index++;
        }

        auto var = variable();

        nodes->append(new T{var, type});

        if (isAssign = (currentToken_.type() == TokenType::LASSIGN))
        {
            if (isMulDecl)
            {
                const auto op = currentToken_;
                consume(TokenType::LASSIGN);
                auto mAssign = new MultAssign{op, expr()};
                auto size = nodes->size() - 1;
                for (size_t i = index; i < size; i++)
                {
                    //! Utils::print(i);
                    mAssign->append((*nodes)[i]->reveal<ValDecl *>()->var());
                }

                mAssign->append(var); //? a last var multy line

                nodes->append(mAssign);
            }
            else
            {
                nodes->append(assignStatement(var));
            }
        }

        prevVarPosLine = pos; //? Update last position

        if (currentToken_.type() == TokenType::SEMI ||
            currentToken_.type() == TokenType::RCURLY)
            break;

        consume(TokenType::COMMA);
    }
    return nodes;
}

Node *Parser::constDeclaration() //TODO: Refact code to Generic Declaration
{
    return nullptr; //! Test
}

Node *Parser::funcDeclaration()
{
    consume(TokenType::LTHAN);
    auto returnType = typeSpec();
    consume(TokenType::GTHAN);

    auto funcName = currentToken_.value();
    consume(TokenType::ID);

    auto params = funcParameters();

    consume(TokenType::LCURLY);
    auto block = this->block(); //? Block declaration into function
    consume(TokenType::RCURLY);

    return new FuncDecl(funcName, returnType, params, block);
}

Node *Parser::funcParameters()
{
    consume(TokenType::LPAREN);

    if (currentToken_.type() == TokenType::RPAREN)
    {
        consume(TokenType::RPAREN);
        return new Empty();
    }

    auto params = new FuncParams();

    auto getParams = [&]() { //? Lamda expresion to get a val params declaration
        auto type = typeSpec();
        consume(TokenType::COLON);
        auto var = variable();
        params->append(new ValDecl{var, type});
    };

    getParams(); //? Get a first params

    while (currentToken_.type() != TokenType::RPAREN && currentToken_.type() == TokenType::COMMA)
    {
        consume(TokenType::COMMA);
        getParams();
    }

    consume(TokenType::RPAREN);
    return params;
}

Node *Parser::assignStatement()
{
    auto var = variable();
    return assignStatement(var);
}

Node *Parser::assignStatement(Node *&var)
{
    const auto op = currentToken_;
    consume(TokenType::LASSIGN);
    return new Assign{var, op, expr()};
}

Node *Parser::variable()
{
    auto token{currentToken_};
    consume(TokenType::ID);
    return new Var(token);
}

Node *Parser::typeSpec()
{
    // consume(TokenType::LTHAN);

    const auto token = currentToken_;

    if (currentToken_.type() == TokenType::INTEGER)
        consume(TokenType::INTEGER);
    else if (currentToken_.type() == TokenType::REAL)
        consume(TokenType::REAL);
    else if (currentToken_.type() == TokenType::STRING)
        consume(TokenType::STRING);
    else if (currentToken_.type() == TokenType::BOOL)
        consume(TokenType::BOOL);
    else if (currentToken_.type() == TokenType::AUTO)
        consume(TokenType::AUTO);
    else
        throw error();

    // consume(TokenType::GTHAN);

    return new VarType(token);
}

Node *Parser::factor()
{
    if (currentToken_.type() == TokenType::INUM ||
        currentToken_.type() == TokenType::FNUM)
    {
        const auto token{currentToken_};
        if (currentToken_.type() == TokenType::INUM)
            consume(TokenType::INUM);
        else
            consume(TokenType::FNUM);

        return new Num(token);
    }
    else if (currentToken_.type() == TokenType::PLUS ||
             currentToken_.type() == TokenType::MINUS)
    {
        const auto token{currentToken_};
        if (currentToken_.type() == TokenType::PLUS)
            consume(TokenType::PLUS);
        else
            consume(TokenType::MINUS);
        return new UnaryOp{token, expr()};
    }
    else if (currentToken_.type() == TokenType::LPAREN)
    {
        consume(TokenType::LPAREN);
        const auto node{expr()};
        consume(TokenType::RPAREN);
        return node;
    }
    else
    {
        return variable();
    }
}

Node *Parser::term()
{
    auto node{factor()};

    while (currentToken_.type() == TokenType::MULT ||
           currentToken_.type() == TokenType::DIV ||
           currentToken_.type() == TokenType::MOD)
    {
        auto token = currentToken_;
        if (currentToken_.type() == TokenType::MULT)
            consume(TokenType::MULT);
        else if (currentToken_.type() == TokenType::DIV)
            consume(TokenType::DIV);
        else if (currentToken_.type() == TokenType::MOD)
            consume(TokenType::MOD);
        node = new BinOp(node, token, factor());
    }
    return node;
}

Node *Parser::expr()
{
    auto node{term()};

    while (currentToken_.type() == TokenType::PLUS ||
           currentToken_.type() == TokenType::MINUS)
    {
        auto token = currentToken_;
        if (currentToken_.type() == TokenType::PLUS)
            consume(TokenType::PLUS);
        else if (currentToken_.type() == TokenType::MINUS)
            consume(TokenType::MINUS);

        node = new BinOp(node, token, term());
    }

    return node;
}

Node *Parser::parse()
{
    auto tree{program()};
    if (currentToken_.type() != TokenType::_EOF_)
        throw error();
    return tree;
}

Parser::~Parser()
{
}