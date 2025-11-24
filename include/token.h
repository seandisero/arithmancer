#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {
	TOKEN_NUMBER,
	TOKEN_OPERATOR,
	TOKEN_LEFT_BRAKET,
	TOKEN_RIGHT_BRAKET
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
int operator_precidence(OperatorType op);
int operator_left_associative(OperatorType op);
int token_print(Token* t);

int is_num(char c);
int is_left_braket(char c);
int is_right_braket(char c);
int is_operator(char c);
OperatorType char_to_operator(char c);

#endif // TOKEN_H
