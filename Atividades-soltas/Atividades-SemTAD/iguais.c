#include <stdio.h>
#include <string.h>

// Modifique essa função para que a letra minúscula seja considerada igual a sua respectiva versão maiúscula
// letras minúsculas e maiúsculas tem uma diferença de 32 na tabela ASCII
// passa tudo pra maiúsculo pra que as minúsculas e as maiúsculas sejam iguais
int iguais (char* s1, char* s2)
{
   int i;

   int tam1 = strlen(s1);
   int tam2 = strlen(s2);

   if (tam1!=tam2)
        return 0;

   /* compara caractere por caractere */
   for (i=0; i<tam1; i++) {

         // se é uma letra minúscula e converte para maiúscula
         if (s1[i] >= 'a' && s1[i] <= 'z') {
            s1[i] -= 32; // converte para maiúscula
         }

         // se é uma letra minúscula e converte para maiúscula
         if (s2[i] >= 'a' && s2[i] <= 'z') {
            s2[i] -= 32; // converte para maiúscula
         }
   
            // compara os caracteres convertidos
         if (s1[i] != s2[i]) {
            return 0;
         }
   }

   return 1;
}


int main(){
   char s1[] = "joao do pulo";
   char s2[] = "joao do pulos";
   char s3[] = "Joao do Pulo";

   if (iguais(s1,s2))
   {
       printf("Cadeias %s e %s sao iguais. ", s1, s2);
   } else {
         printf("Cadeias %s e %s nao sao iguais. ", s1, s2);
   } 

      if (iguais(s1,s3)) 
   {
       printf("Cadeias %s e %s sao iguais. ", s1, s2);
   } else {
         printf("Cadeias %s e %s nao sao iguais. ", s1, s2);
   } 


return 0;
}

