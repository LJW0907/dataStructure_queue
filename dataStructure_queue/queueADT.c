#include <stdio.h>
#include <stdlib.h>
#include "queueADT.h"

struct node {
	Item data;
	struct node *next;
};

struct queue_type {
	struct node *front;
	struct node *rear;
	int size;
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

	q->front = NULL;
	q->rear = NULL;
	q->size = 0;

	return q;
}

void destroy(Queue q) {
	make_empty(q);
	free(q);
}

void make_empty(Queue q) {
	while (!is_empty(q))
		dequeue(q);
	q->size = 0;
}

bool is_empty(Queue q) {
	return q->front == NULL;
}

void enqueue(Queue q, Item i) { //push ����
	struct node *new_node = (struct node*)malloc(sizeof(struct node));
	if (new_node == NULL)
		terminate("Error in create: node could not be created.");

	new_node->data = i;
	new_node->next = NULL;

	if (q->front == NULL) { //ù ��� ����
		q->front = new_node;
		q->rear = new_node;
	}
	else {
		q->rear->next = new_node;
		q->rear = new_node;
	}
	q->size++;
}

Item dequeue(Queue q) { //pop ����
	struct node *tmp;
	Item i;

	if (is_empty(q))
		terminate("Error in create: queue is empty.");

	tmp = q->front;
	i = q->front->data;
	
	if(q->front->next == NULL) //��尡 �� ��
		q->rear = NULL;

	q->front = q->front->next;

	free(tmp);
	q->size--;

	return i;
}
Item peek(Queue q) {
	if (is_empty(q))
		terminate("Error in create: queue is empty.");

	return q->front->data;
}