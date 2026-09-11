#include <stdio.h>
#include <stdbool.h>

struct Stack {
    int arr[10];
    int top;
};

void push(struct Stack *st, int x) {
    if (st->top == 9) {
        printf("Stack Overflow\n");
        return;
    }
    st->top++;
    st->arr[st->top] = x;
}

void pop(struct Stack *st) {
    if (st->top == -1) {
        printf("Stack Underflow\n");
        return;
    }
    st->top--;
}

int peek(struct Stack *st) {
    if (st->top == -1) {
        printf("Stack is empty\n");
        return -1;
    }
    return st->arr[st->top];
}

bool isEmpty(struct Stack *st) {
    return st->top == -1;
}

int main() {
    struct Stack st;
    st.top = -1;
    push(&st, 10);
    push(&st, 20);
    push(&st, 30);
    push(&st, 40);
    printf("%d\n", peek(&st));
    pop(&st);
    printf("%d\n", peek(&st));
    return 0;
}