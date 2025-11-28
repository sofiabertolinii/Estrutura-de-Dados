#include <stdio.h>
#include "notas.c"

int main (void)
{
// testando o módulo notas2 (que usa vetor de inteiros em vez de variáveis inteiras)
   Notas* n = ntn_cria_notas(7, 9); // cria notas com n1=7 e n2=9
   int n1, n2;
   ntn_retorna_notas(n, &n1, &n2); // passa as notas pras variaveis criadas n1 e n2

   printf("Notas iniciais: nota 1 =%d, nota 2 =%d\n", n1, n2);

   int media = ntn_calcula_media(n);
   printf("Media inicial: %d\n", media);

   ntn_modifica_nota1(n, 8); // modifica n1 para 8
   ntn_modifica_nota2(n, 10); // modifica n2 para 10
   ntn_retorna_notas(n, &n1, &n2);

   printf("Notas modificadas: n1=%d, n2=%d\n", n1, n2);
   
   media = ntn_calcula_media(n);
   printf("Media modificada: %d\n", media);
   ntn_libera_notas(n); // libera a memória alocada

   return 0;
}
