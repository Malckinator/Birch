#ifndef POSITION_H
#define POSITION_H

typedef struct PositionStruct {
    int index;
    int line;
    int column;
} Position;

Position* initPosition();

void positionAdvance(Position* position, char c);

Position* positionCopy(Position* position);

#endif