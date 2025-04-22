/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-5                                 */
/*             Objetivo: << Transformar Lista Ligada em Pilha >>                    */
/*                                                                                  */
/*                                  Autor: Nuno Kasuo Tronco Yokoji                 */
/*                                                                  Data:01/04/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4

typedef struct {
    int orderNumber;
    char customerName[30];
    char description[50];
    int quantity;
    char status[20];
} Order;

typedef struct {
    Order data[MAX];
    int top;
} Stack;

char statusTypes[4][20] = {"Pendente", "Em Preparo", "Pronto", "Entregue"};

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX - 1;
}

void pushOrder(Stack* stack) {
    if (isFull(stack)) {
        printf("Aviso: A pilha atingiu sua capacidade máxima. Não é possível adicionar mais pedidos.\n");
        return;
    }

    Order newOrder;
    printf("Digite o número do pedido: ");
    scanf("%d", &newOrder.orderNumber);
    printf("Informe o nome do cliente: ");
    scanf("%s", newOrder.customerName);
    printf("Descreva o pedido: ");
    scanf("%s", newOrder.description);
    printf("Informe a quantidade desejada: ");
    scanf("%d", &newOrder.quantity);
    strcpy(newOrder.status, statusTypes[0]);

    stack->top++;
    stack->data[stack->top] = newOrder;
}

void popOrder(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Aviso: Nenhum pedido disponível para remoção.\n");
        return;
    }

    Order order = stack->data[stack->top];
    stack->top--;
    printf("Pedido removido da pilha: %d - %s - %s\n", order.orderNumber, order.customerName, order.status);
}

void updateOrderStatus(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Aviso: Não há pedidos para atualizar.\n");
        return;
    }

    Order* order = &stack->data[stack->top];
    for (int i = 0; i < 3; i++) {
        if (strcmp(order->status, statusTypes[i]) == 0) {
            strcpy(order->status, statusTypes[i + 1]);
            printf("Status do pedido alterado para: %s\n", order->status);
            if (strcmp(order->status, "Entregue") == 0) {
                popOrder(stack);
            }
            return;
        }
    }
}

void showCurrentOrder(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Aviso: Nenhum pedido foi encontrado no topo da pilha.\n");
        return;
    }

    Order order = stack->data[stack->top];
    printf("\nDetalhes do pedido atual:\nNúmero: %d\nCliente: %s\nDescrição: %s\nQuantidade: %d\nStatus: %s\n", 
           order.orderNumber, order.customerName, order.description, order.quantity, order.status);
}

void opt() {
    printf("\n\nSistema de Pedidos - Restaurante (Pilha)\n");
        printf("1 - Cadastrar novo pedido\n");
        printf("2 - Visualizar pedido atual\n");
        printf("3 - Atualizar status do pedido\n");
        printf("0 - Encerrar o sistema\n");
        printf("Escolha uma opção: ");
}

int menu(int option, Stack* stack) {
    do {
        opt();
        scanf("%d", &option);

        switch (option) {
            case 0:
                free(stack);
                return 0;
            case 1:
                pushOrder(stack);
                break;
            case 2:
                showCurrentOrder(stack);
                break;
            case 3:
                updateOrderStatus(stack);
                break;
            default:
                printf("\nOpção não reconhecida. Tente novamente.\n");
        } 
    } while (option = 1);
}

int main() {
    Stack* stack = createStack();
    int option;
    menu(option, stack);
}