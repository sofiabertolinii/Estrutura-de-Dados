#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* função de criação */
void lst_cria (No ** inicio)
{
    *inicio = NULL; // inicializa todos os elementos como nulos
}


/* retorna 1 se vazia ou 0 se n�o vazia */
int lst_vazia (No* inicio)
{
   return (inicio == NULL); 
}


/* inser��o no in�cio */
void lst_insere (No** inicio, int i)
{
   No* novo = (No*) malloc(sizeof (No));
   novo->info = i;
   novo->prox = *inicio;
   *inicio = novo;
}




void lst_insere_ordenado(No** inicio, int v)
{
    No* ant = lst_localiza_ultimo_menor(*inicio, v);	/* ponteiro para elemento anterior	*/
    insere_lista(inicio, v, ant); // chama a função que insere o novo nó na lista
}

void lst_insere_final (No** inicio, int v)
{
    No* ant = lst_localiza_ultimo(*inicio);	/* ponteiro para o �ltimo elemento	*/
    insere_lista(inicio, v, ant); // chama a função que insere o novo nó na lista
}


void lst_imprime (No* inicio)
{
   No* p = inicio;
   while (p != NULL) {
      printf("info = %d\n", p->info);
      p = p->prox;
   }
}


// Atividade Individual – Parte 1
// • Implemente a função lst_localiza_ultimo_menor
// • No* ant = lst_localiza_ultimo_menor (No *inicio, int v);
// • A função deve varrer os nós a partir de inicio
// • Até encontrar o último nó cujo valor seja menor do que v
// • Esse nó deve ser retornado
// • A função lst_insere_ordenado usa essa informação em
// sua lógica de inserção

No * lst_localiza_ultimo_menor(No * inicio, int v)
{
   No* p = inicio;
   No* ant = NULL; // ponteiro para o nó anterior

   while (p != NULL && p->info < v) { // enquanto não chega no fim e o valor do nó for menor que v
      ant = p; // atualiza o ponteiro para o nó anterior
      p = p->prox; // avança para o próximo nó
   }

   return ant; // retorna o último nó cujo valor é menor que v
}

// Atividade Individual – Parte 2
// • Implemente a função lst_localiza_ultimo
// • No* ant = lst_localiza_ultimo (No *inicio);
// • A função deve varrer os nós a partir de inicio
// • Até encontrar o último nó
// • Esse nó deve ser retornado
// • A função lst_insere_final usa essa informação em sua
// lógica de inserção

No * lst_localiza_ultimo(No * inicio)
{
   No* p = inicio;
   No* ant = NULL; // ponteiro para o nó anterior

   while (p != NULL) { // enquanto não chega no fim
      ant = p; // atualiza o ponteiro para o nó anterior
      p = p->prox; // avança para o próximo nó
   }

   return ant; // retorna o último nó
}

// Atividade Individual – Parte 3
// • Refatore o código encapsulando o trecho que é comum as
// seguintes funções
// • Lst_insere_ordenado
// • Lst_insere_final
// • Em uma função separada chamada insere_lista
// • void insere_lista(No** inicio, int v, No * ant)

void insere_lista(No** inicio, int v, No * ant)
{
   No* novo = (No*) malloc(sizeof (No)); // cria um novo elemento e aloca a memória
   novo->info = v; // passa o valor v para o novo nó

   if (ant == NULL){ // se ant é NULL coloca no início da lista
      novo->prox = *inicio; 
      *inicio = novo; // o início da lista recebe o novo nó
   }
   else { // se ant não é NULL insere no meio ou no final da lista
      novo->prox = ant->prox; 
      ant->prox = novo;
   }
}

// separado
// Atividade Individual – Parte 4
// • Transforme o código em uma TAD para listas.
// • Três arquivos passarão a existir:
// • lista.h (coloquei os protótipos das funções e o tipo No)
// • lista.c (coloquei a implementação das funções)
// • main.c (coloquei o main que testa as funções)

