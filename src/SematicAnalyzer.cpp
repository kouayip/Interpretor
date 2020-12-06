#include "../include/SematicAnalyzer.hpp"

SematicAnalyzer::SematicAnalyzer()
{
}

void SematicAnalyzer::printSymbolTable()
{
    // currentCope_.print();
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
    case NodeType::FUNCDECL:
        return visitNodeFuncDecl(node->reveal<FuncDecl *>());
        break;
    case NodeType::FUNCPARAMS:
        return visitNodeFuncParams(node->reveal<FuncParams *>());
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
    Utils::print(std::string("ENTER scope: global"));
    auto globalScope = new ScopedSymbolTable("global", 1);
    this->currentCope_ = globalScope;

    visitNode(program->block());

    globalScope->print();

    this->currentCope_ = this->currentCope_->enclosingScope_;

    Utils::print(std::string("LEAVE scope: global"));

    delete globalScope;
    globalScope = nullptr;
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

    auto symbolType = currentCope_->lookup(type);

    if (symbolType)
        throw std::runtime_error(std::string("Error: Symbol type '" + type + "' is not defined"));

    auto varName = decl->var()
                       ->reveal<Var *>()
                       ->name();

    if (currentCope_->hasKey(varName)) //* Check is var exist
        throw std::runtime_error(std::string("Error: Duplicate Symbol '" + varName + "'"));

    auto varSymbole = new ValSymbol(varName, symbolType);
    currentCope_->insert(varSymbole);
}

void SematicAnalyzer::visitNodeFuncDecl(FuncDecl *decl)
{
    auto funName = decl->name();
    auto funType = decl->type()
                       ->reveal<VarType *>()
                       ->type();

    auto funSymbol = new FuncSymbol(funName, currentCope_->lookup(funType));
    currentCope_->insert(funSymbol);

    Utils::print("ENTER scope: " + funName);
    auto funScope = new ScopedSymbolTable(
        funName,
        this->currentCope_->getLevel() + 1,
        this->currentCope_);

    currentCope_ = funScope;

    auto params = decl->params()->reveal<FuncParams *>();
    for (size_t i = 0; i < params->size(); i++)
    {
        auto valDecl = (*params)[i]->reveal<ValDecl *>();
        auto type = valDecl->type()
                        ->reveal<VarType *>()
                        ->type();
        auto paramType = currentCope_->lookup(type);

        auto paramName = valDecl->var()
                             ->reveal<Var *>()
                             ->name();

        auto varSymbole = new ValSymbol(paramName, paramType);
        currentCope_->insert(varSymbole);
        funSymbol->append(varSymbole);
    }

    visitNode(decl->block());

    funScope->print();

    this->currentCope_ = currentCope_->enclosingScope_;

    Utils::print(std::string("LEAVE scope: " + funName));
    delete funScope;
    funScope = nullptr;
}

void SematicAnalyzer::visitNodeFuncParams(FuncParams *params)
{
    for (size_t i = 0; i < params->size(); i++)
    {
        visitNode((*params)[i]);
    }
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
    auto varSymbole = currentCope_->lookup(varName);

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

SematicAnalyzer::~SematicAnalyzer()
{
    if (currentCope_ != nullptr)
    {
        delete currentCope_;
        currentCope_ = nullptr;
    }
}