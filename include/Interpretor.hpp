#ifndef __INTERPRETOR__
#define __INTERPRETOR__

#include "../include/AST.hpp"

class Interpretor
{
private:
    /**
     * Visit node Num
     */
    auto visitNodeNum(Num *num);

    /**
     * Visit node UnaryOp
     */
    double visitUnaryOp(UnaryOp *node);

    /**
     * Visit node BinOp
     */
    double visitNodeBinOp(BinOp *node);

    /**
     * After visit, close a node and free heaps
     */
    void close(Node *node);

    /**
     * Visit node
     */
    auto visitNode(Node *node);

public:
    ~Interpretor();

    /**
     * Interpret a Tree code AST
     */
    double interpret(Node *node); //?Test: interpret return double
};

#endif