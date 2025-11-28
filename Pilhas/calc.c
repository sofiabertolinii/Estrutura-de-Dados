#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "calc.h"
#include "pilha.h"


Calc* calc_cria ()
{
   Calc* c = (Calc*) malloc(sizeof(Calc));
   //cria pilha vazia
   c->p = pilha_cria();
   return c;
}


void calc_operando (Calc* c, float v)
{
   /* empilha operando */
   pilha_push(c->p,v);
}

void calc_operador (Calc* c, char op)
{
   float v1, v2, v;

   if (pilha_vazia(c->p))              /* desempilha segundo operando*/
      v2 = 0.0;
   else
      v2 = pilha_pop(c->p);

   if (pilha_vazia(c->p))              /* desempilha segundo operando*/
      v1 = 0.0;
   else
      v1 = pilha_pop(c->p);

   switch (op) {                               /* faz opera��o */
      case '+':    v = v1+v2;     break;
      case '-':     v = v1-v2;      break;
      case '*':     v = v1*v2;     break;
      case '/':     v = v1/v2;      break;
   }

   pilha_push(c->p,v);                     /* empilha resultado */

}

/*• 3) Implemente uma função no TAD de calculadora que
libere a memória ocupada por uma calculadora
• O protótipo da função deve ser:
• void calc_libera (Calc* c); */
void calc_libera (Calc* calc) {
   if (calc) {
      pilha_libera(calc->p); 
      free(calc);
   }
}

/*• 4) Implemente uma função no TAD de calculadora que
retorne o valor de uma equação
• O protótipo da função deve ser:
• float calc_calcula (Calc* c, char * equacao); */
float calc_calcula (Calc* c, char * equacao) {
   
   int tamanho = strlen(equacao); // tamanho da string

   for (int i = 0; i < tamanho; i++) {
       if (equacao[i] >= '0' && equacao[i] <= '9') { // se for um número
           float valor = equacao[i] - '0'; // converte caractere para float 
           calc_operando(c, valor); // calcula a operação
      } else {
           calc_operador(c, equacao[i]);
      }
   }

   if (!pilha_vazia(c->p)) { // coloca o resultado no todo da pilha
       return pilha_pop(c->p);

   } else {
       printf("Erro: Pilha vazia.\n");
       return -1; // ou algum valor de erro apropriado
   }
}