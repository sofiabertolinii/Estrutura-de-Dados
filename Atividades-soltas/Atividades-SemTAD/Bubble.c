#include <stdio.h>

// ATIVIDADE: encapsular a parte de comparação e de troca em duas funções
// aula 2
// parte 2: prever a parte em que a parte final do vetor já esteja ordenada
// se não teve diferença na comparação ja pode sair do loop

// ALUNA SOFIA BERTOLINI LOPES

# include <stdbool.h>
# include <stdlib.h>

bool compara(int primeiro, int segundo) {
    if (primeiro > segundo) {
        return true;
    }
    return false;
}

void troca(int vetor[], int idx) {
    int temp = vetor[idx];
    vetor[idx] = vetor[idx + 1];
    vetor[idx + 1] = temp;
}

int main ( void )
{
   int v[] = {1,6,7,3,5};

   int x;

   for (x=4;x>0;x--){
       int y;
       for (y=0;y<x;y++){

            bool teve_troca = false;
            if (compara(v[y], v[y + 1])) // usando a função de comparação
           {
                troca(v, y);
                teve_troca = true;
           }

           if (!teve_troca) { // aqui o loop é interrompido, não houve troca pq a variável teve_troca não foi alterada
            break;
           }
       }
   }

   for (x=0;x<5;x++){
      printf ("%d ", v[x]);
   }


   return 0;
}

