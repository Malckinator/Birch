#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include "position.h"

typedef struct ErrorStruct {
    char* line;
    char* title;
    char* description;
    Position* startPosition;
    Position* endPosition;
} Error;

Error* initError(char* title, char* description, char* line, Position* startPosition, Position* endPosition);

void errorDisplay(Error* error);

#endif