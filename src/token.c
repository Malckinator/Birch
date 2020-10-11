#include <stdlib.h>
#include <stdbool.h>
#include "../include/token.h"
#include "../include/position.h"

char* TT_EOF = "TT_EOF";
char* TT_INT = "TT_INT";
char* TT_FLOAT = "TT_FLOAT";
char* TT_PLUS = "TT_PLUS";
char* TT_MIN = "TT_MIN";
char* TT_MUL = "TT_MUL";
char* TT_DIV = "TT_DIV";

Token* initToken(char* type, char* value, Position* startPosition, Position* endPosition) {
    Token* token = (Token*) calloc(1, sizeof(struct TokenStruct));

    token->type = type;
    token->value = value;
    token->startPosition = startPosition;
    token->endPosition = endPosition;

    return token;
}

bool tokenMatch(Token* token, char* type, char* value) {
    return token->type == type && token->value == value;
}