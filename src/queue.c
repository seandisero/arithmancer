#include "../include/queue.h"

int queue_init(Queue* q){
	assert(q != NULL);
	q->upper = -1;
	q->lower = 0;
	assert(q->upper == -1);
	assert(q->lower == 0);
	return 0;
}

int queue_empty(Queue* q){
	assert(q != NULL);
	return q->upper < q->lower;
}

int queue_push(Queue* q, Token* t){
	assert(q != NULL);
	assert(t != NULL);
	assert(q->upper < MAX_SIZE);
	if(q->upper - q->lower + 1 >= MAX_SIZE) { return 1; }
	int old_upper = q->upper;
	q->upper++;
	assert(q->upper > old_upper);

	q->tokens[q->upper] = *t;
	return 0;
}

Token* queue_pull(Queue* q){
	assert(q != NULL);
	if(q == NULL) {return NULL;}
	if(queue_empty(q)){return NULL;}
	Token* t = &q->tokens[q->lower++];
	assert(t != NULL);
	return t;
}

void queue_print(Queue* q){
	assert(q != NULL);
	for(int i = q->lower; i <= q->upper; i++) {
		token_print(&q->tokens[i]);
		printf("\n");
	}
}
