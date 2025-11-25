#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef enum {
	TOKEN_NUMBER,
	TOKEN_OPERATOR,
	TOKEN_LEFT_BRACKET,
	TOKEN_RIGHT_BRACKET
} TokenType;

typedef enum {
	ADD = '+',
	SUB = '-',
	MUL = '*',
	DIV = '/',
	POW = '^',
} OperatorType;

typedef union {
	OperatorType op;
	double number;
} TokenValue;

typedef struct {
	TokenType type;
	TokenValue value;
} Token;

int operator_type_print(OperatorType ot);
int operator_precedence(OperatorType op);
int operator_left_associative(OperatorType op);
int token_print(Token* t);

int is_num(char c);
int is_operator(char c);
OperatorType char_to_operator(char c);

#endif // TOKEN_H
