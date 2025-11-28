#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "grafo.h"


struct aresta{
    int peso;
    Vertice * vertice_saida;
    struct aresta * prox_aresta;
};

typedef struct aresta Aresta;

struct vertice{
    char nome[50];
    Vertice * prox_vertice;
    struct aresta * primeira_aresta;
    struct aresta * ultima_aresta;
};

/*composi��o de um grafo*/
struct grafo{
    Vertice * primeiro_vertice;
    Vertice * ultimo_vertice;
};


void grafo_imprime_tab_ (Grafo * grafo, Vertice * vertice1, Vertice * vertice2, int prof);


Grafo * grafo_cria()
{
    Grafo * grafo = (Grafo *) malloc(sizeof(Grafo));
    grafo->primeiro_vertice = NULL;
    grafo->ultimo_vertice = NULL;
    return grafo;
}

// • 1) Ajuste a função que libera a memória ocupada por um
// grafo
// • O protótipo da função é:
void grafo_libera (Grafo * grafo){
    if (grafo == NULL) return;

    Vertice * vertice = grafo->primeiro_vertice;
    while (vertice != NULL) {
        Vertice * temp = vertice;
        vertice = vertice->prox_vertice;

        // Libera as arestas do vértice
        Aresta * aresta = temp->primeira_aresta;
        while (aresta != NULL) {
            Aresta * temp_aresta = aresta;
            aresta = aresta->prox_aresta;
            free(temp_aresta);
        }
        free(temp);
    }
    free(grafo);
}


int grafo_qtd_vertices (Grafo * grafo){
    Vertice * vertice = grafo->primeiro_vertice;
    int qtd = 0;
    while (vertice!=NULL){
        qtd++;
        vertice = vertice->prox_vertice;
    }

    return qtd;
}

Vertice ** grafo_busca_vertices_saida(Grafo * grafo, Vertice * vertice, int * cont){

    int num_arestas =0;
    Aresta * aresta = vertice->primeira_aresta;
    while (aresta!=NULL){
        num_arestas++;
        aresta = aresta->prox_aresta;
    }

    Vertice ** vertices = (Vertice **)malloc(sizeof(Vertice * ) * num_arestas);
    int num_aresta = 0;
    aresta = vertice->primeira_aresta;
    while (aresta!=NULL && num_aresta<num_arestas){
        vertices[num_aresta] = aresta->vertice_saida;
        aresta = aresta->prox_aresta;
        num_aresta++;
    }
    *cont = num_arestas;
    return vertices;

}

// • 3) Ajuste a função que busca os vértices de entrada a partir
// de um vértice de saída
// • O protótipo da função é:
// • Vertice ** grafo_busca_vertices_entrada(Grafo * grafo, Vertice *
// vertice, int * cont);
Vertice ** grafo_busca_vertices_entrada(Grafo * grafo, Vertice * vertice, int * cont){
    int num_arestas = 0;
    Aresta * aresta = vertice->primeira_aresta;
    while (aresta != NULL) {
        num_arestas++;
        aresta = aresta->prox_aresta;
    }

    Vertice ** vertices = (Vertice **)malloc(sizeof(Vertice *) * num_arestas);
    if(vertices == NULL) {
        *cont = 0;
        return NULL; // Falha na alocação de memória
    }
    
    int num_aresta = 0;

    aresta = vertice->primeira_aresta;
    while (aresta != NULL && num_aresta < num_arestas) {
        vertices[num_aresta] = aresta->vertice_saida;
        aresta = aresta->prox_aresta;
        num_aresta++;
    }
    *cont = num_arestas;
    return vertices;

}

void grafo_insere_aresta (Grafo * grafo, Vertice * vertice1, Vertice * vertice2, int peso){

    Aresta * aresta = (Aresta*) malloc(sizeof(Aresta));
    aresta->peso = peso;
    aresta->vertice_saida = vertice2;
    aresta->prox_aresta = NULL;

    if (vertice1->ultima_aresta!=NULL){
        vertice1->ultima_aresta->prox_aresta = aresta;
        vertice1->ultima_aresta = aresta;
    }
    else {
        vertice1->primeira_aresta = aresta;
        vertice1->ultima_aresta = aresta;
    }
}



Vertice * grafo_cria_vertice(Grafo * grafo, const char nome[]){

    Vertice * v = (Vertice *)malloc(sizeof(Vertice));
    strcpy(v->nome, nome);
    v->prox_vertice = NULL;
    v->primeira_aresta = NULL;
    v->ultima_aresta = NULL;

    if (grafo->ultimo_vertice!=NULL){
        grafo->ultimo_vertice->prox_vertice = v;
        grafo->ultimo_vertice = v;
    }
    else {
        grafo->primeiro_vertice = v;
        grafo->ultimo_vertice = v;
    }

    return v;
}


Vertice * grafo_retorna_vertice(Grafo * grafo, int indice){
    Vertice * vertice = grafo->primeiro_vertice;
    int qtd = 0;
    while (vertice!=NULL){
        if (qtd == indice)
            return vertice;
        qtd++;
        vertice = vertice->prox_vertice;
    }
    return NULL;

}

char * grafo_retorna_nome(Vertice * vertice){
    return vertice->nome;
}



void grafo_imprime_tab (Grafo * grafo, Vertice * vertice)
{
   grafo_imprime_tab_(grafo, vertice, NULL, 0);
}


void grafo_imprime_tab_ (Grafo * grafo, Vertice * vertice1, Vertice * vertice2, int prof)
{
   static int tab = 0;
   int x;
   for(x=0;x<tab;x++)
       printf("   ");
   if (vertice2!=NULL)
        printf("%s -- %s (%d)\n", vertice2->nome,vertice1->nome, grafo_busca_aresta(grafo, vertice2,vertice1));

   if (prof==3) return;

   tab+=1;
   int num_vertices = 0;
   Vertice ** vertices = grafo_busca_vertices_saida(grafo, vertice1, &num_vertices);
   int i = 0;
   for (i=0;i<num_vertices;i++){
       grafo_imprime_tab_(grafo, vertices[i], vertice1, prof + 1);
   }

   tab-=1;
}

// 2) Ajuste a função que busca o peso de uma aresta entre
// dois vértices do grafo
// • O protótipo da função é:
// • int grafo_busca_aresta (Grafo * grafo, Vertice * vertice1, Vertice *
// vertice2);
int grafo_busca_aresta(Grafo * grafo, Vertice * vertice1, Vertice * vertice2){
    Aresta * aresta = vertice1->primeira_aresta;
    while (aresta != NULL) {
        if (aresta->vertice_saida == vertice2) {
            return aresta->peso;
        }
        aresta = aresta->prox_aresta;
    }
    return -1; // Aresta não encontrada
}





