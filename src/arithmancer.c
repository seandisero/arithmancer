#include "../include/arithmancer.h"

int tokenize(Queue*q, char* in) {
	int current = 0;
	char str[64];
	int i;
	while (in[current] != '\0'){
		i = 0;
		Token t;
		while(in[current] == ' '|| in[current] == '\n') {
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
			t.value.op = char_to_operator(in[current]);
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


int should_move_operator(Stack* os, Token* t){
	if(t->type == TOKEN_NUMBER) {return -1;}
	if(stack_empty(os) == 1) return 0;

	Token* peek = stack_peek(os);
	int peek_pr = operator_precidence(peek->value.op);
	int t_pr = operator_precidence(t->value.op);
	int t_left_ass = operator_left_associative(t->value.op);

	return (peek->type != TOKEN_LEFT_BRAKET &&
	(peek_pr > t_pr || (t_pr == peek_pr && t_left_ass)));
}

int shunting_yard(Queue* token_queue, Queue* out_queue, Stack* operator_stack){
	for(int i = 0; queue_empty(token_queue) != 1; i++){
		Token* t = queue_pull(token_queue);
		if(t->type == TOKEN_NUMBER){
			queue_push(out_queue, t);
		}
		else if (t->type == TOKEN_OPERATOR){
			while (should_move_operator(operator_stack, t) == 1){
				queue_push(out_queue, stack_pop(operator_stack));
			}
			stack_push(operator_stack, t);
		}
		else if(t->type == TOKEN_LEFT_BRAKET){
			stack_push(operator_stack, t);
		}
		else if(t->type == TOKEN_RIGHT_BRAKET){
			while (stack_peek(operator_stack)->type != TOKEN_LEFT_BRAKET){
				if(stack_empty(operator_stack) == 1){
					return -1;
				}
				queue_push(out_queue, stack_pop(operator_stack));
			}
			Token* discard = stack_pop(operator_stack);
		}
	}
	while (stack_empty(operator_stack) != 1){
		queue_push(out_queue, stack_pop(operator_stack));
	}
	return 0;
}

int calculate(Queue* out_queue, Stack* a_stack){
	while(queue_empty(out_queue) != 1){
		Token* t = queue_pull(out_queue);
		if(t->type == TOKEN_NUMBER){
			stack_push(a_stack, t);
		}
		else if(t->type == TOKEN_OPERATOR){
			Token result;
			result.type = TOKEN_NUMBER;
			Token* b = stack_pop(a_stack);
			Token* a = stack_pop(a_stack);
			if (t->value.op== ADD){result.value.number = a->value.number + b->value.number;}
			if (t->value.op== SUB){result.value.number = a->value.number - b->value.number;}
			if (t->value.op== MUL){result.value.number = a->value.number * b->value.number;}
			if (t->value.op== DIV){result.value.number = a->value.number / b->value.number;}
			if (t->value.op== POW){result.value.number = pow(a->value.number, b->value.number);}
			stack_push(a_stack, &result);
		}
	}
	return 0;
}

int run(){
	char input[MAX_SIZE];
	Queue token_queue;
	Queue out_queue;
	Stack operator_stack;
	Stack a_stack;

	printf("sizeof(Token) = %zu bytes\n", sizeof(Token));
	printf("sizeof(TokenType) = %zu bytes\n", sizeof(TokenType));
	printf("sizeof(TokenValue) = %zu bytes\n", sizeof(TokenValue));
	printf("sizeof(Queue) = %zu bytes\n", sizeof(token_queue));
	printf("sizeof(Stack) = %zu bytes\n", sizeof(operator_stack));


	while(1){
		int success = queue_init(&token_queue);
		success = queue_init(&out_queue);
		success = stack_init(&operator_stack);
		success = stack_init(&a_stack);
		printf("> ");
		fgets(input, sizeof(input), stdin);
		if(strcmp(input, "q") == 0){break;}

		// char* in = "3.14159 * ( 5.5 + 12.9 )";
		success = tokenize(&token_queue, input);
		success = shunting_yard(&token_queue, &out_queue, &operator_stack);
		success = calculate(&out_queue, &a_stack);
		printf("%f\n\n", a_stack.tokens[0].value.number);
	}
	return 0;
}
