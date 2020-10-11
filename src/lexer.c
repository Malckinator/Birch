#include <stdio.h>
#include <string.h>
#include "../include/error.h"
#include "../include/utill.h"
#include "../include/lexer.h"

LexerResult* initLexerResult(Token* token, Error* error) {
    LexerResult* lexerResult = calloc(1, sizeof(struct LexerResultStruct));

    lexerResult->token = token;
    lexerResult->error = error;

    return lexerResult;
}

Lexer* initLexer(char* source) {
    Lexer* lexer = calloc(1, sizeof(struct LexerStruct));

    lexer->source = source;
    lexer->c = ' ';
    lexer->position = initPosition();

    lexerAdvance(lexer);

    return lexer;
}

void lexerAdvance(Lexer* lexer) {
    positionAdvance(lexer->position, lexer->c);

    lexer->c = lexer->source[lexer->position->index];
}

Token* addToken(Token* array, int* size, Token* token) {
    Token* new = calloc(*size + 1, sizeof(struct TokenStruct));

    for (int i = 0; i < *size; i++) {
        new[i] = array[i];
    }

    new[*size] = *token;
    *size += 1;
    return new;
}

Error* lexerMakeTokens(Lexer* lexer) {
    Token* tokens = calloc(0, sizeof(struct TokenStruct));
    int size = 0;

    while (lexer->c != '\0') {
        if (charInString(lexer->c, "0123456789.")) {
            LexerResult* result = lexerMakeNumber(lexer);
            
            if (result->error != NULL) {
                return result->error;
            }

            Token* token = result->token;

            tokens = addToken(tokens, &size, token);
            continue;
        } else if (lexer->c == '+') {
            Token* token = initToken(TT_PLUS, "+", positionCopy(lexer->position), positionCopy(lexer->position));
            
            tokens = addToken(tokens, &size, token);
        } else if (lexer->c == '-') {
            Token* token = initToken(TT_MIN, "-", positionCopy(lexer->position), positionCopy(lexer->position));

            tokens = addToken(tokens, &size, token);
        } else if (lexer->c == '*') {
            Token* token = initToken(TT_MUL, "*", positionCopy(lexer->position), positionCopy(lexer->position));

            tokens = addToken(tokens, &size, token);
        } else if (lexer->c == '/') {
            Token* token = initToken(TT_DIV, "/", positionCopy(lexer->position), positionCopy(lexer->position));

            tokens = addToken(tokens, &size, token);
        } else if (lexer->c != ' ' && lexer->c != '\t' && lexer->c != '\n') {
            char* format = calloc(25, sizeof(char));
            
            sprintf(format, "Unexpected character '%c'.", lexer->c);

            return initError("IllegalCharacterError", format, getLines(lexer->source)[lexer->position->line - 1], positionCopy(lexer->position), positionCopy(lexer->position));
        }
        
        lexerAdvance(lexer);
    }

    tokens = addToken(tokens, &size, initToken(TT_EOF, TT_EOF, positionCopy(lexer->position), positionCopy(lexer->position)));

    lexer->tokens = tokens;
    lexer->tokensSize = size;
    return NULL;
}

LexerResult* lexerMakeNumber(Lexer* lexer) {
    char* number = calloc(1, sizeof(char));
    number[0] = '\0';
    int numberSize = 1;
    Position* startPosition = positionCopy(lexer->position);
    bool dot = false;

    while (lexer->c != '\0') {
        if (charInString(lexer->c, "0123456789")) {
            number = realloc(number, (numberSize + 1) * sizeof(char));
            
            number = concat(number, charToString(lexer->c));

            numberSize++;
        } else if (lexer->c == '.') {
            if (dot) {
                Error* error = initError("NumberFormatError", "Too many decimal points.", getLines(lexer->source)[startPosition->line - 1], startPosition, positionCopy(lexer->position));

                return initLexerResult(NULL, error);
            } else {
                number = realloc(number, (numberSize + 1) * sizeof(char));
                
                number = concat(number, charToString(lexer->c));

                numberSize++;

                dot = true;
            }
        } else {
            break;
        }
        
        lexerAdvance(lexer);
    }
    
    if (dot) {
        Token* token = initToken(TT_FLOAT, number, startPosition, positionCopy(lexer->position));

        return initLexerResult(token, NULL);
    } else {
        Token* token = initToken(TT_INT, number, startPosition, positionCopy(lexer->position));
        
        return initLexerResult(token, NULL);
    }
}