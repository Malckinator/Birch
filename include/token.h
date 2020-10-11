#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdbool.h>
#include "position.h"

char* TT_EOF;
char* TT_INT;
char* TT_FLOAT;
char* TT_PLUS;
char* TT_MIN;
char* TT_MUL;
char* TT_DIV;

typedef struct TokenStruct {
    char* type;
    char* value;
    Position* startPosition;
    Position* endPosition;
} Token;

Token* initToken(char* type, char* value, Position* startPosition, Position* endPosition);

bool tokenMatch(Token* token, char* type, char* value);

#endif