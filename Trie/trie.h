// TAD de Trie modificado para palavras com UTF-8

#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct No {
    uint32_t codepoint;         // símbolo Unicode
    struct No *filho;           // primeiro filho
    struct No *irmao;           // próximo irmão
    bool fimPalavra;            // indica final de palavra
} No;

typedef struct Trie {
    No *raiz;
    int qtd_nos;
    int qtd_palavras;
} Trie;

// Funções públicas
Trie *tr_cria(void);
void tr_destroi(Trie *t);
void tr_inserir(Trie *t, char *palavra);
bool tr_busca(Trie *t, char *palavra);
bool tr_remove(Trie *t, char *palavra);
void tr_imprimir(Trie *t);
int tr_indice_palavra(Trie *t, char *palavra);
char **tr_palavras(Trie *t);
#endif
