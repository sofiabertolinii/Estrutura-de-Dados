#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"


/*composi��o de um no*/
struct no{
   int info;
   struct no* esq;
   struct no* dir;
};

/*composi��o de uma arvore*/
struct arvore{
    No * raiz;
};


/* fun��o de cria��o */
Arvore * arv_cria ()
{
    Arvore * arv = (Arvore *) malloc(sizeof(Arvore));
    arv->raiz = NULL;
    return arv;
}



/* fun��o de cria��o */
No * arv_cria_no (int v)
{
    No * no = (No *) malloc(sizeof(No));
    no->info = v;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}


/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
int arv_vazia (Arvore * arvore)
{
   return (arvore->raiz == NULL);
}


/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
int arv_no_vazio (No * no)
{
   //supondo que no n�o seja nulo
   return (no->esq==NULL && no->dir == NULL);
}


/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
No * arv_busca_raiz (Arvore * arvore)
{
   return (arvore->raiz);
}



/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
void arv_seta_raiz (Arvore * arvore, No * raiz)
{
   arvore->raiz = raiz;
}


/* inser��o de um no filho abaixo de um no pai */
void arv_insere (No* pai, No* filho, int dir)
{
   if (dir)
       pai->dir = filho;
   else
      pai->esq = filho;
}


void arv_imprime (No* pai)
{
   if (pai==NULL)
        return;

   printf("\n%d", pai->info);
   arv_imprime(pai->esq);
   arv_imprime(pai->dir);

}

// • 1) Implemente uma função no TAD que imprima os valores
// da árvore seguindo a ordem hierárquica
// • O protótipo da função deve ser:
// • void arv_imprime_tab (No* pai, char * lado);

// --- 30 (raiz)
// ------ 20 (esq)
// --------- 10 (esq)
// ------ 15(dir)
// --------- 25(esq)
// --------- 40(dir)

void arv_imprime_tab (No *pai, char *lado) {
   static int no = 0; // vai guardar a altura em que o nó está

   if(pai == NULL) return; // retorna se tiver chegado no final

   for(int i = 0; i < no; i++) {
      printf("-----"); // printa os tracinhos
   }

   printf("%d\n", pai->info);

   no++;
   arv_imprime_tab(pai->esq, "esq");
   arv_imprime_tab(pai->dir, "dir");
   no--;
   
}


// AUXILIARES DA FUNÇÃO 2
No* arv_busca_filho (No * no, int dir) {
   if(no == NULL) return;

   if(dir) {
      return no->dir;
   } else {
      return no->esq;
   }
}

int arv_busca_valor (No * no) {
   return no->info;
}

// 3) Implemente uma nova função de inserção no TAD.
// • Essa função só insere um filho se a posição estiver vazia.
// • Caso contrário, deve-se procurar alguma posição vazia a partir
// daquela onde se desejava fazer a inserção

void arv_insere_final (No* pai, No* filho, int dir) {
   if(pai == NULL) return; // se o pai for nulo ja retorna

   if(!dir) { // se for esquerda
      if(pai->esq == NULL) { // se for nulo
         arv_insere(pai->esq, filho, 0); // insere

      } else {
         arv_insere_final(pai->esq, filho, 0); // se não for nulo chama pro filho da esquerda
      }
   
   } else { // se for direita
      if(pai->dir == NULL) { // se for nulo
         arv_insere(pai->dir, filho, 1); // insere

      } else {
         arv_insere_final(pai->dir, filho, 1); // se não for nulo chama pro filho da direita
      }
   }
}
