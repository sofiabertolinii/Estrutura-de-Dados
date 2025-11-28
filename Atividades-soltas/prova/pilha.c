
// o último que entra é o primeiro que sai
// pilha de pratos

// o topo avança, os elementos não precisam ser movidos

#include <stdbool.h>

#define MAX 100

typedef struct {
    int itens[MAX];
    int topo;   // índice do último elemento
} Pilha;


// inicializa(Pilha*)
void inicializa (Pilha *p) {
    p->topo = -1; // -1 é o valor que vai representar que a pilha ainda está vazia
}

// push(Pilha*, valor)
void insere(Pilha *p, int valor) {
    if(p->topo == MAX - 1) {
        printf("Erro, pilha cheia\n");
        return;
    }

    p->topo++; // passa pro próximo que ainda está vazio
    p->itens[p->topo] = valor;
}

// pop(Pilha*) elimina do topo
void elimina(Pilha *p) {
    if(vazia(p)) {
        printf("Erro: pilha vazia\n");
        return;
    }

    p->topo--;
}

// topo(Pilha*)
int topo(Pilha *p) {
    if(vazia(p)) {
        printf("Erro: pilha vazia\n");
        return;
    }

    return p->itens[p->topo];
}   

// isEmpty(Pilha*)
bool vazia(Pilha *p) {
    return p->topo == -1;
}

// exibir(Pilha*)
void imprime(Pilha *p) {
    for(int i = 0; i <= p->topo; i++) {
        printf("Valor: %d\n", p->itens[i]);
    }
}

int tamanho(Pilha *p) {
    return p->topo + 1;
}