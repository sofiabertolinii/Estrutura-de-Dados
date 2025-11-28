// TAD de dicionário de palavras baseado em uma Trie com suporte a UTF-8

#ifndef DIC_H
#define DIC_H

#include <stdbool.h>
#include <stdint.h>
#include "trie.h"

typedef struct Dict {
    Trie *palavras;
    char **significados;
    int qtd_palavras;
    int cap;
} Dict;

Dict *dict_cria(void);
void dict_destroi(Dict *dicionario);
void dict_insere_palavra(Dict *dicionario, char *palavra, char *significado);
bool dict_remove_palavra(Dict *dicionario, char *palavra);
char *dict_busca_palavra(Dict *dicionario, char *palavra);
void dict_imprime(Dict *dicionario);

#endif