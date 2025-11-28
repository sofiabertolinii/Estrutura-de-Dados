#include "stdlib.h"
#include "stdio.h"
#include "grafo.h"

void imprime_tab (Grafo * grafo, int vertice);
void encontra_mais_popular(Grafo * grafo);

// • 1) Implemente uma função de impressão no main
// equivalente à função de impressão existente no TAD.
// • O protótipo da função principal deve ser:
// • void imprime_tab (Grafo * grafo, int vertice);
// • Como a função estará no main, não se poderá usar os
// campos da estrutura do grafo diretamente.
void imprime_tab(Grafo *grafo, int vertice)
{
    static int tab = 0;
    int i, j;
    int qtd_vertices = grafo_qtd_vertices(grafo);

    // imprime as conexões a partir do vértice atual
    for (i = 0; i < qtd_vertices; i++) {
        int valor = grafo_busca_aresta(grafo, vertice, i);
        if (valor != -1) {
            for (j = 0; j < tab; j++)
                printf("   ");
            printf("%d -- %d (%d)\n", vertice, i, valor);

            // recursão limitada a 3 níveis de profundidade (como no TAD)
            if (tab < 3) {
                tab++;
                imprime_tab(grafo, i);
                tab--;
            }
        }
    }
}



// • 3) Considere que os vértices sejam pessoas e que uma
// aresta valorada de a para b indica o quanto a considera b
// popular.
// • Implemente uma função no main que imprima quem é a
// pessoa mais popular e o seu valor de popularidade.
// • O protótipo da função deve ser:
// • void encontra_mais_popular (Grafo * grafo);
void encontra_mais_popular(Grafo * grafo){
    int i, j;
    int mais_popular = -1;
    int valor_popularidade = -1;

    for (i = 0; i < grafo_qtd_vertices(grafo); i++) {
        int popularidade_atual = 0;
        for (j = 0; j < grafo_qtd_vertices(grafo); j++) {
            int valor = grafo_busca_aresta(grafo, j, i);
            if (valor != -1) {
                popularidade_atual += valor;
            }
        }
        if (popularidade_atual > valor_popularidade) {
            valor_popularidade = popularidade_atual;
            mais_popular = i;
        }
    }

    if (mais_popular != -1) {
        printf("A pessoa mais popular é a pessoa %d com um valor de popularidade de %d\n", mais_popular, valor_popularidade);
    } else {
        printf("Nenhuma pessoa encontrada.\n");
    }
}


int main()
{
   Grafo * grafo = grafo_cria();

   grafo_insere_aresta(grafo, 1, 2, 1);
   grafo_insere_aresta(grafo, 1, 3, 1);
   grafo_insere_aresta(grafo, 1, 4, 1);

   grafo_insere_aresta(grafo, 2, 3, 1);
   grafo_insere_aresta(grafo, 2, 4, 1);
   grafo_insere_aresta(grafo, 3, 4, 1);

   grafo_insere_aresta(grafo, 4, 8, 10);

   imprime_tab(grafo, 1);

   //imprime_tab(grafo, 1);

    int cont = 0;
    int vertice = 1;
    int * vertices = grafo_busca_vertices_saida(grafo, vertice, &cont);
    int i;
    printf("Os vertices de saida do vertice %d sao:\n", vertice );
    for (i=0;i<cont;i++){
        printf("%d\n", vertices[i]);

    }

   encontra_mais_popular(grafo);

   grafo_libera(grafo);

   return 0;
}
