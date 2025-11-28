#include <stdio.h>
#include <stdbool.h>
// Atualize o método de ordenação na pasta bolha
// encapsulando os trechos indicados
bool compara(int v1, int v2) {
    if(v1 > v2) return true;
    return false;
}

void troca(int *v1, int *v2) {
    int temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

int main ( void )
{
   int v[] = {1,6,7,3,5};

   int x;
   for (x=4;x>0;x--){
       int y;
       for (y=0;y<x;y++){
           if (compara(v[y], v[y + 1])) // encapsule em uma função compara
           {
                troca(&v[y], v[y + 1]);
           }
       }
   }

   for (x=0;x<5;x++){
      printf ("%d ", v[x]);
   }


   return 0;
}



