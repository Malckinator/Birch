#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../include/lexer.h"

LexerT* initLexer(char* source) {
    LexerT* lexer = calloc(1, sizeof(struct LexerS));

    lexer->source = source;
    lexer->i = -1;
    lexer->c = ' ';

    lexerAdvance(lexer);

    return lexer;
}

void lexerAdvance(LexerT* lexer) {
    lexer->i++;

    if (lexer->i < strlen(lexer->source)) {
        lexer->c = lexer->source[lexer->i];
    } else {
        lexer->c = '\0';
    }
}

void lexerSkip(LexerT* lexer) {
    while (lexer->c == ' ' || lexer->c == '\t' || lexer->c == '\n')
    {
       lexerAdvance(lexer);
    }
}

TokenT* lexerNextToken(LexerT* lexer) {
    while (lexer->c != '\0' && lexer->i < strlen(lexer->source)) {
        lexerSkip(lexer);

        if (isalnum(lexer->c)) {
            return lexerCollectId(lexer);
        }

        if (lexer->c == '"') {
            return lexerCollectString(lexer);
        }

        TokenT* token;

        switch (lexer->c) {
            case '=':
                token = initToken(TT_Equals, lexerCharToString(lexer));
                lexerAdvance(lexer);
                break;
            case ';':
                token = initToken(TT_Semi, lexerCharToString(lexer));
                lexerAdvance(lexer);
                break;
            case '(':
                token = initToken(TT_LParen, lexerCharToString(lexer));
                lexerAdvance(lexer);
                break;
            case ')':
                token = initToken(TT_RParen, lexerCharToString(lexer));
                lexerAdvance(lexer);
                break;
        }

        return token;
    }

    return (void*)0;
}

TokenT* lexerAdvanceToken(LexerT* lexer, TokenT* token) {
    lexerAdvance(lexer);

    return token;
}

TokenT* lexerCollectString(LexerT* lexer) { // Todo add errors, add support for '
    lexerAdvance(lexer);
    bool backslash = false;
    bool finished = false; //////////////////////////////////////////////////////////////////////////////
    char* value = calloc(1, sizeof(char));

    value[0] = '\0';

    while (lexer->c != '\0') {
        if (lexer->c == '\\' && !backslash) {
            backslash = true;
            continue;
        } else if (backslash) {
            if (backslash) {
                if (lexer->c == 'n') {
                    lexer->c = '\n';
                } else if (lexer->c == 't') {
                    lexer->c = '\t';
                } //////////////////////////////////////////////////////////////////////////////////////
            }
        } else if (lexer->c == '"') {
            finished = true;

            lexerAdvance(lexer);

            break;
        }

        char* s = lexerCharToString(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexerAdvance(lexer);
    }

    return initToken(TT_String, value);
}

TokenT* lexerCollectId(LexerT* lexer) {
    char* value = calloc(1, sizeof(char));

    value[0] = '\0';

    while (isalnum(lexer->c)) {
        char* s = lexerCharToString(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexerAdvance(lexer);
    }

    return initToken(TT_Id, value);
}

char* lexerCharToString(LexerT* lexer) {
    char* str = calloc(2, sizeof(char));

    str[0] = lexer->c;
    str[1] = '\0';

    return str;
}