#define MAX 100
#include <stdbool.h>
#include <stdio.h>

// o primeiro que entra é o primeiro que sai
// fila de banco: quem chega primeiro é atendido primeiro

typedef struct {
    int itens[MAX];
    int ini;    // índice do primeiro elemento
    int fim;    // índice do último elemento
    int qtd;    // quantidade de elementos na fila
} Fila;

// inicializa
void inicializa (Fila *f) {
    f->ini = 0;
    f->fim = -1;
    f->qtd = 0;
}

// verificação se está vazia
bool vazia(Fila *f) {
    return f->qtd == 0;
}

// verificação se está cheia
bool cheia(Fila *f) {
    return f->qtd == MAX;
}

// insere
void insere(Fila *f, int valor) {
    if(cheia(f)) {
        printf("Erro> fila cheia\n");
        return;
    }

    if(vazia(f)) {
        f->itens[0] = valor;
        f->ini++;
        f->fim++;
    }

    f->fim++;
    f->itens[f->fim] = valor;
    f->qtd++;
}

// remove
void remove(Fila *f) {
    if(vazia(f)) {
        printf("Erro: fila vazia\n");
        return;
    }

    f->fim--;
    f->qtd--;
}

// acesso
int acessa(Fila *f) {
    if(vazia(f)) {
        printf("Erro: fila vazia\n");
        return;
    }

    return f->itens[f->fim];
}

// imprime
void imprime(Fila *f) {
    for(int i = 0; i < f->qtd; i++) {
        printf("Elemento: %d\n", f->itens[i]);
    }
}

// tamanho
int tamanho(Fila *f) {
    return f->qtd;
}


