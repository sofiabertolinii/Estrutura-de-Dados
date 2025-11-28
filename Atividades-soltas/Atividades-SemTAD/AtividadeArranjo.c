#include <stdio.h>

// aula 1
// ATIVIDADE: fazer uma função encapsulando a parte em que o cálculo do arranjo é feito
// passar o cálculo do arranjo para dentro de uma função

// aluna Sofia Bertolini Lopes
// Disciplina de Estrutura de dados
//                                                                  NOTA 100/100

int calcula_fatorial (int n);

/* funcao para calcular o valor do fatorial */
int calcula_fatorial (int n){
   int i;

   int f = 1;
   for (i = 1; i <= n; i++)
      f *= i;
   return f;
}

// fazer uma função chamada calcula_arranjo que retorne o numero de arranjos de n elementos tomados k a k dados pela fórmula
// passagem por valor
int calcula_arranjo1 (int n, int k) 
{
   int fat_n = calcula_fatorial(n); // calcula o fatorial de n
   int fat_n_k = calcula_fatorial(n - k); // calcula o fatorial de n - k
   return fat_n/fat_n_k; // retorna o arranjo final
}

// calcula_arranjo2 que faz a mesma coisa, mas dessa vez retorna os valores por referencia
void calcula_arranjo2 (int n, int k, int *r)
{
   int fat_n = calcula_fatorial(n); // calcula o fatorial de n
   int fat_n_k = calcula_fatorial(n - k); // calcula o fatorial de n - k
   *r = fat_n/fat_n_k; // o ponteiro r recebe o resultado final dos arranjos
}

int main (void){
   int n, r;
   printf("Digite um numero nao negativo:");
   scanf("%d", &n);
   r = calcula_fatorial(n);
   printf("Fatorial = %d\n", r);


   int k = 2;
   //calculo do arranjo usando passagem por valor
   r = -1; //;
   r = calcula_arranjo1(n, k);
   printf("Arranjo de %d elementos tomados de %d a %d = %d\n", n,k,k,r);

   //calculo do arranjo usando passagem por referencia
   r = -1;
   calcula_arranjo2(n, k, &r);
   printf("Arranjo de %d elementos tomados de %d a %d = %d\n", n,k,k,r);

   return 0;
}

