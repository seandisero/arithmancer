#include <stdio.h>
#include <stdlib.h>

typedef enum {
	ERR = '\0',
	ADD = '+',
	SUB = '-',
	MUL = '*',
	DIV = '/'
} operator_type;

typedef struct {
	int index;
	operator_type t;
} operator_t;

typedef struct {
	int len;
	int first;
	int last;
	int result;
	operator_t op;
	char input[64];
	char intstr[64];
} data_t;

operator_type operator(char c){
	switch (c){
		case ADD:
			return ADD;
		case SUB:
			return SUB;
		case MUL:
			return MUL;
		case DIV:
			return DIV;
	}
	return ERR;
}

int split_by_operator(data_t* data) {
	int i = 0;
	char* in = data->input;
	for (; in[i] != '\0'; i++) {
		operator_type op = operator(in[i]);
		if(op != ERR) {
			data->op.index = i;
			data->op.t = op;
			return 1;
		}
	}
	return 0;
}

int string_to_int(data_t* data, int lower, int upper) {
	int i = lower;
	for (; i < upper; i++) {
		data->intstr[i - lower] = data->input[i];
	}
	data->intstr[i-lower] = '\0';
	return atoi(data->intstr);
}

int string_length(char* in){
	int i = 0;
	for(; in[i] != '\0' && i < 1000; i++){
	}
	return i;
}

int add(int a, int b){
	return a + b;
}

int sub(int a, int b){
	return a - b;
}

int mul(int a, int b){
	return a * b;
}

int dvi(int a, int b){
	return a / b;
}

void handle_input(data_t* data){
	printf(":");
	scanf_s("%s", data->input, sizeof(data->input));
}

int run(data_t* data) {
	while (1) {
		handle_input(data);
		data->len = string_length(data->input); 
		int success = split_by_operator(data);
		if(success == 0) {continue;}
		data->first = string_to_int(data, 0, data->op.index);
		data->last = string_to_int(data, data->op.index + 1, data->len);
		switch (data->op.t) {
			case ADD:
				data->result = add(data->first, data->last);
				printf("= %d\n\n", data->result);
				break;
			case SUB:
				data->result = sub(data->first, data->last);
				printf("= %d\n\n", data->result);
				break;
			case MUL:
				data->result = mul(data->first, data->last);
				printf("= %d\n\n", data->result);
				break;
			case DIV:
				data->result = dvi(data->first, data->last);
				printf("= %d\n\n", data->result);
				break;
			case ERR:
				printf("an error occered");
				break;
		}
	}
	return 0;
}

int main() {
	data_t data;
	int out = run(&data);
	exit(out);
}
