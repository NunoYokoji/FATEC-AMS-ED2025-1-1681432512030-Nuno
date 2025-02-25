#include <stdio.h>

float Discount(float *ptrOriginal, float *ptrFinal, float *ptrDiscount, int *ptrDisChoice) {
    
    switch(*ptrDisChoice) {
        case 0:
            *ptrFinal = *ptrOriginal - ((*ptrOriginal * *ptrDiscount) / 100);
            return *ptrFinal;
            break;
            
        case 1:
            *ptrFinal = *ptrOriginal - *ptrDiscount;
            return *ptrFinal;
            break;
        
        default:
            return *ptrFinal = -1;
            break;
    }
    
}

int main() {
    
    float originalPrice, discount, finalPrice;
    int disChoice;
    
    printf("Digite o valor do produto: ");
    scanf("%f", &originalPrice);
    
    printf("Informe a maneira a qual o desconto será aplicado:\n");
    printf("0 - Desconto em porcentagem %%\n");
    printf("1 - Desconto em valor R$\n");
    scanf("%d", &disChoice);
    
    printf("Informe o desconto: ");
    scanf("%f", &discount);
    
    Discount(&originalPrice, &finalPrice, &discount, &disChoice);
    
    if(finalPrice >= 0) {
        printf("O valor original do produto é R$%.2f\n", originalPrice);
        
        if(disChoice == 0) {
            printf("A porcentagem do desconto aplicado é de %.2f%%\n", discount);
            
        } else {
            printf("O valor do desconto aplicado foi de R$%.2f\n", discount);
        }
        
        printf("O valor final da compra com o desconto é de R$%.2f\n", finalPrice);
        
    } else {
        printf("Algo deu errado, insira informações válidas e pertinentes\n");
    }

    return 0;
}