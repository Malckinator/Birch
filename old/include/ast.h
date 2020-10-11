#ifndef AST_H
#define AST_H

typedef struct AST_S
{
    enum {
        ASTVariableDef,
        ASTVariable,
        ASTFunctionCall,
        ASTString
    } type;
} AST_T;


#endif