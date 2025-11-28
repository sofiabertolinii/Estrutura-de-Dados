#include "stdlib.h"
#include "stdio.h"
#include "arvore.h"

// • 1) Implemente uma função no main que descubra se uma árvore
// é AVL
// • Ou seja, se não existe duas sub-árvores cuja diferença de altura é superior
// a 1
// • O protótipo da função deve ser:
// • int balanceada (No * no)
// • Uma função para calcular a altura de uma sub-árvore pode ajudar:
// • int calcula_altura (No * no);
int calcula_altura(No *no) {
    if (no == NULL) {
        return 0;
    }

    int altura_esq = calcula_altura(arv_busca_filho(no, 0));
    int altura_dir = calcula_altura(arv_busca_filho(no, 1));

    // +1 para contar o nó atual
    if(altura_esq > altura_dir) {
        return altura_esq + 1;
    } else {
        return altura_dir + 1;
    }
}

int balanceada(No *no) {
    if (no == NULL) {
        return 1; // árvore vazia é balanceada
    }

    // calcula a altura dos filhos 
    int altura_esq = calcula_altura(arv_busca_filho(no, 0));
    int altura_dir = calcula_altura(arv_busca_filho(no, 1));

    // verifica a diferença de altura
    if(altura_dir - altura_esq > 1 || altura_esq - altura_dir > 1) {
        return 0; // não está balanceada
    }

    // verifica os filhos da esquerda e da direita
    return balanceada(arv_busca_filho(no, 0)) && balanceada(arv_busca_filho(no, 1));
}

// • 2) Implemente uma função no main que gere um vetor contendo
// todos os valores de uma árvore que sejam superiores a um valor
// passado por parâmetro
// • O protótipo da função deve ser:
// • int gera_vetor_maiores (No * no, int v, int ** vetor);
// • Uma função para calcular o tamanho do array pode ajudar:
// • int quant_maiores (No * no, int v);

int quant_maiores(No *no, int v) {
    if (no == NULL) {
        return 0;
    }

    int count = 0;
    // se for maior, conta esse nó
    if (arv_busca_valor(no) > v) {
        count = 1;
    }

    // conta os maiores nos filhos
    count += quant_maiores(arv_busca_filho(no, 0), v);
    count += quant_maiores(arv_busca_filho(no, 1), v);

    return count;
}

int gera_vetor_maiores(No *no, int v, int **vetor) {
    int tamanho = quant_maiores(no, v);
    *vetor = malloc(tamanho * sizeof(int));
    if (*vetor == NULL) {
        return 0; // falha na alocação
    }

    int index = 0;

    for (int i = 0; i < tamanho; i++) {
        if (arv_busca_valor(no) > v) {
            (*vetor)[index] = arv_busca_valor(no);
            index++;
        }
        no = arv_busca_filho(no, 1);
    }

    return tamanho;
}

void imprime_asc(No * no){
    if (no==NULL)
        return;

    imprime_asc(arv_busca_filho(no,0));
    printf("%d, ",arv_busca_valor(no) );
    imprime_asc(arv_busca_filho(no,1));

}





int main()
{

   printf("\n\n******************* TESTE 1 ******************************");
   Arvore * arv = arv_cria();

   arv_insere_no(arv, 1);
   arv_insere_no(arv, 2);
   arv_insere_no(arv, 3);
   arv_insere_no(arv, 4);
   arv_insere_no(arv, 5);
   arv_insere_no(arv, 6);
   arv_insere_no(arv, 7);

   printf("\n");
   int bal = balanceada(arv_busca_raiz(arv));
   if (bal)
        printf("\nBalanceada");
    else printf("\nNao Balanceada");


   printf("\n\n******************* TESTE 2 ******************************");
   Arvore * arv1 = arv_cria();

   arv_insere_no(arv1, 4);
   arv_insere_no(arv1, 6);
   arv_insere_no(arv1, 2);
   arv_insere_no(arv1, 5);
   arv_insere_no(arv1, 1);
   arv_insere_no(arv1, 7);
   arv_insere_no(arv1, 3);

   printf("\n");
    bal = balanceada(arv_busca_raiz(arv1));
   if (bal)
        printf("\nBalanceada");
    else printf("\nNao Balanceada");


   int * vetor;
   int tam = gera_vetor_maiores(arv_busca_raiz(arv1), 3, &vetor);

   printf("\n\nvetor gerado: ");
   int x;
   for(x=0;x<tam;x++){
       printf("%d ", vetor[x]);
   }
   printf("\n");


   return 0;
}
