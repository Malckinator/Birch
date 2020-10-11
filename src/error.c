#include <stdio.h>
#include <stdlib.h>
#include "../include/error.h"

Error* initError(char* title, char* description, char* line, Position* startPosition, Position* endPosition) {
    Error* error = calloc(1, sizeof(struct ErrorStruct));
    
    error->title = title;
    error->description = description;
    error->line = line;
    error->startPosition = startPosition;
    error->endPosition = endPosition;
    
    return error;
}

void errorDisplay(Error* error) {
    printf("%s: %s\n", error->title, error->description);
    printf("%s\n", error->line);

    for (int i = 0; i <= error->endPosition->index; i++) {
        if (error->startPosition->index <= i) {
            printf("^");
        } else {
            printf(" ");
        }
    }

    printf("\n");
}
