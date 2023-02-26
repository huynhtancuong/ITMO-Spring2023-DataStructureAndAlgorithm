#include <stdio.h>
#define MAX_LENGTH 100000



typedef struct
{
    int stack[MAX_LENGTH];
    size_t top;
} Stack;

Stack stack_init() {
    Stack stack;
    stack.top = 0;
    return stack;
}

void stack_push(Stack *stack, int num) {
    stack->stack[stack->top++] = num;
}

int stack_pop(Stack *stack) {
    return stack->stack[--stack->top];
}

int stack_seek(Stack *stack) {
    return stack->stack[stack->top - 1];
}


int main() {
	int n;
    scanf("%d", &n);

    Stack stack = stack_init();

    int counter = 0;

    for (int i = 0; i<n; i++) {
        int current;
        scanf("%d", &current);
        while (counter < current) stack_push(&stack, ++counter);
        if (current == stack_seek(&stack)) stack_pop(&stack);
    }

    if (stack.top == 0) printf("Not a proof");
    else printf("Cheater");
    
	return 0;
}
