#include <stdlib.h>
#include "../include/position.h"

Position* initPosition() {
    Position* position = calloc(1, sizeof(struct PositionStruct));

    position->index = -1;
    position->line = 1;
    position->column = -1;

    return position;
}

void positionAdvance(Position* position, char c) {
    if (c == '\n') {
        position->line++;
        position->column = -1;
    }

    position->index++;
    position->column++;
}

Position* positionCopy(Position* position) {
    Position* copy = calloc(1, sizeof(struct PositionStruct));

    copy->index = position->index;
    copy->line = position->line;
    copy->column = position->column;

    return copy;
}
