#include "makenx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void filter_token_stack(TokenStack *t_stack) {
    Token t;
    Token t_new;
    Token temp;
    for (size_t i = 1; i < t_stack->size; ++i) {
        t = t_stack->tokens[i];
        if (t.type == OPERATOR) {
            temp = t_stack->tokens[i - 1];
            switch (t.text[0]) {
            case '+':
                t_new = (Token){STRING, "add"};
                break;
            case '-':
                t_new = (Token){STRING, "sub"};
                break;
            case '*':
                t_new = (Token){STRING, "mul"};
                break;
            case '/':
                t_new = (Token){STRING, "div"};
                break;
            case '^':
                t_new = (Token){STRING, "pow"};
                break;
            case '!':
                t_new = (Token){STRING, "fact"};
                break;
            case '.':
                t_new = (Token){STRING, "period"};
                break;
            default:
                break;
            }
            if (temp.type == R_PAREN) {
                size_t j = i - 1;
                size_t r_paren_count = 1;
                size_t l_paren_count = 0;
                while (j > 0) {
                    j--;
                    if (t_stack->tokens[j].type == R_PAREN) {
                        r_paren_count++;
                    }
                    if (t_stack->tokens[j].type == L_PAREN) {
                        l_paren_count++;
                        if (l_paren_count == r_paren_count) {
                            break;
                        }
                    }
                }
                memmove(t_stack->tokens + j + 1, t_stack->tokens + j,
                        sizeof(Token) * (i - j));
                t_stack->tokens[j] = t_new;
                continue;
            } else if (t_stack->tokens[i - 1].type == L_PAREN) {
                fprintf(
                    stderr,
                    "Error: Invalid positioning of openining parenthesis '('");
                exit(EXIT_FAILURE);
            }
            t_stack->tokens[i - 1] = t_new;
            t_stack->tokens[i] = temp;
        }
    }
    // Debug help
    // for (size_t a = 0; a < t_stack->size; ++a) {
    //     printf("%s\n", t_stack->tokens[a].text);
    // }
}
