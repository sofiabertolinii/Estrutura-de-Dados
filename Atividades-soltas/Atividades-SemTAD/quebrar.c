#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//  Implemente uma função dentro da pasta quebrar que retorne um vetor de caracteres contendo um prefixo de um vetor de caracteres passado como argumento.
// • O protótipo da função a ser implementada é
// • char * quebrar (char* s1, int n)
// • s1 = vetor de entrada
// • n = tamanho do prefixo

char* quebrar(char* s1, int n) {

   // o tamanho não pode ser negativo, então retorna nulo
   if (n < 0) {
      printf("O tamanho nao pode ser negativo.");
      return NULL;
   }

   char *resultado = malloc(n * sizeof(char));

   // não tem como fazer sem alocar o espaço necessário, então retorna nulo
   if (resultado == NULL) {
      printf("Erro de alocacao.");
      return NULL;
   }

   // passa de um para outro
   for(int i = 0; i < n; i++) {
      resultado[i] = s1[i];
   }

   return resultado;
}

// • Implemente uma função dentro da pasta quebrar que retorne por referência um vetor de caracteres contendo um prefixo de um vetor de caracteres passado como
// argumento.
void quebrar2(char* s1, int n, char** s2) {

   if (n < 0) { // o tamanho nao pode ser negativo
      printf("O tamanho nao pode ser negativo."); 
      *s2 = NULL; 
      return;
   }

   *s2 = malloc((n + 1) * sizeof(char)); // +1 para o caractere nulo

   // retorna nulo se deu erro de alocação
   if (*s2 == NULL) {
      printf("Erro de alocacao.");
      return;
   }

   for(int i = 0; i < n; i++) {
      (*s2)[i] = s1[i]; // passa pro vetor final
   }
   (*s2)[n] = '\0';  // coloca o caractere de fim no final da string
}

int main(){

   char s1[] = "ABCDEF";
   char * s2, * s3;

   int n = 3;
   s2 = quebrar(s1, n);
   printf("\nOs primeiros %d caracteres de %s sao %s", n, s1, s2);

   quebrar2(s1, n, &s3);
   printf("\nOs primeiros %d caracteres de %s sao %s", n, s1, s3);

   return 0;

}
