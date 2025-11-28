
#include <stdbool.h>
#include <stdio.h>

// uma árvore é uma estrutura de dados que organiza os dados de forma hierárquica
// cada elemento da árvore é chamado de nó
// o nó principal é chamado de raiz
// um nó pode ter filhos (outros nós ligados a ele)
// se um nú não tem filhos, ele é chamado de folha
// se tem pelo menos um filho é chamado de nó interno

// profundidade de um nó: quantos passos você precisa dar desde a raiz até ele
// nível: todos os nós que estão na mesma profundidade

//árvores binárisas: um tipo especial de árvore onde cada nó pode ter no máximo 2 filhos

typedef struct no {
    int val;          // valor guardado no nó
    struct no *esq;   // ponteiro para o filho da esquerda
    struct no *dir;   // ponteiro para o filho da direita
} no_t;

typedef no_t arvore;  // sinônimo: uma árvore é um ponteiro para um nó


// função que recebe uma árvore e retorna quantos nós ela tem
int qtd_nos(arvore *a) {
    if(a == NULL) return 0; // se o nó for nulo conta como zero pq não tem nada no nó, então não é um nó
    return 1 + qtd_nos(a->esq) + qtd_nos(a->dir); // retorna um + a quantidade dos próximos (um contando do nó atual)
}

// função que recebe uma árvore e retorna quantas folhas ela tem
int qtd_folhas(arvore *a) {
    if (a == NULL) return 0; // árvore vazia não tem folhas

    if (a->esq == NULL && a->dir == NULL) {
        // se não tem filhos, é folha
        return 1;
    }

    // senão, soma as folhas das subárvores
    return qtd_folhas(a->esq) + qtd_folhas(a->dir);
}

// função que recebe uma árevore e retorna true se a árvore tiver um nó com esse valor
bool existe_valor(arvore *a, int valor) {
    if(a == NULL) {
        return false;
    }

    if(a->val == valor) return true;

    return existe_valor(a->dir, valor) || existe_valor(a->esq, valor);
}

// função que recebe uma árvore e retorna o nível nessa árvore que está o nó que 
// contém esse valor ou -1 se não estiver em nenhum nó
// o nível passado na chamada principal deve ser 0 (raiz da árvore)
int busca_valor(arvore *a, int valor, int nivel) {
    if (a == NULL) {
        return -1; // árvore vazia ou chegou no fim sem achar
    }

    if (a->val == valor) {
        return nivel; // achou o valor, retorna o nível atual
    }

    // busca na subárvore esquerda
    int esq = busca_valor(a->esq, valor, nivel + 1);
    if (esq != -1) return esq; // se encontrou na esquerda, retorna o nível

    // senão, busca na direita
    return busca_valor(a->dir, valor, nivel + 1);
}

// função que retorna a altura de um nó
// a altura de um nó é a distância da raiz até ele
// quantos passos precisa dar (saindo da raiz) pra chegar até ele
// a altura passada na primeira chamada da função deve ser zero
int altura(arvore *a) {
    if (a == NULL) {
        return -1; // árvore vazia
    }

    int h_esq = altura(a->esq); // calcula a altura da esquerda
    int h_dir = altura(a->dir); // calcula a altura da direita

    if (h_esq > h_dir) { // se a altura da esquerda for maior
        return h_esq + 1;
    } else {
        return h_dir + 1;
    }
}


// função que retorna o fator de equilíbrio do nó raiz dessa árvore
// o fator equilíbrio é a diferença entre a esquerda e a direita
int fator_equilibrio(arvore *a) {
    int qtd_esq = altura(a->esq);
    int qtd_dir = altura(a->dir);

    return qtd_esq - qtd_dir;
}

// função que imprime a árvore
void imprime(arvore *a) {
    if(a == NULL) return;


}

// função que retorna o maior valor da árvore
int maior_valor(arvore *a, int valor) {

}

// função que retorna o menor valor da árvore
int menor_arvore(arvore *a, int valor) {
    
}