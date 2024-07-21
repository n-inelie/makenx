#include "makenx.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline size_t handleAlpha(TokenStack *t_stack, char *str, size_t str_len,
                                 size_t index) {
    size_t j = index;
    while (j < str_len && isalpha(str[j])) {
        j++;
    }
    char *substring = malloc(sizeof(char) * (j - index + 1));
    strncpy(substring, str + index, j - index);
    substring[j - 1 + 1] = '\0';
    appendToken(t_stack, (Token){STRING, substring});
    return j;
}

static inline size_t handleNumeric(TokenStack *t_stack, char *str,
                                   size_t str_len, size_t index) {
    size_t j = index;
    while (j < str_len && isdigit(str[j])) {
        j++;
    }
    char *substring = malloc(sizeof(char) * (j - index + 1));
    strncpy(substring, str + index, j - index);
    appendToken(t_stack, (Token){NUMERIC, substring});
    return j;
}

void tokenize(Stats *stats, TokenStack *t_stack, char *str) {
    size_t str_len = strlen(str);
    size_t i = 0;
    char c;
    while (i < str_len) {
        c = str[i];

        if (isalpha(c)) {
            i = handleAlpha(t_stack, str, str_len, i);
            continue;
        }

        if (isdigit(c)) {
            i = handleNumeric(t_stack, str, str_len, i);
            continue;
        }

        switch (c) {
        case '(':
            appendToken(t_stack, (Token){L_PAREN, "("});
            stats->l_paren_count++;
            break;
        case ')':
            appendToken(t_stack, (Token){R_PAREN, ")"});
            stats->r_paren_count++;
            break;
        case ',':
            appendToken(t_stack, (Token){COMMA, ","});
            stats->comma_count++;
            break;
        case '.':
            appendToken(t_stack, (Token){PERIOD, "."});
            stats->period_count++;
            break;
        case '+':
            appendToken(t_stack, (Token){OPERATOR, "+"});
            break;
        case '-':
            appendToken(t_stack, (Token){OPERATOR, "-"});
            break;
        case '*':
            appendToken(t_stack, (Token){OPERATOR, "*"});
            break;
        case '/':
            appendToken(t_stack, (Token){OPERATOR, "/"});
            break;
        case '^':
            appendToken(t_stack, (Token){OPERATOR, "^"});
            break;
        case ' ':
            i++;
            continue;
            break;
        default:
            fprintf(stderr,
                    "Error: Invalid character entered ('%c' at position %zu)\n",
                    c, i);
            exit(EXIT_FAILURE);
            break;
        }
        i++;
    }
}
