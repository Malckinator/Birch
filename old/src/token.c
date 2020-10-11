#include <stdlib.h>
#include <stdbool.h>
#include "../include/token.h"

TokenT* initToken(int type, char* value) {
    TokenT* token = calloc(1, sizeof(struct TokenS));

    token->type = type;
    token->value = value;

    return token;
}

bool match(TokenT* token, int type, char* value) {
    return token->type == type && token->value == value;
}
