#include "../include/arithmancer.h"

int tokenize(Queue*q, char* in) {
	assert(q != NULL);
	assert(in != NULL);
	int current = 0;
	char strnum[TOKEN_BUFFER_SIZE];
	int i;
	int success;
	while (in[current] != '\0' && current < MAX_SIZE){
		i = 0;
		Token t;
		if(in[current] == ' ' || in[current] == '\n') {
			current++;
			continue;
		}
		if(is_num(in[current]) == 1){
			while(is_num(in[current]) == 1 && current < MAX_SIZE && i < TOKEN_BUFFER_SIZE){
				strnum[i] = in[current];
				current++;
				i++;
			}
			strnum[i] = '\0';
			double f = atof(strnum);
			t.type = TOKEN_NUMBER;
			t.value.number = f;
			success = queue_push(q, &t);
			assert(success == 0);
			continue;
		}
		if(is_operator(in[current]) == 1) {
			t.type = TOKEN_OPERATOR;
			t.value.op = char_to_operator(in[current]);
			current++;
			success = queue_push(q, &t);
			assert(success == 0);
			continue;
		}
		if(in[current] == '('){
			t.type = TOKEN_LEFT_BRACKET;
			current++;
			success = queue_push(q, &t);
			assert(success == 0);
			continue;
		}
		if(in[current] == ')'){
			t.type = TOKEN_RIGHT_BRACKET;
			current++;
			success = queue_push(q, &t);
			assert(success == 0);
			continue;
		}
	}
	return 0;
}


int should_move_operator(Stack* os, Token* t){
	assert(os != NULL);
	assert(t != NULL);
	if(t->type == TOKEN_NUMBER) {return 0;}
	if(stack_empty(os) == 1) return 0;

	Token* peek = stack_peek(os);
	assert(peek != NULL);
	int peek_pr = operator_precedence(peek->value.op);
	int t_pr = operator_precedence(t->value.op);
	int t_left_ass = operator_left_associative(t->value.op);

	return (peek->type != TOKEN_LEFT_BRACKET &&
	(peek_pr > t_pr || (t_pr == peek_pr && t_left_ass)));
}

int shunting_yard(Queue* token_queue, Queue* out_queue, Stack* operator_stack){
	assert(token_queue != NULL);
	assert(out_queue != NULL);
	assert(operator_stack != NULL);
	for(int i = 0; queue_empty(token_queue) != 1 && i < MAX_SIZE; i++){
		int success;
		Token* t = queue_pull(token_queue);
		assert(t != NULL);
		if(t->type == TOKEN_NUMBER){
			success = queue_push(out_queue, t);
			assert(success == 0);
		}
		else if (t->type == TOKEN_OPERATOR){
			while (should_move_operator(operator_stack, t) == 1){
				success = queue_push(out_queue, stack_pop(operator_stack));
				assert(success == 0);
			}
			success =stack_push(operator_stack, t);
			assert(success == 0);
		}
		else if(t->type == TOKEN_LEFT_BRACKET){
			success =stack_push(operator_stack, t);
			assert(success == 0);
		}
		else if(t->type == TOKEN_RIGHT_BRACKET){
			while (stack_empty(operator_stack) != 1){
				Token* next_token = stack_peek(operator_stack);
				assert(next_token != NULL);
				if(next_token != NULL && next_token->type == TOKEN_LEFT_BRACKET) {
					break;
				}
				next_token = stack_pop(operator_stack);
				assert(next_token != NULL);
				success = queue_push(out_queue, next_token);
				assert(success == 0);
			}
			success = stack_pop_discard(operator_stack);
			assert(success == 0);
		}
	}
	while (stack_empty(operator_stack) != 1){
		int success = queue_push(out_queue, stack_pop(operator_stack));
		assert(success == 0);
	}
	return 0;
}

int calculate(Queue* out_queue, Stack* a_stack){
	assert(out_queue != NULL);
	assert(a_stack != NULL);
	while(queue_empty(out_queue) != 1){
		Token* t = queue_pull(out_queue);
		assert(t != NULL);
		if(t->type == TOKEN_NUMBER){
			int success = stack_push(a_stack, t);
			assert(success == 0);
		}
		else if(t->type == TOKEN_OPERATOR){
			Token result;
			result.type = TOKEN_NUMBER;
			Token* b = stack_pop(a_stack);
			assert(b != NULL);
			if(b == NULL) { return 1; }
			Token* a = stack_pop(a_stack);
			assert(a != NULL);
			if(a == NULL) { return 1; }
			if (t->value.op== ADD){result.value.number = a->value.number + b->value.number;}
			if (t->value.op== SUB){result.value.number = a->value.number - b->value.number;}
			if (t->value.op== MUL){result.value.number = a->value.number * b->value.number;}
			if (t->value.op== DIV){
				assert(b->value.number != 0.0);
				if(b->value.number == 0.0){ return -1;}
				result.value.number = a->value.number / b->value.number;
			}
			if (t->value.op== POW){result.value.number = pow(a->value.number, b->value.number);}
			int success = stack_push(a_stack, &result);
			assert(success == 0);
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

	while(1){
		int success = queue_init(&token_queue);
		assert(success == 0);
		success = queue_init(&out_queue);
		assert(success == 0);
		success = stack_init(&operator_stack);
		assert(success == 0);
		success = stack_init(&a_stack);
		assert(success == 0);
		printf("> ");
		fgets(input, sizeof(input), stdin);
		if(strcmp(input, "q\n") == 0){break;}

		// char* in = "3.14159 * ( 5.5 + 12.9 )";
		success = tokenize(&token_queue, input);
		if(success != 0) {
			printf("an error occurred tokenizing input\n"); 
			continue;
		}
		success = shunting_yard(&token_queue, &out_queue, &operator_stack);
		if(success != 0) {
			printf("an error occurred during shunting yard\n"); 
			continue;
		}
		success = calculate(&out_queue, &a_stack);
		if(success != 0) {
			printf("an error occurred during calculation\n"); 
			continue;
		}
		printf("%f\n\n", a_stack.tokens[0].value.number);
	}
	return 0;
}
