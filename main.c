#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

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
	OperatorType operator;
	double number;
} TokenValue;

typedef struct {
	TokenType type;
	TokenValue value;
} Token;

typedef struct {
	int size;
	Token tokens[MAX_SIZE];
} Stack;

typedef struct {
	int lower;
	int upper;
	Token tokens[MAX_SIZE];
} Queue;

int operator_type_print(OperatorType ot){
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
	switch (op){
		case ADD:
			return 1;
		case SUB:
			return 1;
		case MUL:
			return 1;
		case DIV:
			return 1;
		case POW:
			return 0;
	}
}

int token_print(Token* t){
	if(t == NULL){return 1;}
	if(t->type == TOKEN_NUMBER){
		printf("num: %f", t->value.number);
		return 0;
	}
	else if(t->type == TOKEN_OPERATOR){
		printf("operator: ");
		return operator_type_print(t->value.operator);
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

int queue_init(Queue* q){
	if(q == NULL) {return 1;}
	q->upper = -1;
	q->lower = 0;
	return 0;
}

int queue_empty(Queue* q){
	return q->upper < q->lower;
}

int queue_push(Queue* q, Token* t){
	if(q == NULL) {return 1;}
	q->upper++;
	q->tokens[q->upper] = *t;
	return 0;
}

Token* queue_pull(Queue* q){
	if(q == NULL) {return NULL;}
	return &q->tokens[q->lower++];
}

void queue_print(Queue* q){
	for(int i = q->lower; i <= q->upper; i++) {
		token_print(&q->tokens[i]);
		printf("\n");
	}
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
	if(c == ADD || c == SUB || c == MUL || c == DIV){
		return 1;
	}
	return 0;
}

OperatorType char_to_operator(char c){
	OperatorType o = (OperatorType)c;
	return o;
}

int tokenize(Queue*q, char* in) {
	int current = 0;
	char str[64];
	int i;
	while (in[current] != '\0'){
		i = 0;
		Token t;
		while(in[current] == ' ') {
			current++;
			continue;
		}
		if(is_num(in[current]) == 1){
			while(is_num(in[current]) == 1){
				str[i] = in[current];
				current++;
				i++;
			}
			str[i] = '\0';
			double f = atof(str);
			t.type = TOKEN_NUMBER;
			t.value.number = f;
			queue_push(q, &t);
			continue;
		}
		if(is_operator(in[current]) == 1) {
			str[i] = in[current];
			t.type = TOKEN_OPERATOR;
			t.value.operator = char_to_operator(in[current]);
			current++;
			queue_push(q, &t);
			continue;
		}
		if(in[current] == '('){
			t.type = TOKEN_LEFT_BRAKET;
			current++;
			queue_push(q, &t);
			continue;
		}
		if(in[current] == ')'){
			t.type = TOKEN_RIGHT_BRAKET;
			current++;
			queue_push(q, &t);
			continue;
		}
	}
	return 0;
}

int run(){
	char input[MAX_SIZE];
	Queue q;
	queue_init(&q);
	while(1){
		scanf_s("%s", input);
		if(strcmp(input, "q") == 0){break;}
		tokenize(&q, input);
		printf("stack size: %d", q.upper - q.lower);
		queue_print(&q);
	}
	return 0;
}

int should_move_operator(Stack* os, Token* t){
	if(t->type == TOKEN_NUMBER) {return -1;}
	if(stack_empty(os) == 1) return 0;
	Token* peek = stack_peek(os);
	int peek_pr = operator_precidence(peek->value.operator);
	int t_pr = operator_precidence(t->value.operator);
	int t_left_ass = operator_left_associative(t->value.operator);
	return (
	peek->type != TOKEN_LEFT_BRAKET &&
	(peek_pr > t_pr || (t_pr == peek_pr && t_left_ass)));
}

int main() {
	Queue token_queue;
	queue_init(&token_queue);
	char* input = "3.14159 * ( 5.5 + 12.9 )";

	int success = tokenize(&token_queue, input);
	printf("\n");
	printf("tokenization success: %d\nnum tokens: %d\n", success, token_queue.upper);
	printf("%s\n", input);
	queue_print(&token_queue); printf("\n");
	printf("\n\n");

	Queue out_queue;
	Stack operator_stack;
	success = queue_init(&out_queue);
	success = stack_init(&operator_stack);
	printf("queue empty: %d\n", queue_empty(&out_queue));

	for(int i = 0; queue_empty(&token_queue) != 1; i++){
		Token* t = queue_pull(&token_queue);
		if(t->type == TOKEN_NUMBER){
			queue_push(&out_queue, t);
		}
		else if (t->type == TOKEN_OPERATOR){
			while (should_move_operator(&operator_stack, t) == 1){
				queue_push(&out_queue, stack_pop(&operator_stack));
			}
			stack_push(&operator_stack, t);
		}
		else if(t->type == TOKEN_LEFT_BRAKET){
			stack_push(&operator_stack, t);
		}
		else if(t->type == TOKEN_RIGHT_BRAKET){
			while (stack_peek(&operator_stack)->type != TOKEN_LEFT_BRAKET){
				if(stack_empty(&operator_stack) == 1){
					return -1;
				}
				queue_push(&out_queue, stack_pop(&operator_stack));
			}
			Token* discard = stack_pop(&operator_stack);
		}
	}
	while (stack_empty(&operator_stack) != 1){
		queue_push(&out_queue, stack_pop(&operator_stack));
	}
	queue_print(&out_queue); printf(" <- out queue\n");

	return 0;
}
