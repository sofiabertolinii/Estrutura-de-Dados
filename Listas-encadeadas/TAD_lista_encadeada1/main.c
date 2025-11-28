#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "lista.c"

int main (void)
{
   No* inicio; // declara uma lista
   lst_cria(&inicio);  // inicializa
   lst_insere_ordenado (&inicio, 5); // insere o 5
   lst_insere_ordenado (&inicio, 2); // insere o 2
   lst_insere_ordenado (&inicio, 3); // insere o 3
   lst_insere_ordenado (&inicio, 1); // insere o 1
   lst_imprime (inicio);        		
   return 0;
}