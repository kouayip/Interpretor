#include "../include/Interpretor.hpp"

Interpretor::Interpretor()
{
}

void Interpretor::close(Node *node)
{
    delete node;
    node = nullptr;
}

template <typename T>
T Interpretor::visitNode(Node *node)
{
    Utils::print(std::string("Visit --> " + node->print()));

    //? Void retrun type
    if constexpr (std::is_same<T, void>::value)
    {
        switch (node->type())
        {
        case NodeType::PROGRAM:
            visitNodeProgram(node->reveal<Program *>());
            break;
        case NodeType::BLOCK:
            visitNodeBlock(node->reveal<Block *>());
            break;
        case NodeType::COMPOUNDDECL:
            visitNodeCompoundDecl(node->reveal<CompoundDecl *>());
            break;

        case NodeType::VALDECL:
            visitNodeValDecl(node->reveal<ValDecl *>());
            break;
        case NodeType::ASSIGN:
            visitNodeAssign(node->reveal<Assign *>());
            break;
        case NodeType::EMPTY:
            visitNodeEmpty(node->reveal<Empty *>());
            break;
        default:
            throw std::runtime_error("Unknown node");
            break;
        }

        return;
    }
    else if constexpr (std::is_same<T, int>::value || std::is_same<T, double>::value)
    {
        switch (node->type())
        {
        case NodeType::VAR:
            return visitNodeVar<T>(node->reveal<Var *>());
            break;
        case NodeType::NUM:
            return visitNodeNum<T>(node->reveal<Num *>());
            break;
        case NodeType::UNARYOP:
            return visitNodeUnaryOp<T>(node->reveal<UnaryOp *>());
            break;
        case NodeType::BINOP:
            return visitNodeBinOp<T>(node->reveal<BinOp *>());
            break;
        default:
            throw std::runtime_error("Unknown node");
            break;
        }
    }
    else
    {
        std::cout << "Type not recognized" << std::endl;
    }
    throw std::runtime_error("Error type node");
}

void Interpretor::visitNodeProgram(Program *program)
{
    visitNode<void>(program->block());
}

void Interpretor::visitNodeBlock(Block *block)
{
    for (size_t i = 0; i < block->size(); i++)
    {
        visitNode<void>((*block)[i]);
    }
}

void Interpretor::visitNodeEmpty(Empty *empty)
{
}

void Interpretor::visitNodeCompoundDecl(CompoundDecl *decl)
{
    for (size_t i = 0; i < decl->size(); i++)
    {
        visitNode<void>((*decl)[i]);
    }
}

// auto Interpretor::visitNodeConstDecl(ConstDecl *decl)
// {
// }

void Interpretor::visitNodeValDecl(ValDecl *decl)
{
}

void Interpretor::visitNodeAssign(Assign *assign)
{
}

// auto Interpretor::visitNodeMultAssign(MultAssign *assign)
// {
// }

auto Interpretor::visitNodeVarType(VarType *type)
{
    return type->type();
}

template <class T>
T Interpretor::visitNodeVar(Var *var)
{
}

template <class T>
T Interpretor::visitNodeNum(Num *num)
{
    return num->value();
}

template <class T>
T Interpretor::visitNodeUnaryOp(UnaryOp *node) //! Convert num to real type
{
    if (node->op().type() == TokenType::PLUS)
        return +visitNode<T>(node->expr());
    else
        return -visitNode<T>(node->expr());
}

template <class T>
T Interpretor::visitNodeBinOp(BinOp *node) //! convert to Return real type
{
    switch (node->op().type())
    {
    case TokenType::PLUS:
        return visitNode<T>(node->left()) + visitNode<T>(node->right());
        break;

    case TokenType::MINUS:
        return visitNode<T>(node->left()) - visitNode<T>(node->right());
        break;

    case TokenType::MULT:
        return visitNode<T>(node->left()) * visitNode<T>(node->right());
        break;

    case TokenType::DIV:
        return visitNode<T>(node->left()) / visitNode<T>(node->right());
        break;

    case TokenType::MOD:
        return (T)((int)visitNode<T>(node->left()) % (int)visitNode<T>(node->right()));
        break;

    default:
        throw "Error Bin Op";
        break;
    }
}

void Interpretor::interpret(Node *node)
{
    try
    {
        auto analyzer = SematicAnalyzer();
        analyzer.visitNode(node);
        analyzer.printSymbolTable();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // visitNode<void>(node);

    // std::cout << '{' << std::endl;
    // for (auto itr = GLOBAL_SCOPE_.begin(); itr != GLOBAL_SCOPE_.end(); ++itr) //! Test get all var declare to scope
    // {
    //     std::cout << itr->first << ": " << itr->second << ',' << '\n';
    // }
    // std::cout << '}' << std::endl;
}

Interpretor::~Interpretor()
{
}