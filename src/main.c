#include <stdio.h>
#include "../include/lexer.h"

int main(int argc, char* argv) {
    LexerT* lexer = initLexer("var name=\"mal\";print(name);");
    
    TokenT* token = (void*)0;

    while ((token = lexerNextToken(lexer)) != (void*)0) {
        printf("Token(Type='%d', Value='%s')\n", token->type, token->value);
    }

    return 0;
}