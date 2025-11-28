#include "stdlib.h"
#include "stdio.h"
#include "pilha.c"
#include "calc.c"

/*• 1) Implemente uma função no main que imprima os valores
da pilha conforme os valores vão sendo desempilhados
• O protótipo da função deve ser:
• void imprime (Pilha * p); */
void imprime(Pilha *p) {
   Pilha *auxiliar = pilha_cria(); // cria uma pilha auxiliar
   float valor;

   while (!pilha_vazia(p)) {
       valor = pilha_pop(p);
       printf("\n%.0f", valor);
       pilha_push(auxiliar, valor); // armazena os valores em uma pilha auxiliar
   }

   pilha_libera(auxiliar);
}

/*• 2) Implemente uma função no main que gere uma pilha com
os mesmos elementos de uma pilha de entrada, só que
invertidos
• O protótipo da função deve ser:
• Pilha * invertePilha (Pilha * p); */

Pilha *invertePilha (Pilha * p) {
   Pilha *temp = pilha_cria();
   while(!pilha_vazia(p)) {
      float valor = pilha_pop(p);
      pilha_push(temp, valor);
   }
   return temp;
}

int main (void)
{
   Pilha * p1 = pilha_cria();
   pilha_push(p1, 4);
   pilha_push(p1, 6);
   pilha_push(p1, 8);

   printf("\nimpressao da pilha 1");
   imprime(p1);

   //depois da impressao a pilha ficou vazia. Por isso os elementos serao empilhados novamente
   pilha_push(p1, 4);
   pilha_push(p1, 6);
   pilha_push(p1, 8);

   Pilha * p2 = invertePilha(p1);
   printf("\n\nimpressao da pilha invertida");
   imprime(p2);

   char equacao[] = "123-+";
   printf("\n\nCalculando resultado da equacao %s", equacao);
   Calc * calc = calc_cria();
   printf("\nResultado: %.0f",calc_calcula(calc, equacao));
   printf("\n");

   calc_libera(calc);
   return 0;
}
