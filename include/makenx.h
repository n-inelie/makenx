#ifndef MAKENX_H
#define MAKENX_H

#include <stdbool.h>
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

typedef struct {
    char *name;
    double value;
} Var;

typedef struct {
    size_t capacity;
    size_t size;
    Var *vars;
} VarStack;

bool are_var_equal(Var v1, Var v2);

// Returns -1 if var does not exist
int does_var_exist(VarStack *v_stack, char *name);

double get_var_value(VarStack *v_stack, char *name);

VarStack *create_var_stack(size_t reserve);
void destroy_var_stack(VarStack *v_stack);
void append_var(VarStack *v_stack, Var t);
void print_var_stack(VarStack *v_stack);

double get_var_value(VarStack *v_stack, char *name);
void set_var_value(VarStack *v_stack, char *name, double value);
bool are_all_var_set(VarStack *v_stack);

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
    union {
        double value;
        Var v;
    };
} Node;

void destroy_node(Node *n);

void parse(TokenStack *t_stack, size_t stack_index, VarStack *v_stack,
           Node *current_node);
double evaluate(Node *n, VarStack *v_stack);

void print_node(Node *n, size_t padding);

#endif
