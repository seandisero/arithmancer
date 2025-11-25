#include "../include/stack.h"

int stack_init(Stack* s){
	assert(s != NULL);
	if(s == NULL) {return 1;}
	s->size = 0;
	assert(s->size == 0);
	return 0;
}

int stack_empty(Stack* s){
	assert(s != NULL);
	if(s==NULL){return 1;}
	if(s->size == 0){return 1;}
	return 0;
}

int stack_push(Stack* s, Token* t) {
	assert(s != NULL);
	assert(t != NULL);

	if(s==NULL){return 1;}
	if(s->size + 1 >= MAX_SIZE) { return 1; }
	s->tokens[s->size++] = *t;

	assert(s->size < MAX_SIZE);
	return 0;
}

Token* stack_pop(Stack* s) {
	assert(s != NULL);
	if(s==NULL){return NULL;}
	if(stack_empty(s) == 1) {return NULL;}
	s->size--;
	assert(s->size >= 0);
	return &s->tokens[s->size];
}

int stack_pop_discard(Stack* s) {
	assert(s != NULL);
	if(s==NULL){return 1;}
	if(stack_empty(s) == 1) {return 1;}
	s->size--;
	assert(s->size >= 0);
	return 0;
}

Token* stack_peek(Stack* s){
	assert(s != NULL);
	if(s==NULL){return NULL;}
	if(stack_empty(s) == 1) {return NULL;}
	assert(s->size != 0);
	return &s->tokens[s->size-1];
}

void stack_print(Stack* s){
	assert(s != NULL);
	for(int i = 0; i < s->size; i++) {
		token_print(&s->tokens[i]);
		printf(" ");
	}
}
