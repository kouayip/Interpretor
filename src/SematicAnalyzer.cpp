#include "../include/SematicAnalyzer.hpp"

void SematicAnalyzer::printSymbolTable()
{
    symtab_.print();
}

void SematicAnalyzer::visitNode(Node *node)
{
    // std::cout << std::string("Visit --> " + node->print()) << '\n';

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
    case NodeType::VAR:
        return visitNodeVar(node->reveal<Var *>());
        break;
    case NodeType::NUM:
        return visitNodeNum(node->reveal<Num *>());
        break;
    case NodeType::UNARYOP:
        return visitNodeUnaryOp(node->reveal<UnaryOp *>());
        break;
    case NodeType::BINOP:
        return visitNodeBinOp(node->reveal<BinOp *>());
        break;
    default:
        throw std::runtime_error("Analyzer: Unknown node");
        break;
    }
}

void SematicAnalyzer::visitNodeProgram(Program *program)
{
    visitNode(program->block());
}

void SematicAnalyzer::visitNodeBlock(Block *block)
{
    for (size_t i = 0; i < block->size(); i++)
    {
        visitNode((*block)[i]);
    }
}

void SematicAnalyzer::visitNodeEmpty(Empty *empty) {}

void SematicAnalyzer::visitNodeCompoundDecl(CompoundDecl *decl)
{
    for (size_t i = 0; i < decl->size(); i++)
    {
        visitNode((*decl)[i]);
    }
}

void SematicAnalyzer::visitNodeConstDecl(ConstDecl *decl) //TODO: Analyse a declaration const
{
}

void SematicAnalyzer::visitNodeValDecl(ValDecl *decl)
{
    auto type = decl->type()
                    ->reveal<VarType *>()
                    ->type();

    if (!symtab_.hasKey(type))
        throw std::runtime_error(std::string("Error: Symbol type '" + type + "' is not defined"));

    auto symbolType = symtab_.lookup(type);
    auto varName = decl->var()
                       ->reveal<Var *>()
                       ->name();

    if (symtab_.hasKey(varName)) //* Check is var exist
        throw std::runtime_error(std::string("Error: Duplicate Symbol '" + varName + "'"));

    auto varSymbole = new ValSymbol(varName, symbolType);
    symtab_.insert(varSymbole);
}

void SematicAnalyzer::visitNodeAssign(Assign *assign)
{
    visitNode(assign->right());
    visitNode(assign->left());
}

void SematicAnalyzer::visitNodeMultAssign(MultAssign *assign) //TODO: Analyse mul assaign
{
}

void SematicAnalyzer::visitNodeVar(Var *var)
{
    const auto varName = var->name();
    auto varSymbole = symtab_.lookup(varName);

    if (!varSymbole)
        throw std::runtime_error(std::string("Error: Symbol '" + varName + "' has not been declared"));
}

void SematicAnalyzer::visitNodeNum(Num *num) {}

void SematicAnalyzer::visitNodeUnaryOp(UnaryOp *node)
{
    visitNode(node->expr());
}

void SematicAnalyzer::visitNodeBinOp(BinOp *node)
{
    visitNode(node->left());
    visitNode(node->right());
}