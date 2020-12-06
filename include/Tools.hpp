#if !defined(__TOOLS__)
#define __TOOLS__

#include <fstream>
#include "AST.hpp"
#include "Utils.hpp"

struct Tools
{
    /**
     * Use to clean all node to the tree
     */
    static void freeTree(Node *node, bool isShared_ = false)
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
            auto block = static_cast<Block *>(node);
            for (size_t i = 0; i < block->size(); i++)
            {
                freeTree((*block)[i], true);
            }
            delete block;
            block = nullptr;
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

            if (isShared_)
                freeTree(val->type());

            delete val;
            val = nullptr;
        }
        else if (node->type() == NodeType::CONSTDECL)
        {
            auto cst = node->reveal<ConstDecl *>();
            freeTree(cst->var());

            if (isShared_)
                freeTree(cst->type());

            delete cst;
            cst = nullptr;
        }
        else if (node->type() == NodeType::FUNCDECL)
        {
            auto func = node->reveal<FuncDecl *>();
            freeTree(func->type());
            freeTree(func->params());
            freeTree(func->block());
            delete func;
            func = nullptr;
        }
        else if (node->type() == NodeType::FUNCPARAMS)
        {
            auto params = node->reveal<FuncParams *>();
            for (size_t i = 0; i < params->size(); i++)
            {
                freeTree((*params)[i], true);
            }
            delete params;
            params = nullptr;
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
            if (isShared_)
                freeTree(asn->left()); //! Check is very freeTree
            freeTree(asn->right());
            delete asn;
            asn = nullptr;
        }
        else if (node->type() == NodeType::MULTASSIGN)
        {
            auto masn = node->reveal<MultAssign *>();
            //!Check is very freeTree branch left assign var
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
        else if (node->type() == NodeType::EMPTY)
        {
            auto empty = node->reveal<Empty *>();
            delete empty;
            empty = nullptr;
        }
        else
        {
            Utils::print(node->print());
            return;
        }
    };

    /**
     * Read content file source;
     */
    static const std::string readFile(char *path)
    {
        std::ifstream infile(path);
        std::string line;
        std::string lines;
        while (std::getline(infile, line))
        {
            lines += line + "\n";
        }

        return lines;
    }
};

#endif