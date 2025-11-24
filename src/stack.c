#include "../include/stack.h"

int stack_init(Stack* s){
	if(s == NULL) {return 1;}
	s->size = 0;
	return 0;
}

int stack_empty(Stack* s){
	if(s==NULL){return 1;}
	if(s->size == 0){return 1;}
	return 0;
}

int stack_push(Stack* s, Token* t) {
	if(s==NULL){return 0;}
	s->tokens[s->size++] = *t;
	return 1;
}

Token* stack_pop(Stack* s) {
	if(s==NULL){return NULL;}
	if(stack_empty(s) == 1) {return NULL;}
	s->size--;
	return &s->tokens[s->size];
}

Token* stack_peek(Stack* s){
	if(s==NULL){return NULL;}
	if(stack_empty(s) == 1) {return NULL;}
	return &s->tokens[s->size-1];
}

void stack_print(Stack* s){
	char str[MAX_SIZE];
	for(int i = 0; i < s->size; i++) {
		token_print(&s->tokens[i]);
		printf(" ");
	}
}
