#include "lista.c"
#include "stdlib.h"
#include "stdio.h"

int main (void)
{
   No* inicio;                      /* declara uma lista n�o iniciada*/
   lst_cria(&inicio);               /* inicia lista vazia*/
   lst_insere_final (&inicio, 7);	/* insere na lista o elemento 7*/
   lst_insere_final (&inicio, 2);	/* insere na lista o elemento 2*/
   lst_insere_final (&inicio, 8);	/* insere na lista o elemento 8*/
   lst_insere_final (&inicio, 1);	/* insere na lista o elemento 1*/

   lst_retira_rec(&inicio, 2);

   printf("Lista atual: \n");
   lst_imprime_rec (inicio);
   No* n = lst_busca(inicio, 8);
   if (n==NULL)
        printf("No nao encontrado\n");
   else printf("No encontrado\n");

   int cont = lst_conta_menores(inicio, 6);
   printf("\nExistem %d valores na lista menores do que 6\n", cont);

   No *ant = lst_localiza_ultimo_menor_rec(NULL, inicio, 6);
   if(ant != NULL) {
      printf("Ultimo menor elemento eh %d", ant->info);
   } else {
      printf("Nao existe");
   }

}

