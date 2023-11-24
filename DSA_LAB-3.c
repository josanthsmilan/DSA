#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Define the stack structure
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Function to create a stack
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$'; // '$' is used to indicate an empty stack
}

// Function to return the top element of the stack without popping
char peek(struct Stack* stack) {
    return stack->array[stack->top];
}

// Function to check if a character is an operand
int isOperand(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// Function to get the precedence of an operator
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char* infix) {
    struct Stack* stack = createStack(strlen(infix));
    int i, k;

    for (i = 0, k = -1; infix[i]; ++i) {
        // If the scanned character is an operand, add it to the output
        if (isOperand(infix[i]))
            infix[++k] = infix[i];

        // If the scanned character is an '(', push it onto the stack
        else if (infix[i] == '(')
            push(stack, infix[i]);

        // If the scanned character is an ')', pop and output from the stack until an '(' is encountered
        else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                infix[++k] = pop(stack);
            if (!isEmpty(stack))
                pop(stack); // Pop '(' from the stack
            else {
                printf("Error: Unmatched closing parenthesis.\n");
                return; // Exit the function on error
            }
        }

        // If an operator is encountered
        else {
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack)))
                infix[++k] = pop(stack);
            push(stack, infix[i]);
        }
    }

    // Pop all the remaining operators from the stack
    while (!isEmpty(stack))
        infix[++k] = pop(stack);

    infix[++k] = '\0';
    printf("Postfix Expression: %s\n", infix);

    // Free the dynamically allocated memory for the stack
    free(stack->array);
    free(stack);
}

// Function to validate balanced parentheses in an infix expression
int isValidExpression(char* infix) {
    struct Stack* stack = createStack(strlen(infix));

    for (int i = 0; infix[i]; ++i) {
        if (infix[i] == '(') {
            push(stack, infix[i]);
        } else if (infix[i] == ')') {
            if (isEmpty(stack)) {
                // Unmatched closing parenthesis
                free(stack->array);
                free(stack);
                return 0;
            }
            pop(stack);
        }
    }

    int isValid = isEmpty(stack);  // Stack should be empty for a valid expression

    // Free the dynamically allocated memory for the stack
    free(stack->array);
    free(stack);

    return isValid;
}

int main() {
    char infix[MAX_SIZE];
    int choice;

    while (1) {
        // Menu
        printf("\nMenu:\n");
        printf("1. Enter the infix expression\n");
        printf("2. Display infix as postfix\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Input infix expression
                printf("Enter the infix expression: ");
                scanf("%s", infix);

                // Validate balanced parentheses
                if (!isValidExpression(infix)) {
                    printf("Error: Unmatched parentheses in the expression.\n");
                } else {
                    printf("Expression entered successfully: %s\n", infix);
                }
                break;

            case 2:
                // Convert infix to postfix if an expression is entered
                if (strlen(infix) > 0) {
                    infixToPostfix(infix);
                } else {
                    printf("Error: No infix expression entered yet.\n");
                }
                break;

            case 3:
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}