#include "../include/token.h"

int operator_type_print(OperatorType ot) {
	assert(ot == ADD || ot == SUB || ot == MUL || ot == DIV || ot == POW);

	int result;
	switch(ot){
		case ADD:
			printf("ADD");
			result = 0;
			break;
		case SUB:
			printf("SUB");
			result = 0;
			break;
		case MUL:
			printf("MUL");
			result = 0;
			break;
		case DIV:
			printf("DIV");
			result = 0;
			break;
		case POW:
			printf("POW");
			result = 0;
			break;
		default:
			result = 1;
			break;
	}
	assert(result == 0);
	return result;
}

int operator_precedence(OperatorType ot){
	assert(ot == ADD || ot == SUB || ot == MUL || ot == DIV || ot == POW);

	int result;
	switch (ot)
	{
	case ADD:
		result = 2;
		break;
	case SUB:
		result = 2;
		break;
	case MUL:
		result = 3;
		break;
	case DIV:
		result = 3;
		break;
	case POW:
		result = 4;
		break;
	default:
		result = -1;
		break;
	}
	assert(result >= 2 && result <= 4);
	return result;
}

int operator_left_associative(OperatorType op){
	assert(op == ADD || op == SUB || op == MUL || op == DIV || op == POW);
	int result = 1;
	if(op == POW) {
		result = 0;
	} 
	assert(result == 0 || result == 1);
	return result;
}

int token_print(Token* t){
	assert(t != NULL);
	if(t == NULL){return 1;}

	int result = 1;
	switch (t->type) {
		case TOKEN_NUMBER:
			printf("num: %f", t->value.number);
			result = 0;
			break;
		case TOKEN_OPERATOR:
			printf("operator: ");
			result = operator_type_print(t->value.op);
			break;
		case TOKEN_LEFT_BRACKET:
			printf("bracket: left");
			result = 0;
			break;
		case TOKEN_RIGHT_BRACKET:
			printf("bracket: right");
			result = 0;
			break;
		default:
			result = 1;
			break;
	}
	assert(result == 0 || result == 1);
	return result;
}

int is_num(char c){
	if((c >= '0' && c <= '9') || c == '.') {return 1;}
	return 0;
}

int is_operator(char c){
	if(c == ADD || c == SUB || c == MUL || c == DIV || c == POW){
		return 1;
	}
	return 0;
}

OperatorType char_to_operator(char c){
	assert(c == ADD || c == SUB || c == MUL || c == DIV || c == POW);
	OperatorType o = (OperatorType)c;
	return o;
}

