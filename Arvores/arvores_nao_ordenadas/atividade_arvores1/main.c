#include "stdlib.h"
#include "stdio.h"
#include "arvore.h"

// 2) Implemente a mesma função de impressão dentro do
// arquivo main.c
// • O protótipo da função deve ser:
// • void imprime_tab (No* pai, char * lado);
// • Como a função estará no main, não se poderá usar os
// campos da estrutura de um nó diretamente.
// • Será necessário criar algumas funções auxiliares para isso.
// • No* arv_busca_filho (No * no, int dir);
// • int arv_busca_valor (No * no);
void imprime_tab(No *pai, char *lado) {
   static int no = 0;

   if(pai == NULL) return;

   for(int i = 0; i < no; i++) {
      printf("-----");
   }

   int info = arv_busca_info(pai);
   printf("%s %d\n", lado, info);

   No *esquerda = arv_busca_filho(pai, 0);
   No *direita = arv_busca_filho(pai, 1);
   
   no++;
   imprime_tab(esquerda, "esq");
   imprime_tab(direita, "dir");
   no--;

}



int main()
{
   Arvore * arv = arv_cria();
   No * no1 = arv_cria_no(10);
   No * no2 = arv_cria_no(20);
   No * no3 = arv_cria_no(30);
   No * no4 = arv_cria_no(40);
   No * no5 = arv_cria_no(50);

   No * no6 = arv_cria_no(60);

   arv_insere(no1, no2, 0);
   arv_insere(no1, no3, 1);
   arv_insere(no3, no4, 0);
   arv_insere(no3, no5, 1);
   arv_insere(no3, no6, 1);
   arv_seta_raiz (arv, no1);

   arv_imprime(arv_busca_raiz(arv));

   return 0;
}
