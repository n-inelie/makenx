#ifndef MAKENX_H
#define MAKENX_H

#include <stddef.h>

typedef enum {
    STRING,
    NUMERIC,
    L_PAREN,
    R_PAREN,
    COMMA,
    PERIOD,
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

TokenStack *CreateStack(size_t reserve);
void destroyTokenStack(TokenStack *t_stack);
void appendToken(TokenStack *t_stack, Token t);

typedef struct {
    size_t l_paren_count;
    size_t r_paren_count;
    size_t comma_count;
    size_t period_count;
} Stats;

void tokenize(Stats *stats, TokenStack *t_stack, char *str);

typedef enum {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    POW,
    VARIABLE,
    NUMBER,
    ROOT,
} Symbol;

extern Symbol OMap[1024];
void initOMap(void);
size_t hash(char *str);

typedef struct node {
    Symbol sym;
    size_t sub_nodes_count;
    struct node **sub_nodes;
    double value;
} Node;

void destroyNode(Node *n);

void parse(TokenStack *t_stack, size_t stack_index, Node *current_node);
double evaluate(Node *n);


#endif
