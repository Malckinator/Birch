#ifndef UTILL_H
#define UTILL_H

#include <stdbool.h>

char* concat(const char* s1, const char* s2);

char* charToString(char c);

bool charInString(char c, char* s);

char** getLines(char* text);

#endif