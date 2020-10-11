#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "error.h"

typedef struct LexerStruct {
    Token* tokens;
    int tokensSize;
    Position* position;
    char* source;
    char c;
} Lexer;

typedef struct LexerResultStruct {
    Token* token;
    Error* error;
} LexerResult;

LexerResult* initLexerResult(Token* token, Error* error);

Lexer* initLexer(char* source);

void lexerAdvance(Lexer* lexer);

Token* addToken(Token* array, int* size, Token* token);

Error* lexerMakeTokens(Lexer* lexer);

LexerResult* lexerMakeNumber(Lexer* lexer);

#endif

/*
void push(int *arr, int index, int value, int *size, int *capacity){
    if(*size > *capacity){
        realloc(arr, sizeof(arr) * 2);
        *capacity = sizeof(arr) * 2;
    }
    arr[index] = value;
    *size = *size + 1;
}
*/