#ifndef MAKENX_H
#define MAKENX_H

#include <stddef.h>

typedef enum {
    STRING,
    NUMERIC,
    L_PAREN,
    R_PAREN,
    COMMA,
    OPERATOR,
} TokenType;

typedef struct {
    TokenType type;
    char *text;
} Token;

typedef struct {
    size_t capacity;
    size_t size;
    Token *tokens;
} TokenStack;

TokenStack *create_token_stack(size_t reserve);
void destroy_token_stack(TokenStack *t_stack);
void append_token(TokenStack *t_stack, Token t);

void tokenize(TokenStack *t_stack, char *str);
void filter_token_stack(TokenStack *t_stack);

typedef enum {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    POW,
    FACT,
    LN,
    LOG,
    LOG10,
    LOG2,
    LOGAB,
    SIN,
    COS,
    TAN, 
    VARIABLE,
    NUMBER,
    ROOT,
    PERIOD,
} Symbol;

Symbol get_symbol(char *str);

typedef struct node {
    Symbol sym;
    size_t sub_nodes_count;
    struct node **sub_nodes;
    double value;
} Node;

void destroy_node(Node *n);

void parse(TokenStack *t_stack, size_t stack_index, Node *current_node);
double evaluate(Node *n);

void print_node(Node *n, size_t padding);

#endif
