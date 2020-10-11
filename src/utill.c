#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/utill.h"

char* concat(const char* s1, const char* s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    
    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

char* charToString(char c) {
    char* string = calloc(2, sizeof(char));

    string[0] = c;
    string[1] = '\0';

    return string;
}

bool charInString(char c, char* s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (c == s[i]) {
            return true;
        }
    }

    return false;
}

char** getLines(char* text) {
    char** lines = calloc(0, sizeof(char*));
    int size = 0;

    char* last = strtok(text, "\n");

	while(last != NULL) {
        realloc(lines, (size + 1) * sizeof(char*));
        lines[size] = last;
        size++;
        
		last = strtok(NULL, "\n");
	}

    return lines;
}
