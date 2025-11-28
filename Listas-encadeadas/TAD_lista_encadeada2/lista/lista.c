#include <stdlib.h>
#include <stdio.h>

#include "lista.h"

static No * lst_localiza_ultimo_menor(No * inicio, int v);
static No * lst_localiza_ultimo(No * inicio, int v);
static void insere_lista(No** inicio, int v, No * ant);

struct no{
   int info;
   struct no* prox;
};


/* fun��o de cria��o */
void lst_cria (No ** inicio)
{
    *inicio = NULL;
}

void lst_libera (No** inicio)
{
   No* p = *inicio;
   while (p != NULL) {
      No* t = p->prox;
      free(p);
      p = t;
   }
 *inicio = NULL;
}


/* retorna 1 se vazia ou 0 se n�o vazia */
int lst_vazia (No* inicio)
{
   return (inicio == NULL);
}




/* inser��o no in�cio */
void lst_insere_comeco (No** inicio, int i)
{
   No* novo = (No*) malloc(sizeof (No));
   novo->info = i;
   novo->prox = *inicio;
   *inicio = novo;
}

void lst_insere_ordenado (No** inicio, int v)
{
   No* ant = lst_localiza_ultimo_menor(*inicio, v);	/* ponteiro para elemento anterior	*/
   insere_lista(inicio, v, ant);
}

void lst_insere_final (No** inicio, int v)
{
   No* ant = lst_localiza_ultimo(*inicio, v);	/* ponteiro para o �ltimo elemento	*/
   insere_lista(inicio, v, ant);
}

void lst_retira (No** inicio, int v)
{
   No* ant = NULL;
   No* p = *inicio;

   while (p != NULL && p->info != v){
      ant = p;
      p = p->prox;
   }

 if (p == NULL)   return;

   if (ant == NULL)
      *inicio = p->prox;
   else
      ant->prox = p->prox;

   free(p);
}

No* lst_busca (No* inicio, int v)
{
   No* p = inicio;
   while (p!=NULL)
   {
        if (p->info ==  v)
            return  p;
        p = p->prox;
   }
return NULL;
}


void lst_imprime (No* inicio)
{
   No* p = inicio;
   while (p != NULL) {
      printf("info = %d\n", p->info);
      p = p->prox;
   }
}

static void insere_lista(No** inicio, int v, No * ant)
{
    /* cria novo elemento */
   No* novo = (No*) malloc(sizeof (No));
   novo->info = v;
   /* encadeia elemento */
   if (ant == NULL){         /* insere elemento no in�cio	*/
      novo->prox = *inicio;
      *inicio = novo;
   }
   else {                           /* insere elemento no meio da lista */
      novo->prox = ant->prox;
      ant->prox = novo;
   }

}



static No * lst_localiza_ultimo_menor(No * inicio, int v){
   No* p = inicio;	/* ponteiro para percorrer a lista	*/
   No* ant = NULL;	/* ponteiro para elemento anterior	*/
   /* procura posi��o de inser��o */
   while (p != NULL && p->info < v){
      ant = p;
      p = p->prox;
   }
   return ant;

}

static No * lst_localiza_ultimo(No * inicio, int v){
   No* p = inicio;	/* ponteiro para percorrer a lista	*/
   No* ant = NULL;	/* ponteiro para elemento anterior	*/
   /* procura posi��o de inser��o */
   while (p != NULL){
      ant = p;
      p = p->prox;
   }
   return ant;

}

// • O código implementa um TAD para lista encadeada com
// diversas funções, como por exemplo
// • Remoção de elemento que possua um valor definido
// • Busca de elemento que possua um valor definido
// • Atualize esse código para implementar o que se pede nos
// próximos slides
// • Teste cada uma das funções implementadas no main.c
// Atividade Individual
// • 1) Implemente uma função no TAD que remova o elemento do
// começo da lista
// • O protótipo da função deve ser:
// • void lst_retira_comeco (No** inicio);
void lst_retira_comeco (No **inicio) {
   if(*inicio == NULL) {
      return; // retorna pq ta vazio
   }

   No *temp =  *inicio; // cria uma variavel temporaria que guarda o inicio
   *inicio = (*inicio)->prox; // o inicio recebe o que vem depois dele (que agora é o primeiro)
   free(temp); // libera o primeiro
}

// • 2) Implemente uma função no TAD que remova o elemento do
// final da lista
// • O protótipo da função deve ser:
// • void lst_retira_final (No** inicio);
void lst_retira_final (No **inicio) {
   if(*inicio == NULL) {
      return; // retorna pq ta vazio
   }

   No *fim = *inicio;
   while(fim->prox->prox != NULL) { // itera até achar o ultimo (para no penultimo)
      fim = fim->prox;
   }

   free(fim->prox); // libera o ultimo
   fim->prox = NULL; // o penultimo passa a apontar pra NULL pq agora é o ultimo
}

// • 3) Implemente uma função no TAD que retorne o número de
// elementos cujo valor seja menor do que um valor v passado por
// parâmetro
// • O protótipo da função deve ser:
// • int lst_conta_menores (No* inicio, int v);

int lst_conta_menores (No *inicio, int v) {
   int qtd = 0; // quantidade de valores menores
   if(inicio == NULL) {
      return qtd; // a lista esta vazia
   }

   No *temp = inicio; // variavel temporaria pra iterar sobre os itens da lista
   while(temp != NULL) { // enquanto nao chegar no ultimo
      if(temp->info < v) { // se for menor incrementa
         qtd++;
      }
      temp = temp->prox; // o temp recebe o proximo nó da lista
   }

   return qtd;
}