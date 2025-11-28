#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int valor;
    struct No *prox;
    struct No *ant;
} No;

typedef struct {
    No *ini;  // primeiro nó
    No *fim;  // último nó
} ListaDupla;

// inicializa
void inicializa(ListaDupla *l) {
    l->ini = NULL;
    l->fim = NULL;
}

// verificação
bool vazia(ListaDupla *l) {
    return l->ini == NULL;
}

// inserções
void inserirInicio(ListaDupla *l, int valor) {
    No *novo = malloc(sizeof(No));
    if(novo == NULL) {
        printf("Erro de alocacao.\n");
        return;
    }

    novo->ant = NULL;
    novo->valor = valor;
    No *antigo_inicio = l->ini;
    novo->prox = antigo_inicio;
    l->ini = novo;
    antigo_inicio->ant = novo;
}

void inserirFim(ListaDupla *l, int valor) {
    No *novo = malloc(sizeof(No));
    if(novo == NULL) {
        printf("Erro de alocacao.\n");
        return;
    }

    novo->ant = l->fim;
    novo->valor = valor;
    novo->prox = NULL;
    No *antigo_fim = l->fim;
    l->fim = novo;
    antigo_fim->prox = novo;
}

// remoções
void removerInicio(ListaDupla *l) {
    if(vazia(l)) {
        printf("Erro: lista vazia\n");
        return;
    }

    No *antigo_inicio = l->ini;
    l->ini = antigo_inicio->prox;
    l->ini->ant = NULL;

    free(antigo_inicio);
}

void removerFim(ListaDupla *l) {
    if(vazia(l)) {
        printf("Erro: lista vazia\n");
        return;
    }

    No *antigo_fim = l->fim;
    l->fim = antigo_fim->ant;
    l->fim->prox = NULL;

    free(antigo_fim);
}

// busca
No* buscar(ListaDupla *l, int valor) {
    if(vazia(l)) {
        printf("Erro: lista vazia\n");
        return NULL;
    }

    No *temp = l->ini;
    while(temp != NULL) {
        if(temp->valor == valor) {
            return temp;
        }

        temp = temp->prox;
    }

    printf("Valor nao encontrado.\n");
    return NULL;
}

// percursos
void exibirDireto(ListaDupla *l) {
    if(vazia(l)) {
        printf("Erro: lista vazia\n");
        return;
    }

    No *temp = l->ini;
    while(temp != NULL) {
        printf("Valor: %d\n");
        temp = temp->prox;
    }
}


// utilidade
int tamanho(ListaDupla *l) {
    if(vazia(l)) {
        return 0;
    }

    int qtd = 0;
    No *temp = l->ini;
    while(temp != NULL) {
        qtd++;
        temp = temp->prox;
    }

    return qtd;
}
