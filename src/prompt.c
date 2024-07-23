#include "prompt.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void start_prompt(void) {
    char command[256];
    while (1) {
        printf("makenx%c ", '%');
        scanf("%s", command);
        if (strncmp(command, "exit", 4) == 0) {
            exit(EXIT_SUCCESS);
        }
    }
}
