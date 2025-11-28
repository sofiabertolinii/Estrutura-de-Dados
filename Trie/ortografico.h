
// coloque as palavras corretas no arquivo "dicionario.txt"
// coloque o texto a ser corrigido no arquivo "texto.txt"
// o texto corrigido será salvo no arquivo "corrigido.txt"

#include "trie.h"
#ifndef ORTOGRAFICO_H
#define ORTOGRAFICO_H

// função que carrega as palavras do dicionário em uma trie
Trie *carregar_dicionario(const char *nome_arquivo);
// função que normaliza uma palavra (remove pontuação, converte para minúsculas)
void normalizar_palavra(char *palavra);
// função que retorna uma lista de sugestões de palavras com o mesmo prefixo
char **tr_autocompletar(Trie *t, const char *prefixo, int *n);
// função que calcula a distância de Levenshtein entre duas palavras
int distancia_levenshtein(const char *a, const char *b);
// função que sugere a melhor correção para uma palavra incorreta
char *melhor_sugestao(Trie *t, const char *palavra);
// função que corrige um texto em um arquivo, salvando o resultado em outro arquivo
void corrigir_texto(Trie *t, const char *arquivo_texto, const char *arquivo_saida);

#endif 