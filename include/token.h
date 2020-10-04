#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>

typedef struct TokenS
{
    enum {
        TT_Id,
        TT_Equals,
        TT_String,
        TT_Semi,
        TT_LParen,
        TT_RParen
    } type;

    char* value;
} TokenT;

TokenT* initToken(int type, char* value);

bool match(TokenT* token, int type, char* value);

#endif