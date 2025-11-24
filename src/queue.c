#include "../include/queue.h"

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
