/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-2                                 */
/*             Objetivo: << Manipulacao de Array com ponteiro >>                    */
/*                                                                                  */
/*                                  Autor: Nuno Kasuo Tronco Yokoji                 */
/*                                                                  Data:12/03/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Candidate {
    char name[50];
    float PE[4];
    float AC[5];
    float PP[10];
    float EB[3];
    float NF;
    struct Candidate *next; 
};

float average(float *ptrGrades, int size) { 
    float sum = 0, highest = ptrGrades[0], lowest = ptrGrades[0];
    int i;
    
    for (i = 0; i < size; i++) {
        sum += ptrGrades[i];
        if (ptrGrades[i] > highest) highest = ptrGrades[i];
        if (ptrGrades[i] < lowest) lowest = ptrGrades[i];
    }

    return (sum - highest - lowest); 
}

void insertCandidate(struct Candidate **start, char name[], float PE[], float AC[], float PP[], float EB[]) {
    struct Candidate *newCandidate = (struct Candidate*)malloc(sizeof(struct Candidate));
    
    if (newCandidate == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    strcpy(newCandidate->name, name);
    memcpy(newCandidate->PE, PE, 4 * sizeof(float));
    memcpy(newCandidate->AC, AC, 5 * sizeof(float));
    memcpy(newCandidate->PP, PP, 10 * sizeof(float));
    memcpy(newCandidate->EB, EB, 3 * sizeof(float));

    float avg_PE = average(PE, 4); 
    float avg_AC = average(AC, 5);  
    float avg_PP = average(PP, 10); 
    float avg_EB = average(EB, 3);  

    newCandidate->NF = (avg_PE * 0.3f) + (avg_AC * 0.1f) + (avg_PP * 0.4f) + (avg_EB * 0.2f);
    
    newCandidate->next = *start;
    *start = newCandidate;
}

void rank(struct Candidate **start) {
    struct Candidate *i, *j;
    float tempNF;
    char tempName[50];

    for (i = *start; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->NF < j->NF) {
                tempNF = i->NF;
                i->NF = j->NF;
                j->NF = tempNF;

                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);
            }
        }
    }
}

void showRank(struct Candidate *start) {
    struct Candidate *ptr = start;
    printf("Classificação dos melhores candidatos: \n");
    for (int i = 0; i < 5 && ptr != NULL; i++) {
        printf("%dº %s - Nota Final: %.2f \n", i + 1, ptr->name, ptr->NF);
        ptr = ptr->next;
    }
}

void showTitle() {
    printf("*-------------------------------------------------------------------------------------*\n");
    printf("* Bem-vindo ao sistema de classificação para o processo seletivo de residência médica *\n");
    printf("*-------------------------------------------------------------------------------------*\n");
}

int main() {
    struct Candidate *start = NULL;

    int numOfCandidates = 0;
    int proceed = 1;  
    
    showTitle();
    
    while (proceed == 1) {
        char name[50];
        float PE[4], AC[5], PP[10], EB[3];
        
        printf("Você deseja adicionar mais um candidato?\n");
        printf("0 - NÃO\n");
        printf("1 - SIM\n");
        scanf("%d", &proceed);
        
        if(proceed == 0) break;
        
        printf("Você já cadastrou %i candidato(os) \n", numOfCandidates);
        printf("Digite o nome do candidato: ");
        scanf("%s", name);

        printf("Digite as 4 notas para Prova Escrita(PE):\n");
        for (int qtde = 0; qtde < 4; qtde++) {
            scanf("%f", &PE[qtde]);
        }

        printf("Digite as 5 notas para Análise Curricular(AC):\n");
        for (int qtde = 0; qtde < 5; qtde++) {
            scanf("%f", &AC[qtde]);
        }

        printf("Digite as 10 notas para Prova Prática(PP):\n");
        for (int qtde = 0; qtde < 10; qtde++) {
            scanf("%f", &PP[qtde]);
        }

        printf("Digite as 3 notas para Entrevista em Banca(EB):\n");
        for (int qtde = 0; qtde < 3; qtde++) {
            scanf("%f", &EB[qtde]);
        }

        insertCandidate(&start, name, PE, AC, PP, EB);
        numOfCandidates++;

        if (numOfCandidates >= 50) {
            printf("Limite de 50 candidatos atingido. \n");
            break;
        }
    }

    rank(&start);
    showRank(start);

    return 0;
}