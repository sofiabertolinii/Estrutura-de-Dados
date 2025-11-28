#include <stdio.h>

// ATIVIDADE: fazer uma função encapsulando a parte em que a leitura dos valores é feita
// passar a leitura dos valores para dentto de uma função
// aula 2

// ALUNA SOFIA BERTOLINI LOPES

/* Função para cálculo da média */
float calcula_media (int n, float* v)
{
  int i;
  float s = 0.0;
  for (i = 0; i < n; i++)
       s += v[i];
  return s/n;
}


/* Função para cálculo da variância */
float calcula_variancia (int n, float* v, float m)
{
   int i;
   float s = 0.0;
   for (i = 0; i < n; i++)
      s += (v[i] - m) * (v[i] - m);
   return s/n;
}

// Função que lê os valores
void le_valores(float *v)
{
   for(int i = 0; i < 10; i++) {
      printf("Digite um numero: ");
      scanf("%f", &v[i]);
   }
}



int main ( void )
{
   float v[10];
   float med, var;

   le_valores(v); // chamando a função que lê os valores

   med = calcula_media(10,v);
   var = calcula_variancia(10,v,med);

   printf ( "Media = %f	Variancia = %f  \n", med, var);
   return 0;
}

