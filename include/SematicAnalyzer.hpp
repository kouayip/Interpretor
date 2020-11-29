#ifndef __SEMATICANALYZER__
#define __SEMATICANALYZER__

#include "AST.hpp"
#include "Symbol.hpp"

/**
 * Static semantic checks
 * Semantic Analysis
 */
class SematicAnalyzer
{
private:
    SymbolTable symtab_;

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

    void visitNodeNum(Num *num);

    /**
     * Visit node Var
     */
    void visitNodeVar(Var *var);

    /**
     * Visit node UnaryOp
     */
    void visitNodeUnaryOp(UnaryOp *node);

    /**
     * Visit node BinOp
     */
    void visitNodeBinOp(BinOp *node);

    /**
     * Visit node Empty
     */
    void visitNodeEmpty(Empty *empty);

public:
    /**
     * Visit node
     */
    void visitNode(Node *node);

    /**
     * 
     */
    void printSymbolTable();
};

#endif