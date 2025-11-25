#include "token.h"
#include "globals.h"

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
	int lower;
	int upper;
	Token tokens[MAX_SIZE];
} Queue;

int queue_init(Queue* q);
int queue_empty(Queue* q);
int queue_push(Queue* q, Token* t);
Token* queue_pull(Queue* q);
void queue_print(Queue* q);

#endif
