#include <stdio.h>
#include <stdbool.h>

struct Queue {
    int arr[10];
    int front;
    int rear;
};

void enqueue(struct Queue *q, int x) {
    if (q->rear == 9) {
        printf("Queue Overflow\n");
        return;
    }

    q->rear++;
    q->arr[q->rear] = x;
}

void dequeue(struct Queue *q) {
    if (q->front > q->rear) {
        printf("Queue Underflow\n");
        return;
    }

    q->front++;
}

int peek(struct Queue *q) {
    if (q->front > q->rear) {
        printf("Queue is empty\n");
        return -1;
    }

    return q->arr[q->front];
}

bool isEmpty(struct Queue *q) {
    return q->front > q->rear;
}

int main() {
    struct Queue q;
    q.front = 0;
    q.rear = -1;
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    printf("%d\n", peek(&q));
    dequeue(&q);
    printf("%d\n", peek(&q));
    return 0;
}