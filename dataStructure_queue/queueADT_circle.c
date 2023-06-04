#include <stdio.h>
#include <stdlib.h>
#include "queueADT_circle.h"

struct queue_type {
	Item *contents; //ȯ�� �迭
	int front;
	int rear;
	int size; //������ ����	
	int capacity; //�迭 contents ũ��
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
	q->rear = -1; //ȯ�� �迭�� �����ϱ� ���ؼ� ����
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

void enqueue(Queue q, Item i) { //push ����
	if (is_full(q))
		reallocate(q);

	q->rear = (q->rear + 1) % q->capacity; //ȯ�� �迭 ����
	q->contents[q->rear] = i;
	q->size++;
}

Item dequeue(Queue q) { //pop ����
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
	//ȯ�� �迭���� reallocate()�� �����ϴ�
	//front���� rear���� ������ ������� ���ļ� ���Ҵ�� �迭�� �־�� �Ѵ�.
	Item *tmp = (Item*)malloc(2 * q->capacity * sizeof(Item));
	if (tmp == NULL)
		terminate("Error in create : queue could not be expanded.");

	int j = q->front;

	for (int i = 0; i < q->size; i++) { //ȯ���� ���������� ���ļ� front->rear ������� ��迭�Ѵ�
		tmp[i] = q->contents[j];
		j = (j + 1) % q->capacity;
	}
	free(q->contents);

	q->front = 0;
	q->rear = q->size - 1;
	q->contents = tmp;
	q->capacity *= 2;
}