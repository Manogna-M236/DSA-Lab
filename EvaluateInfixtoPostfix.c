#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE 40

int stack[SIZE];
int top = -1;

void push(int n) {
    if (top < SIZE - 1) {
        stack[++top] = n;
    } else {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
}

int pop() {
    if (top > -1) {
        return stack[top--];
    } else {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char postfix[SIZE];
    int i, a, b, result;
    char ch;

    printf("Enter a postfix expression: ");
    scanf("%s", postfix);

    for (i = 0; postfix[i] != '\0'; i++) {
        ch = postfix[i];
        if (isdigit(ch)) {
            push(ch - '0');  // Convert char digit to int and push
        } else {
            b = pop();
            a = pop();
            switch (ch) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                default:
                    printf("Invalid operator %c\n", ch);
                    exit(EXIT_FAILURE);
            }
            push(result);
        }
    }

    printf("The evaluated result is: %d\n", pop());
    return 0;
}
