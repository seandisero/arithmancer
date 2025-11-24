#include "token.h"
#include "stack.h"
#include "queue.h"

#ifndef ARITHMANCER_H
#define ARITHMANCER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tokenize(Queue* q, char* in);
int should_move_operator(Stack* os, Token* t);
int shunting_yard(Queue* token_queue, Queue* out_queue, Stack* operator_stack);
int calculate(Queue* out_queue, Stack* a_stack);

int run(void);

#endif // ARITHMANCER_H
