#include <iostream>

#include "../include/Parser.hpp"
#include "../include/Interpretor.hpp"
#include "../include/Asset.hpp"
#include "../include/Type.hpp"

void freeTree(Node *node, bool isShared = false)
{
    if (node == nullptr || node == NULL)
        return;

    if (node->type() == NodeType::PROGRAM)
    {
        auto prg = static_cast<Program *>(node);
        freeTree(prg->block());
        delete prg;
        prg = nullptr;
    }
    else if (node->type() == NodeType::BLOCK)
    {
        auto blog = static_cast<Block *>(node);
        for (size_t i = 0; i < blog->size(); i++)
        {
            freeTree((*blog)[i]);
        }
        delete blog;
        blog = nullptr;
    }
    else if (node->type() == NodeType::COMPOUNDDECL)
    {
        auto cdl = static_cast<CompoundDecl *>(node);

        for (size_t i = 0; i < cdl->size(); i++)
        {
            freeTree((*cdl)[i], i == 0);
        }
        delete cdl;
        cdl = nullptr;
    }
    else if (node->type() == NodeType::VALDECL)
    {
        auto val = node->reveal<ValDecl *>();
        if (val->var())
            freeTree(val->var());

        if (isShared)
            freeTree(val->type());

        delete val;
        val = nullptr;
    }
    else if (node->type() == NodeType::CONSTDECL)
    {
        auto cst = node->reveal<ConstDecl *>();
        freeTree(cst->var());

        if (isShared)
            freeTree(cst->type());

        delete cst;
        cst = nullptr;
    }
    else if (node->type() == NodeType::VAR)
    {
        auto var = node->reveal<Var *>();
        delete var;
        var = nullptr;
    }
    else if (node->type() == NodeType::VARTYPE)
    {
        auto varType = static_cast<VarType *>(node);
        delete varType;
        varType = nullptr;
    }
    else if (node->type() == NodeType::ASSIGN)
    {
        auto asn = node->reveal<Assign *>();
        // freeTree(asn->left()); //! Check is very free
        freeTree(asn->right());
        delete asn;
        asn = nullptr;
    }
    else if (node->type() == NodeType::MULTASSIGN)
    {
        auto masn = node->reveal<MultAssign *>();
        //!Check is very free branch left assign var
        freeTree(masn->right());
        delete masn;
        masn = nullptr;
    }
    else if (node->type() == NodeType::BINOP)
    {
        auto op = node->reveal<BinOp *>();
        freeTree(op->left());
        freeTree(op->right());
        delete op;
        op = nullptr;
    }
    else if (node->type() == NodeType::UNARYOP)
    {
        auto unary = node->reveal<UnaryOp *>();
        freeTree(unary->expr());
        delete unary;
        unary = nullptr;
    }
    else if (node->type() == NodeType::NUM)
    {
        auto num = node->reveal<Num *>();
        delete num;
        num = nullptr;
    }
    else
    {
        Utils::print(node->print());
        return;
    }
}

Node *nodeTest()
{
    auto token = Token{TokenType::MINUS, '-', Location{}};
    return new Var{token};
}

Node *nodeBlock()
{
    auto block = new Block;
    block->append(nodeTest());
    return block;
}

//TODO: Geret la gestion de la memoire des tree AST
int main()
{
    try
    {
        //? 7 + (((3 + 2))) = 12
        //? 5 - - - + - (3 + 4) - +2 = 10
        auto source{"((\n"
                    "val<int>\n{\n"
                    "x <- 3,\n"
                    "y,z <- 10.8 + 9 / 7 + (((3 + 2))),\n"
                    "t <- 5 - - - + - (3 + 4) - +2"
                    "};\n"
                    "))\n"}; // 10

        // auto source{"((\n"
        //             "val<int>\n{\n"
        //             "x, s<- 12 + 2 * 5 - - - + - (3 + 4)"
        //             "};"
        //             "))\n"}; // 10

        //? Test Lexer
        // Lexer lex{source};
        // while (true)
        // {
        //     auto token = lex.getNextToken();

        //     token.print();
        //     if (token.type() == TokenType::_EOF_)
        //         break;
        // }

        // return 0; //! test

        Parser parse{source};

        auto ast{parse.parse()};

        auto inter = Interpretor{};

        ast->printNode();
        freeTree(ast);

        // inter.interpret(ast);

        // remove(ast);
        // inter.clearRes();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // auto elem = (*block)[0];

    return 0;
}