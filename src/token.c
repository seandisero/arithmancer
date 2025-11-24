#include "../include/token.h"

int operator_type_print(OperatorType ot) {
	switch(ot){
		case ADD:
			printf("ADD");
			return 0;
		case SUB:
			printf("SUB");
			return 0;
		case MUL:
			printf("MUL");
			return 0;
		case DIV:
			printf("DIV");
			return 0;
		case POW:
			printf("POW");
			return 0;
	}
	return 1;
}

int operator_precidence(OperatorType op){
	switch (op){
		case ADD:
			return 2;
		case SUB:
			return 2;
		case MUL:
			return 3;
		case DIV:
			return 3;
		case POW:
			return 4;
	}
}

int operator_left_associative(OperatorType op){
	if(op == POW) {return 0;}
	return 1;
}

int token_print(Token* t){
	if(t == NULL){return 1;}
	if(t->type == TOKEN_NUMBER){
		printf("num: %f", t->value.number);
		return 0;
	}
	else if(t->type == TOKEN_OPERATOR){
		printf("operator: ");
		return operator_type_print(t->value.op);
	}
	else if(t->type == TOKEN_LEFT_BRAKET){
		printf("braket: left");
		return 0;
	}
	else if(t->type == TOKEN_RIGHT_BRAKET){
		printf("braket: right");
		return 0;
	}
	return 1;
}

int is_num(char c){
	if(c >= '0' && c <= '9' || c == '.') {return 1;}
	return 0;
}

int is_left_braket(char c){
	return c == '(';
}

int is_right_braket(char c){
	return c == ')';
}

int is_operator(char c){
	if(c == ADD || c == SUB || c == MUL || c == DIV || c == POW){
		return 1;
	}
	return 0;
}

OperatorType char_to_operator(char c){
	OperatorType o = (OperatorType)c;
	return o;
}

