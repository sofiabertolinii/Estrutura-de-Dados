#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
// • 1) Implemente uma função no main que retorne uma flag (0
// ou 1) indicando se um nó passado como parâmetro possui
// um determinado valor como conteúdo como parte da sua
// hierarquia.
// • O protótipo da função deve ser:
// • int possui_valor (No * no, int valor);
int possui_valor(No *no, int valor) {
    if(no == NULL) return 0;
    if(arv_busca_valor_no(no) == valor) {
        return 1; // se tem o valor no nó
    }

    if(arv_busca_irmao(no) != NULL) {
        if(possui_valor(arv_busca_irmao(no), valor)){
            return 1; // se tem nos irmãos
        }
    }
    if(arv_busca_filho(no) != NULL) {
        if(possui_valor(arv_busca_filho(no), valor)) return 1; // se tem nos filhos
    }
    
    return 0;
}

// • 2) Implemente uma função no main que imprima as
// discrepâncias em uma árvore.
// • Nesse caso, considere que uma discrepância é um filho ter o valor
// maior do que o valor do pai. 
void imprime_discrepancias(No *no) {
    if(no == NULL) return;

    No *filho = arv_busca_filho(no);
    while(filho != NULL) {
        if(arv_busca_valor_no(filho) > arv_busca_valor_no(no)) {
            printf("O filho %d é maior que o pai %d\n", arv_busca_valor_no(filho), arv_busca_valor_no(no));
        }
        imprime_discrepancias(filho);  // percorre os descendentes
        filho = arv_busca_irmao(filho); // vai para o próximo filho do mesmo pai
    }
}


// calcula a quantidade de filhos de um nó
static int qtd_filhos(No *no) {
    int count = 0;
    No *filho = arv_busca_filho(no);
    while(filho != NULL) {
        count++;
        filho = arv_busca_irmao(filho);
    }
    return count;
}

// 3) Implemente uma função no main que retorne a maior
// quantidade de filhos existentes de um mesmo pai, a partir
// de um nó passado como parâmetro.
// procurar qual nó tem mais filhos
int busca_maior_quant_filhos(No *no) {
    if(no == NULL) return 0;
    static int maior = 0;

    if(qtd_filhos(no) > maior) {
        maior = qtd_filhos(no);
    }
    busca_maior_quant_filhos(arv_busca_filho(no));
    busca_maior_quant_filhos(arv_busca_irmao(no));
    return maior;
}

void imprime(No * no)
{

    static int endent = 0;
    if (no==NULL)
        return;

    int i;
    for (i=0;i<endent;i++)
        printf("  ");

    printf("%d\n", arv_busca_valor_no(no));
    endent++;
    imprime(arv_busca_filho(no));
    endent--;
    imprime(arv_busca_irmao(no));

}


int main()
{
    Arvore * arv = arv_cria_arvore();
    No * n1 = arv_cria_no(1);
    No * n2 = arv_cria_no(2);
    No * n3 = arv_cria_no(3);
    No * n4 = arv_cria_no(4);
    No * n5 = arv_cria_no(5);
    No * n6 = arv_cria_no(6);

    No * n7 = arv_cria_no(7);
    No * n8 = arv_cria_no(8);
    No * n9 = arv_cria_no(9);
    No * n10 = arv_cria_no(10);

    arv_insere_no(n1, n2);
    arv_insere_no(n1, n3);

    arv_insere_no(n2, n4);
    arv_insere_no(n3, n5);

    arv_insere_no(n5, n6);

    arv_insere_no(n6, n7);
    arv_insere_no(n6, n8);
    arv_insere_no(n6, n9);
    arv_insere_no(n6, n10);

    arv_seta_raiz(arv, n1);


    printf("Arvore: ");
    printf("\n");
    imprime(arv_pega_raiz(arv));
    printf("\n");

    int valor = 10;
    int resp = possui_valor(arv_pega_raiz(arv), valor);
    if (resp)
        printf("\nA arvore possui o valor %d", valor);
    else printf("\nA arvore nao possui o valor %d", valor);

    printf("\nImpressao de discrepancias da arvore\n");
    imprime_discrepancias(arv_pega_raiz(arv));

    int quant = busca_maior_quant_filhos(arv_pega_raiz(arv));
    printf("\n\nGrau da arvore: %d\n", quant);

    return 0;
}




