#include "stdlib.h"
#include "stdio.h"
#include "grafo.h"
#include "limits.h"

struct item{
    Vertice * vertice;
    struct item  * precedente;
    struct item  * prox_item;
};

typedef struct item Item;

typedef struct lista{
    Item * primeiro_item;
    Item * ultimo_item;
} Lista;

void menor_caminho (Grafo * grafo, Vertice * origem, Vertice * destino);

Lista * cria_lista();
Item * adiciona_item(Lista * lista, Vertice * vertice);
Item * busca_item(Lista * lista, Vertice * vertice);

//essa eh a funcao a ser implementada. Ela pode ser inspirada na bfs e usar as funcoes que manipulam lista
void menor_caminho (Grafo * grafo, Vertice * origem, Vertice * destino){
    Lista * fila = cria_lista();
    Lista * visitados = cria_lista();

    // adiciona o vértice do início
    Item * item_origem = adiciona_item(fila, origem);
    item_origem->precedente = NULL;
    adiciona_item(visitados, origem);

    Item * atual = NULL; // nó atual sendo processado
    Item * encontrado = NULL; // nó onde o destino foi encontrado

    // BFS
    // encadeamento da busca em largura
    while (fila->primeiro_item != NULL) {
        atual = fila->primeiro_item; // pega o primeiro da fila
        fila->primeiro_item = atual->prox_item; // remove da fila

        // se achamos o destino, interrompe
        // se o vértice atual é o destino
        if (atual->vertice == destino) {
            encontrado = atual;
            break;
        }

        int num_vizinhos = 0;
        // pega os vizinhos do vértice atual
        Vertice ** vizinhos = grafo_busca_vertices_saida(grafo, atual->vertice, &num_vizinhos);

        // para cada vizinho
        // adiciona na fila se não visitado
        for (int i = 0; i < num_vizinhos; i++) {
            Vertice * v = vizinhos[i];

            // verifica se o vizinho já foi visitado
            if (busca_item(visitados, v) == NULL) {
                Item * novo = adiciona_item(fila, v); // adiciona na fila
                novo->precedente = atual;
                adiciona_item(visitados, v);
            }
        }
        free(vizinhos);
    }

    // se não encontrou o destino
    if (encontrado == NULL) {
        printf("Nao existe caminho entre %s e %s.\n",
               grafo_retorna_nome(origem), grafo_retorna_nome(destino));
        return;
    }

    // reconstrói o caminho 
    printf("Menor caminho: ");
    Item * caminho[100];
    int tam = 0;

    // reconstrói o caminho (de trás pra frente)
    Item * p = encontrado;
    while (p != NULL) {
        caminho[tam++] = p;
        p = p->precedente;
    }

    // imprime o caminho na ordem correta
    for (int i = tam - 1; i >= 0; i--) {
        printf("%s", grafo_retorna_nome(caminho[i]->vertice));
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}



Lista * cria_lista(){
    Lista * lista = (Lista*) malloc(sizeof(Lista));
    lista->primeiro_item = NULL;
    lista->ultimo_item = NULL;
    return lista;
}

Item * adiciona_item(Lista * lista, Vertice * vertice){
    Item * item = (Item *)malloc(sizeof(Item));
    item->vertice = vertice;
    item->prox_item = NULL;
    item->precedente = NULL;

    if (lista->primeiro_item==NULL){
        lista->primeiro_item = item;
        lista->ultimo_item = item;
    }
    else{
        lista->ultimo_item->prox_item = item;
        lista->ultimo_item = item;
    }
    return item;

}


Item * busca_item(Lista * lista, Vertice * vertice){
    Item * item = lista->primeiro_item;
    while (item!=NULL){
        if (item->vertice == vertice)
            return item;
        item = item->prox_item;
    }
    return NULL;
}


int main()
{
   Grafo * grafo = grafo_cria(10);
   Vertice * vSantaMaria = grafo_cria_vertice(grafo, "Santa Maria");
   Vertice * vRosario = grafo_cria_vertice(grafo, "Rosario do Sul");
   Vertice * vSaoSepe = grafo_cria_vertice(grafo, "Sao Sepe");
   Vertice * vSaoVicente = grafo_cria_vertice(grafo, "Sao Vicente");
   Vertice * vSaoPedro = grafo_cria_vertice(grafo, "Sao Pedro");
   Vertice * vSaoGabriel = grafo_cria_vertice(grafo, "Sao Gabriel");


   grafo_insere_aresta(grafo, vSantaMaria, vRosario, 430); //230
   grafo_insere_aresta(grafo, vSantaMaria, vSaoPedro, 60);
   grafo_insere_aresta(grafo, vSaoPedro, vSantaMaria, 60);
   grafo_insere_aresta(grafo, vSaoPedro, vSaoVicente, 50);
   grafo_insere_aresta(grafo, vSaoVicente, vRosario, 130);
   grafo_insere_aresta(grafo, vSantaMaria, vSaoSepe, 80);
   grafo_insere_aresta(grafo, vSaoSepe, vSaoGabriel, 140);
   grafo_insere_aresta(grafo, vSaoGabriel, vRosario, 60);

   menor_caminho(grafo, vSantaMaria, vRosario);

   grafo_libera(grafo);

   return 0;
}
