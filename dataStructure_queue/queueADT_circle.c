#include <stdio.h>
#include <stdlib.h>
#include "queueADT_circle.h"

struct queue_type {
	Item *contents; //환형 배열
	int front;
	int rear;
	int size; //데이터 개수	
	int capacity; //배열 contents 크기
};

void terminate(const char *message) {
	printf("%s\n", message);
	exit(1);
}


int get_size(Queue q) {
	return q->size;
}

Queue create() {
	Queue q = malloc(sizeof(struct queue_type));
	if (q == NULL)
		terminate("Error in create: queue could not be created.");

	q->contents = malloc(sizeof(Item*) * INIT_CAPACITY);
	if (q->contents == NULL) {
		free(q);
		terminate("Error in create: queue could not be created.");
	}
		
	q->front = 0;
	q->rear = -1; //환형 배열을 구현하기 위해서 설정
	q->size = 0;
	q->capacity = INIT_CAPACITY;

	return q;
}

void destroy(Queue q) {
	free(q->contents);
	free(q);
}

void make_empty(Queue q) {
	q->front = 0;
	q->rear = -1;
	q->size = 0;
}

bool is_empty(Queue q) {
	return q->size == 0;
}

bool is_full(Queue q) {
	return q->size == q->capacity;
}

void enqueue(Queue q, Item i) { //push 역할
	if (is_full(q))
		reallocate(q);

	q->rear = (q->rear + 1) % q->capacity; //환형 배열 구현
	q->contents[q->rear] = i;
	q->size++;
}

Item dequeue(Queue q) { //pop 역할
	if (is_empty(q))
		terminate("Error in create: queue is empty.");

	Item result = q->contents[q->front];

	q->front = (q->front + 1) % q->capacity;
	q->size--;

	return result;
}

Item peek(Queue q) {
	if (is_empty(q))
		terminate("Error in create: queue is empty.");

	return q->contents[q->front];
}

void reallocate(Queue q) { 
	//환형 배열에서 reallocate()는 복잡하다
	//front부터 rear까지 일직선 순서대로 펼쳐서 재할당된 배열에 넣어야 한다.
	Item *tmp = (Item*)malloc(2 * q->capacity * sizeof(Item));
	if (tmp == NULL)
		terminate("Error in create : queue could not be expanded.");

	int j = q->front;

	for (int i = 0; i < q->size; i++) { //환형을 일직선으로 펼쳐서 front->rear 순서대로 재배열한다
		tmp[i] = q->contents[j];
		j = (j + 1) % q->capacity;
	}
	free(q->contents);

	q->front = 0;
	q->rear = q->size - 1;
	q->contents = tmp;
	q->capacity *= 2;
}