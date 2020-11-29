#ifndef __INTERPRETOR__
#define __INTERPRETOR__

#include <map>
#include "AST.hpp"
#include "Utils.hpp"
#include "SematicAnalyzer.hpp"
#include "Tools.hpp"

class Interpretor
{
private:
    //? Test A Global scone
    std::map<std::string, double> GLOBAL_SCOPE_;

    /**
     * Visit node Program
     */
    void visitNodeProgram(Program *program);

    /**
     * Visit node Block
     */
    void visitNodeBlock(Block *block);

    /**
     * Visit node CompoundDecl
     */
    void visitNodeCompoundDecl(CompoundDecl *decl);

    /**
     * Visit node ConstDecl
     */
    void visitNodeConstDecl(ConstDecl *decl);

    /**
     * Visit node ValDecl
     */
    void visitNodeValDecl(ValDecl *decl);

    /**
     * Visit node Assign
     */
    void visitNodeAssign(Assign *assign);

    /**
     * Visit node MultAssign
     */
    void visitNodeMultAssign(MultAssign *assign);

    /**
     * Visit node VarType
     */
    auto visitNodeVarType(VarType *type);

    /**
     * Visit node Var
     */
    template <typename T>
    T visitNodeVar(Var *var);

    /**
     * Visit node Num
     */
    template <typename T>
    T visitNodeNum(Num *num);

    /**
     * Visit node UnaryOp
     */
    template <typename T>
    T visitNodeUnaryOp(UnaryOp *node);

    /**
     * Visit node BinOp
     */
    template <typename T>
    T visitNodeBinOp(BinOp *node);

    /**
     * Visit node Empty
     */
    void visitNodeEmpty(Empty *empty);

    /**
     * After visit, close a node and free heaps
     */
    void close(Node *node);

    /**
     * Visit node
     */
    template <typename T>
    T visitNode(Node *node);

    /**
     * Visit node
     */
    template <typename T>
    T visit(T node);

public:
    Interpretor();
    ~Interpretor();

    /**
     * Interpret a Tree code AST
     */
    void interpret(Node *node); //?Test: interpret return double
};

#endif