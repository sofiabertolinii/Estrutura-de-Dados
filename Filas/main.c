#include "stdlib.h"
#include "stdio.h"
#include "fila.c"

// função que imprime os valores dos elementos de uma fila
void imprime(Fila *f) {
   while(!fila_vazia(f)) {
      int valor = fila_retira(f);
      printf("Elemento: %d\n", valor);
   }
}


// função que imprima os valores dos elementos de uma fila mas garante que a fila continue com os mesmos elementos
// que antes da impressão
void imprime2(Fila *f) {
   int tamanho = fila_tamanho(f);
   for(int i = 0; i < tamanho; i++) {
      int valor = fila_retira(f);
      printf("Elemento: %d\n", valor);
      fila_insere(f, valor);
   }
}

// função que gere uma nova fila com os elementos pares de uma lista
// cuidar para que a fila original nao perca nenhum dos seus elementos
Fila *separaPares(Fila *f) {
   int tamanho = fila_tamanho(f);
   Fila *pares = fila_cria();
   for(int i = 0; i < tamanho; i++) {
      int valor = fila_retira(f);
      if(valor % 2 == 0) {
         fila_insere(pares, valor);
      }
      fila_insere(f, valor);
   }
   return pares;
}

int main (void)
{

   Fila * f = fila_cria();
   fila_insere(f, 10);
   fila_insere(f, 15);
   fila_insere(f, 20);


   int tam = fila_tamanho(f);
   printf("\nTamanho da lista: %d\n", tam);

   printf("\nElementos\n");
   imprime2(f);

   printf("\n\nElementos pares\n");
   Fila * f2 = separaPares(f);
   imprime2(f2);
   return 0;
}

