#include "makenx.h"

void filterTokenStack(TokenStack *t_stack) {
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
            }
            t_stack->tokens[i - 1] = t_new;
            t_stack->tokens[i] = temp;
        }
    }
}
