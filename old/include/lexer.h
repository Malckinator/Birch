#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct LexerS {
    char* source;
    char c;
    unsigned int i;
} LexerT;

LexerT* initLexer(char* source);

void lexerAdvance(LexerT* lexer);

void lexerSkip(LexerT* lexer);

TokenT* lexerNextToken(LexerT* lexer);

TokenT* lexerCollectString(LexerT* lexer);

TokenT* lexerCollectId(LexerT* lexer);

char* lexerCharToString(LexerT* lexer);

#endif