#include <stdio.h>
#include <stdlib.h>

/* Fun��o para c�lculo da m�dia */
float calcula_media (int n, float* v)
{
  int i;
  float s = 0.0;
  for (i = 0; i < n; i++)
       s += v[i];
  return s/n;
}


/* Fun��o para c�lculo da vari�ncia */
float calcula_variancia (int n, float* v, float m)
{
   int i;
   float s = 0.0;
   for (i = 0; i < n; i++)
      s += (v[i] - m) * (v[i] - m);
   return s/n;
}

// • Atualize o código na pasta media que calcula a média e a
// variância para que a leitura dos valores seja feita dentro de
// uma função específica
float* le_valores(){
   int *vetor = malloc(10 * sizeof(float));
   if(!vetor) {
      printf("Erro de alocacao.\n");
      return NULL;
   }

   for(int i = 0; i < 10; i++) {
      printf("Digite o %d valor: ", i + 1);
      scanf("%f", &vetor[i]);
   }

   return vetor;
}

int main ( void )
{
   float med, var;

   int *v = le_valores();

   med = calcula_media(10,v);
   var = calcula_variancia(10,v,med);

   printf ( "Media = %f	Variancia = %f  \n", med, var);
   return 0;
}




