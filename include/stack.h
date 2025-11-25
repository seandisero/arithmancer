#include "token.h"
#include "globals.h"

#ifndef STACK_H 
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
	int size;
	Token tokens[MAX_SIZE];
} Stack;

int stack_init(Stack* s);
int stack_empty(Stack* s);
int stack_push(Stack* s, Token* t);
Token* stack_pop(Stack* s);
int stack_pop_discard(Stack* s);
Token* stack_peek(Stack* s);
void stack_print(Stack* s);

#endif
