#include <stdio.h>
#include "ponto.c"
#include "circulo.c"

int main (void)
{
   Ponto* p = pto_cria(2.0, 1.0);
   Ponto* q = pto_cria(3.4, 2.1);
   float d = pto_calcula_distancia(p,q);
   printf("Distancia entre pontos: %f\n",d);
   pto_libera(q);
   pto_libera(p);

// Atividade Individual – parte 1
// • Elabore um exemplo de uso no main que verifique se um
// ponto está contido dentro de um círculo.
// • As informações do ponto e do círculo podem ser fixadas no
// código

   Circulo* c = circ_cria(0.0, 0.0, 5.0); // circulo com centro na origem e raio 5

   Ponto* centro = pto_cria(0.0, 0.0); // centro do círculo na origem
   float raio = 5.0; // raio do círculo   
   Ponto* ponto_teste = pto_cria(3.0, 4.0); // ponto a ser testado

   float distancia = pto_calcula_distancia(centro, ponto_teste);
   if (distancia <= raio) {
       printf("O ponto esta dentro do circulo.\n");
   } else {
       printf("O ponto está fora do circulo.\n");
   }
   pto_libera(centro);
   pto_libera(ponto_teste);


   // ou usando a biblioteca circulo (função que retorna se o ponto está dentro do círculo)
   Ponto* p_teste = pto_cria(3.0, 4.0); // ponto a ser testado

   if (circ_verifica_ponto_interno(c, p_teste)) {
       printf("O ponto esta dentro do circulo.\n");
   } else {
       printf("O ponto esta fora do circulo.\n");
   }
   

   // atividade individual - parte 2
   // testando a função que verifica se um círculo está dentro do outro
   Circulo* c1 = circ_cria(0.0, 0.0, 5.0); // círculo maior
   Circulo* c2 = circ_cria(1.0, 1.0, 2.0); // círculo menor dentro do maior 
   if (circ_verifica_circ_interno(c1, c2)) {
       printf("O circulo c2 esta dentro do circulo c1.\n");
   } else {
       printf("O circulo c2 nao esta dentro do circulo c1.\n");
   }

   return 0;
}

// • Os arquivos ponto.c e ponto.h trazem respectivamente a
// implementação de funções que manipulam pontos em um
// espaço cartesiano e a interface com os tipos de dados e
// funções disponibilizada para uso.
// • Os arquivos circulo.c e circulo.h trazem respectivamente a
// implementação de funções que manipulam círculos em um
// espaço cartesiano e a interface com os tipos de dados e
// funções disponibilizada para uso.
// • Além disso, main.c mostra um exemplo de como usar as
// funções do módulo ponto



