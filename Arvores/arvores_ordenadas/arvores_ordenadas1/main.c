#include "stdlib.h"
#include "stdio.h"
#include "arvore.h"



void imprime_tab (No* no, char * lado)
{
   static int tab = 0;

   if (no==NULL) return;

   int x;
   for(x=0;x<tab;x++)
       printf("   ");
   printf("%d (%s)\n", arv_busca_valor(no), lado);

   tab+=1;
   imprime_tab(arv_busca_filho(no,0), "ESQ");
   imprime_tab(arv_busca_filho(no,1), "DIR");
   tab-=1;
}

// Implemente uma função no main que imprima os valores
// da árvore em ordem ascendente de valor
void imprime_asc(No *no) 
{
    if (no == NULL) return;
    imprime_asc(arv_busca_filho(no, 0)); // imprime o filho esquerdo
    printf("%d ", arv_busca_valor(no)); // nó atual
    imprime_asc(arv_busca_filho(no, 1)); // imprime ofilho direito
}

// • 2) Implemente uma função no main que imprima os valores
// da árvore em ordem descendente valor
void imprime_desc(No *no) 
{
    if (no == NULL) return;
    imprime_desc(arv_busca_filho(no, 1)); // imprime o direito
    printf("%d ", arv_busca_valor(no)); // nó atual
    imprime_desc(arv_busca_filho(no, 0)); // filho esquerdo
}

// • 3) Implemente uma função no main que retorne a diferença
// entre o maior e o menor valor armazenados na árvore
// • Caso a árvore não possua filhos o resultado deve ser -1
// • O protótipo da função deve ser:
// • int calcula_diferenca (No * no);
int calcula_diferenca(No *no) {
    if (no == NULL) return -1; // árvore vazia
    if(arv_no_vazio(no)) return -1; // se só tem o nó raiz

    No *atual = no; // árvore que é o atual na iteração

    // encontra o menor valor que é o nó mais à esquerda
    while (arv_busca_filho(atual, 0) != NULL) {
        atual = arv_busca_filho(atual, 0);
    }

    int menor = arv_busca_valor(atual);

    atual = no;

    // encontrar o maior valor que é o nó mais à direita
    while (arv_busca_filho(atual, 1) != NULL) {
        atual = arv_busca_filho(atual, 1);
    }

    int maior = arv_busca_valor(atual);

    return maior - menor;
}


int main()
{
   Arvore * arv = arv_cria();

   arv_insere_no(arv, 10);
   arv_insere_no(arv, 50);
   arv_insere_no(arv, 40);
   arv_insere_no(arv, 20);
   arv_insere_no(arv, 60);

   printf("\n Impressao \n");
   imprime_tab(arv_busca_raiz(arv), "RAIZ");

   printf("\n");
   int valor = 50;
   No * resp = arv_busca_no(arv_busca_raiz(arv), valor);
   if (resp!=NULL)
        printf("No encontrado: %d", valor);
    else printf("No nao encontrado: %d ", valor);


   printf("\n");
   int diff = calcula_diferenca(arv_busca_raiz(arv));
   if (diff!=-1)
        printf("\nDiferenca do maior para o menor e de %d unidades", diff);

   printf("\n\n lista ascendente de valores:");
   imprime_asc(arv_busca_raiz(arv));

   printf("\n\n lista descendente de valores:");
   imprime_desc(arv_busca_raiz(arv));

   return 0;
}
