/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         ID da Atividade: S1-B1-4                                 */
/*             Objetivo: <<  Manipulação de pilhas - Implementação da HP12C >>      */
/*                                                                                  */
/*                                  Autor: Nuno Kasuo Tronco Yokoji                 */
/*                                                                  Data: 01/04/2025*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 4  

typedef struct {
    double data[MAX_SIZE];
    char expr[MAX_SIZE][50];
    int top;
} Stack;

Stack* create_stack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = -1;
    return s;
}

int is_empty(Stack* s) {
    return s->top == -1;
}

int is_full(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack* s, double value, const char* expr) {
    if (is_full(s)) { 
        printf("Erro: Pilha cheia! Não é possível adicionar mais elementos.\n");
        return;
    }

    s->top++;
    s->data[s->top] = value;
    strcpy(s->expr[s->top], expr);
}

double pop(Stack* s, char* expr) {
    if (is_empty(s)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    strcpy(expr, s->expr[s->top]);
    return s->data[s->top--];
}

double top(Stack* s, char* expr) {
    if (is_empty(s)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    strcpy(expr, s->expr[s->top]);
    return s->data[s->top];
}

int is_number(const char* token) {
    char* endptr;
    strtod(token, &endptr);
    return *endptr == '\0';
}

void calculate_RPN(char* expression) {
    Stack* stack = create_stack();
    char* token = strtok(expression, " ");
    
    while (token != NULL) {
        if (is_number(token)) {
            double num = atof(token);
            char temp[20];
            sprintf(temp, "%.2f", num);
            push(stack, num, temp);
        } else {
            if (stack->top < 1) {
                printf("Erro: Expressão inválida!\n");
                free(stack);  
                return;
            }
            char exprA[50], exprB[50];
            double b = pop(stack, exprB);
            double a = pop(stack, exprA);
            double result;
            char operator = token[0];
            char newExpr[150];
            
            switch (operator) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("Erro: Divisão por zero!\n");
                        free(stack); 
                        return;
                    }
                    result = a / b;
                    break;
                default:
                    printf("Erro: Operador inválido!\n");
                    free(stack); 
                    return;
            }
            
            snprintf(newExpr, sizeof(newExpr), "(%s %c %s)", exprA, operator, exprB);
            push(stack, result, newExpr);
        }
        token = strtok(NULL, " ");
    }
    
    if (stack->top != 0) {
        printf("Erro: Expressão inválida!\n");
        free(stack);  
        return;
    }
    
    char resultExpr[100];
    double finalResult = pop(stack, resultExpr);
    printf("\nResultado: %s = %.2f\n", resultExpr , finalResult);
    printf("\n================================================================");
    free(stack);  
}

void menu() {
    int option;
    char expression[MAX_SIZE * 20];
    Stack* stack = NULL;  

    do {
        printf("================================================================");
        printf("\nMENU:\n");
        printf("1 - Inserir expressão RPN\n");
        printf("2 - Sair\n");
        printf("Escolha uma opção:\n");
        scanf("%d", &option);
        getchar();  
        
        switch (option) {
            case 1:
                if (stack == NULL) {
                    stack = create_stack();  
                }
                printf("Digite a expressão RPN (Ex.: a b + c /):\n");
                fgets(expression, sizeof(expression), stdin);
                expression[strcspn(expression, "\n")] = 0; 
                calculate_RPN(expression);  
                break;
            case 2:
                printf("Sistema finalizado.\n");
                if (stack != NULL) {
                    free(stack);  
                }
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (option != 2);  
}

int main() {
    menu();
    return 0;
}
