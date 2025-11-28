#include <stdio.h>
#include <stdlib.h>

// ALUNA SOFIA BERTOLINI LOPES
// Disciplina de Estrutura de dados

// escreva um programa que transforme um vetor de inteiros em um vetor de caracteres de modo que:
// valores maiores do que zero sejam transformados em '+'
// valores menores do que zero sejam transformados em '-'
// valores iguais a zero sejam transformados em '0'

// a transformação deve ser encapsulada em uma função
// função cria1 deve resolver usando alocação dinâmica
// função cria 2 deve resolver usando alocação estática


// versão com alocação dinâmica
// versão com alocação dinâmica
char *cria1(int v[], int n) {
    char *vetor_final = (char *) malloc(n * sizeof(char)); // aloca dinamicamente o vetor de caracteres
    if (vetor_final == NULL) {
        printf("Erro ao alocar memoria.\n");
        return NULL;
    }
    
    // passando os valores do vetor de inteiros para o vetor de caracteres 

    for (int i = 0; i < n; i++) {
        if (v[i] > 0) {
            vetor_final[i] = '+'; // valores maiores que zero recebem +
        } else if (v[i] < 0) {
            vetor_final[i] = '-'; // valores menores que zero recebem -
        } else {
            vetor_final[i] = '0'; // valores iguais a zero recebem 0
        }
    }
    return vetor_final; // retorna o ponteiro para o vetor de caracteres (endereço inicial do vetor)
}

void cria2(int v[], int n, char *vetor_final) {
    // passando os valores do vetor de inteiros para o vetor de caracteres
    for (int i = 0; i < n; i++) {
        if (v[i] > 0) {
            vetor_final[i] = '+'; // valores maiores que zero recebem +
        } else if (v[i] < 0) {
            vetor_final[i] = '-'; // valores menores que zero recebem -
        } else {
            vetor_final[i] = '0'; // valores iguais a zero recebem 0
        }
    }
}       

int main(){
   int v[] = {2,-5,0,-6,1};

   char *v1; // ponteiro para o vetor de caracteres (alocação dinamica)
   //use a função cria1 para preencher o vetor v1

   v1 = cria1 (v, 5);
   int i;
    for (i=0; i<5; i++)
       printf("%c ",v1[i]);

    printf("\n");


   char v2[5];
   //use a função cria2 para preencher o vetor v2
   cria2 (v, 5, v2);

   for (i=0; i<5; i++)
      printf("%c ",v2[i]);

      
}
