#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

void push(Stack* stack, char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

char* pop(Stack* stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    Node* temp = stack->top;
    char* data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

char peek(Stack* stack) {
    if (stack->top == NULL) {
        return '\0';
    }
    return *(stack->top->data);
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void infixToPostfix(char* infix, char* postfix) {
    Stack stack = {NULL};
    int k = 0;
    for (int i = 0; infix[i]; i++) {
        if (isdigit(infix[i]) || isalpha(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            char temp[2] = {infix[i], '\0'};
            push(&stack, temp);
        } else if (infix[i] == ')') {
            while (stack.top && peek(&stack) != '(') {
                postfix[k++] = *(pop(&stack));
            }
            pop(&stack);
        } else if (isOperator(infix[i])) {
            while (stack.top && precedence(peek(&stack)) >= precedence(infix[i])) {
                postfix[k++] = *(pop(&stack));
            }
            char temp[2] = {infix[i], '\0'};
            push(&stack, temp);
        }
    }
    while (stack.top) {
        postfix[k++] = *(pop(&stack));
    }
    postfix[k] = '\0';
}

void postfixToInfix(char* postfix, char* infix) {
    Stack stack = {NULL};
    for (int i = 0; postfix[i]; i++) {
        if (isdigit(postfix[i]) || isalpha(postfix[i])) {
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = postfix[i];
            operand[1] = '\0';
            push(&stack, operand);
        } else if (isOperator(postfix[i])) {
            char* operand2 = pop(&stack);
            char* operand1 = pop(&stack);
            int len = strlen(operand1) + strlen(operand2) + 4;
            char* expr = (char*)malloc(len * sizeof(char));
            snprintf(expr, len, "(%s%c%s)", operand1, postfix[i], operand2);
            push(&stack, expr);
            free(operand1);
            free(operand2);
        }
    }
    strcpy(infix, pop(&stack));
}

int main() {
    int choice;
    char infix[100], postfix[100];
    do {
        printf("\nMenu:\n");
        printf("1. Infix to Postfix\n");
        printf("2. Postfix to Infix\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                scanf("%s", infix);
                infixToPostfix(infix, postfix);
                printf("Postfix expression: %s\n", postfix);
                break;
            case 2:
                printf("Enter postfix expression: ");
                scanf("%s", postfix);
                postfixToInfix(postfix, infix);
                printf("Infix expression: %s\n", infix);
                break;
            case 3:
                printf("Goodbye, have a nice day!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);
    return 0;
}