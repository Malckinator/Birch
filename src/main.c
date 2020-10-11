#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"
#include "../include/error.h"

int main() {
    char* source = "100 + 10;";
    Lexer* lexer = initLexer(source);
    Error* error = lexerMakeTokens(lexer);
    
    if (error != NULL) {
        errorDisplay(error);

        return 0;
    }

    for (int i = 0; i < lexer->tokensSize; i++) {
        Token* token = &lexer->tokens[i];
        printf("Token('%s', '%s')\n", token->type, token->value);
    }

    return 0;
}