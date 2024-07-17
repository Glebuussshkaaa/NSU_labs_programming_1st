#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_SIZE 1000
#define ERROR_HANDLER 1500

enum Operations {
    DIVISION = 47,
    MULTIPLICATION = 42,
    ADDITION = 43,
    SUBTRACTION = 45,
};

enum Type {
    NUM = 0,
    BRACKET = 1,
    ADD_SUB = 2,
    MULT_DIV = 3,
};

struct List {
    int type;
    int value;
    struct List* next;
};

void PushFromStack(struct List** stack, int type, int value);
int PopValueFromStack(struct List** stack);
void DestroyStack(struct List* stack);

int GetPriority(char symbol);
int Calculate(char* infix, int length);
int ConvertToPostfix(const char* infix, const int length, int* postfix);


int main(void) {
    char string[MAX_ARRAY_SIZE + 2];

    if (fgets(string, sizeof(string), stdin) == NULL) {
        return 0;
    }

    int result = Calculate(string, (int)strlen(string) - 1);
    if (result == ERROR_HANDLER) {
        return 0;
    }
    printf("%d", result);

    return 0;
}

void PushFromStack(struct List** stack, int type, int value) {
    struct List* elem = (struct List*)malloc(sizeof(struct List));
    elem->type = type;
    elem->value = value;
    elem->next = *stack;
    *stack = elem;
}

int PopValueFromStack(struct List** stack) {
    if (*stack == NULL) {
        return 0;
    }
    struct List* tmp = *stack;
    *stack = tmp->next;
    int value = tmp->value;
    free(tmp);
    return value;
}

void DestroyStack(struct List* stack) {
    while (stack != NULL) {
        struct List* tmp = stack;
        stack = stack->next;
        free(tmp);
    }
}

int GetPriority(char symbol) {
    switch (symbol) {
        case '*':
        case '/':
            return MULT_DIV;
        case '-':
        case '+':
            return ADD_SUB;
        case '(':
            return BRACKET;
        default:
            return NUM;
    }
}

int ConvertToPostfix(const char* infix, const int length, int* postfix) {
    struct List* operatorStack = NULL;
    int bracketsOpening = 0;
    int bracketsClosing = 0;
    int flagNumber = 0;
    int postfixLength = 0;

    for (int i = 0; i < length; i++) {
        char currentChar = infix[i];
        if (currentChar >= '0' && currentChar <= '9') {
            int currentNumber  = 0;
            while (infix[i] >= '0' && infix[i] <= '9') {
                currentNumber = currentNumber * 10 + infix[i++] - '0';
            }
            i--;
            postfix[postfixLength++] = currentNumber;
            flagNumber = 1;
        } else if (currentChar == '(') {
            PushFromStack(&operatorStack, BRACKET, currentChar);
            bracketsOpening++;
        } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            if ((i > 0 && (infix[i - 1] == '+' || infix[i - 1] == '-' || infix[i - 1] == '*' || infix[i - 1] == '/')) || i == length - 1) {
                printf("syntax error");
                DestroyStack(operatorStack);
                return ERROR_HANDLER;
            }
            while (operatorStack != NULL && operatorStack->type != BRACKET && operatorStack->type >= GetPriority(currentChar)) {
                postfix[postfixLength++] = PopValueFromStack(&operatorStack);
            }
            if (currentChar == '+' || currentChar == '-') {
                PushFromStack(&operatorStack, ADD_SUB, currentChar);
            } else {
                PushFromStack(&operatorStack, MULT_DIV, currentChar);
            }
        } else if (currentChar == ')') {
            while (operatorStack != NULL && operatorStack->value != '(') {
                postfix[postfixLength++] = PopValueFromStack(&operatorStack);
            }
            if ((i > 0 && infix[i - 1] == '(') || operatorStack == NULL) {
                printf("syntax error");
                DestroyStack(operatorStack);
                return ERROR_HANDLER;
            }
            PopValueFromStack(&operatorStack);
            bracketsClosing++;
        }
    }

    if (!flagNumber) {
        printf("syntax error");
        DestroyStack(operatorStack);
        return ERROR_HANDLER;
    } else {
        if (operatorStack == NULL && (bracketsOpening != bracketsClosing)) {
            printf("syntax error");
            DestroyStack(operatorStack);
            return ERROR_HANDLER;
        } else if (operatorStack == NULL && (bracketsOpening == bracketsClosing)) {
            postfix[postfixLength] = '\0';
            return postfixLength;
        } else {
            while (operatorStack != NULL) {
                postfix[postfixLength++] = PopValueFromStack(&operatorStack);
            }
        }
    }
    DestroyStack(operatorStack);
    postfix[postfixLength] = '\0';
    return postfixLength;
}

int Calculate(char* infix, int length) {
    int postfix[MAX_ARRAY_SIZE];
    int postfixLength = ConvertToPostfix(infix, length, postfix);
    if (postfixLength == ERROR_HANDLER) {
        return ERROR_HANDLER;
    }
    struct List* valueStack = NULL;
    for (int i = 0; i < postfixLength; i++) {
        if (postfix[i] != ADDITION && postfix[i] != DIVISION && postfix[i] != SUBTRACTION && postfix[i] != MULTIPLICATION) {
            PushFromStack(&valueStack, NUM, postfix[i]);
        } else {
            int operand2 = valueStack->value;
            PopValueFromStack(&valueStack);
            int operand1 = valueStack->value;
            PopValueFromStack(&valueStack);

            switch (postfix[i]) {
                case ADDITION:
                    PushFromStack(&valueStack, NUM, operand1 + operand2);
                    break;
                case SUBTRACTION:
                    PushFromStack(&valueStack, NUM, operand1 - operand2);
                    break;
                case MULTIPLICATION:
                    PushFromStack(&valueStack, NUM, operand1 * operand2);
                    break;
                case DIVISION:
                    if (operand2 == 0) {
                        printf("division by zero\n");
                        DestroyStack(valueStack);
                        return ERROR_HANDLER;
                    }
                    PushFromStack(&valueStack, NUM, operand1 / operand2);
                    break;
                default:
                    printf("syntax error\n");
                    DestroyStack(valueStack);
                    return ERROR_HANDLER;
            }
        }
    }
    if (valueStack != NULL) {
        int finalResult = valueStack->value;
        if (valueStack->next == NULL) {
            DestroyStack(valueStack);
            return finalResult;
        } else {
            DestroyStack(valueStack);
            printf("syntax error\n");
            return ERROR_HANDLER;
        }
    } else {
        DestroyStack(valueStack);
        printf("syntax error\n");
        return ERROR_HANDLER;
    }
}


