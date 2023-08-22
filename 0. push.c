#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

typedef struct {
    int data[STACK_SIZE];
    int top;
} Stack;

void push(Stack *stack, int value) {
    if (stack->top < STACK_SIZE) {
        stack->data[stack->top++] = value;
    } else {
        fprintf(stderr, "Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

int pop(Stack *stack) {
    if (stack->top > 0) {
        return stack->data[--stack->top];
    } else {
        fprintf(stderr, "Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

void pall(Stack *stack) {
    for (int i = stack->top - 1; i >= 0; i--) {
        printf("%d\n", stack->data[i]);
    }
}

int main() {
    FILE *file = fopen("bytecodes/00.m", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    Stack stack;
    stack.top = 0;

    char line[100];
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        char opcode[10];
        int value;

        if (sscanf(line, "%9s %d", opcode, &value) == 2) {
            if (strcmp(opcode, "push") == 0) {
                push(&stack, value);
            } else {
                fprintf(stderr, "Error at line %d: Unknown opcode '%s'\n", line_number, opcode);
                return EXIT_FAILURE;
            }
        } else if (strcmp(opcode, "pall") == 0) {
            pall(&stack);
        } else if (strcmp(opcode, "push") == 0) {
            fprintf(stderr, "Error at line %d: usage: push integer\n", line_number);
            return EXIT_FAILURE;
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}
