#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct node
{
    char c;
    struct node *next;
}*top;

void push(char c)
{
    struct node *node = (struct node*)malloc(sizeof(struct node));
    node->c = c;
    if (top==NULL)
    {
        node->next = NULL;
        top = node;
    }
    else
    {
        node->next = top;
        top = node;
    }
}

void pop()
{
    if(top==NULL)
    {
        printf("Stack is empty\n");
    }
    else
    {
        struct node *del = top;
        top = top->next;
        free(del);
    }
}

int precedence(char c) {
    if(c == '^')
        return 3;
    else if(c == '*' || c == '/')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else
        return -1;
}

void infixToPostfix(char* infix, char* postfix) {
    int i = 0, j = 0;
    char c;
    while(infix[i] != '\0') {
        c = infix[i];
        if(isalnum(c)) {
            postfix[j++] = c;
        } else if(c == '(') {
            push(c);
        } else if(c == ')') {
            while(top != NULL && top->c != '(') {
                postfix[j++] = top->c;
                pop();
            }
            if(top != NULL && top->c == '(') {
                pop();
            }
        } else {
            while(top != NULL && precedence(c) <= precedence(top->c)) {
                postfix[j++] = top->c;
                pop();
            }
            push(c);
        }
        i++;
    }
    while(top != NULL) {
        postfix[j++] = top->c;
        pop();
    }
    postfix[j] = '\0';
}

void postfixToInfix(char* postfix, char* infix) {
    char stack[100][100];
    int top = -1;
    for(int i = 0; postfix[i] != '\0'; i++) {
        if(isalnum(postfix[i])) {
            char operand[2] = {postfix[i], '\0'};
            strcpy(stack[++top], operand);
        } else {
            char op1[100], op2[100], expr[100];
            strcpy(op1, stack[top--]);
            strcpy(op2, stack[top--]);
            sprintf(expr, "(%s%c%s)", op2, postfix[i], op1);
            strcpy(stack[++top], expr);
        }
    }
    strcpy(infix, stack[top]);
}

int main() {
    int choice;
    char infix[100], postfix[100];
    top = NULL;

    while(1) {
        printf("Menu:\n");
        printf("1. Infix to Postfix\n");
        printf("2. Postfix to Infix\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
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
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}