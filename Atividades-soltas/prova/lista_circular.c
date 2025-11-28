#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// O último nó aponta de volta para o primeiro (ini).

typedef struct No {
    int valor;
    struct No *prox;
} No;

typedef struct {
    No *ini;   // ponteiro para o primeiro nó
} ListaCircular;

// protótipos
void inicializa(ListaCircular *l) {
    l->ini = NULL;
}

bool vazia(ListaCircular *l) {
    return l->ini == NULL;
}

void inserirInicio(ListaCircular *l, int valor) {
    No *novo = malloc(sizeof(No));
    if(novo == NULL) {
        printf("Erro de alocacao\n");
        return;
    }

    No *fim = l->ini;
    while(fim->prox != l->ini) {
        fim = fim->prox;
    }

    fim->prox = novo;
    novo->valor = valor;
    novo->prox = l->ini;
    l->ini = novo;
}

void inserirFim(ListaCircular *l, int valor) {
    No *novo = malloc(sizeof(No));
    if(novo == NULL) {
        printf("Erro de alocacao\n");
        return;
    }

    No *fim = l->ini;
    while(fim->prox != l->ini) {
        fim = fim->prox;
    }

    fim->prox = novo;
    novo->valor = valor;
    novo->prox = l->ini;
}

void removerInicio(ListaCircular *l) {
    if(vazia(l)) {
        printf("Erro: lista vazia\n");
        return;
    }

    No *fim = l->ini;
    while(fim->prox != l->ini) {
        fim = fim->prox;
    }

    No *removido = l->ini;
    fim->prox = removido->prox;
    l->ini = removido->prox;
    free(removido);
}

void removerFim(ListaCircular *l) {
    if(vazia(l)) {
        printf("Erro: lista vazia\n");
        return;
    }

    No *penultimo = l->ini;
    while(penultimo->prox->prox != l->ini) {
        penultimo = penultimo->prox;
    }

    penultimo->prox->prox = l->ini;
    free(penultimo->prox);
}

No* buscar(ListaCircular *l, int valor) {
    if(vazia(l)) {
        printf("Erro: lista vazia\n");
        return NULL;
    }

    No *temp = l->ini;
    while(temp->prox != l->ini) {
        if(temp->valor == valor) {
            return temp;
        }
        temp = temp->prox;
    }

    return NULL;
}

void exibir(ListaCircular *l) {
    if(vazia(l)) {
        printf("Erro: lista vazia\n");
        return;
    }

    No *temp = l->ini;
    while(temp->prox != l->ini) {
        printf("Elemento: %d\n", temp->valor);
        temp = temp->prox;
    }
    
}

int tamanho(ListaCircular *l) {
    if(vazia(l)) {
        return 0;
    }

    No *temp = l->ini;
    int qtd = 0;
    while(temp->prox != l->ini) {
        qtd++;
    }

    return qtd;
}

// usar o do while pra lista circular