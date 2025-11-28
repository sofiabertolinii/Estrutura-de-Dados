//implementação do TAD de dicionário

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "trie.h"
#include "dict.h"

#define BLOCO_ALLOC 8

// cria um dicionário vazio
Dict *dict_cria(void){
    Dict *novo = malloc(sizeof(Dict));

    novo->palavras = tr_cria();
    novo->cap = BLOCO_ALLOC;
    novo->qtd_palavras = 0;

    // aloca um vetor de 8 ponteiros char e inicializa com NULL
    novo->significados = calloc(BLOCO_ALLOC, sizeof(char*));

    return novo;
}

// destrói um dicionário
void dict_destroi(Dict *dicionario){
    //deve destruir todos os ponteiros em significados, o proprio ponteiro significado, a trie e o dict

    if (dicionario == NULL) return; //dicionario vazio
    tr_destroi(dicionario->palavras); //libera a trie que armazena palavras

    // libera todos os ponteiros válidos no vetor (percorrer toda a capacidade)
    for (int i = 0; i < dicionario->cap; i++)
        if (dicionario->significados[i] != NULL)
            free(dicionario->significados[i]); //libera todos os ponteiros do vetor significados

    free(dicionario->significados); //libera o vetor significados
    free(dicionario); //libera o dicionario
}

// insere uma palavra e o respectivo significao no dicionário
void dict_insere_palavra(Dict *dicionario, char *palavra, char *significado){
    // insere a palavra na Trie (sem assumir que cria novo significado)
    tr_inserir(dicionario->palavras, palavra);

    // encontra o índice da palavra na trie
    int index = tr_indice_palavra(dicionario->palavras, palavra);
    if (index < 0) return; // segurança

    // se vetor pequeno para esse índice, realoca até comportar
    if (index >= dicionario->cap) {
        int oldcap = dicionario->cap;
        while (index >= dicionario->cap) dicionario->cap += BLOCO_ALLOC;
        dicionario->significados = realloc(dicionario->significados, dicionario->cap * sizeof(char*));
        // inicializa novas posições para NULL
        for (int i = oldcap; i < dicionario->cap; i++)
            dicionario->significados[i] = NULL;
    }

    // substitui significado existente ou adiciona novo
    if (dicionario->significados[index] != NULL) {
        free(dicionario->significados[index]);
        dicionario->significados[index] = strdup(significado);
        // não incrementa qtd_palavras porque já havia significado
    } else {
        dicionario->significados[index] = strdup(significado);
        dicionario->qtd_palavras++;
    }
}

// remove uma palavra e o respectivo significado do dicionário
bool dict_remove_palavra(Dict *dicionario, char *palavra){
    // pega índice antes de remover (índice é relativo ao estado atual)
    int index = tr_indice_palavra(dicionario->palavras, palavra);
    if (index < 0) return false;

    // remove da Trie (se falhar, aborta)
    if(!tr_remove(dicionario->palavras, palavra)) return false;

    // libera o significado no vetor
    if(index >= 0 && index < dicionario->cap && dicionario->significados[index] !=  NULL){
        free(dicionario->significados[index]);
        dicionario->significados[index] = NULL; // esvazia e libera

        // compacta o vetor de significados:
        // Desloca todos os elementos posteriores uma posição para trás
        // O loop começa em 'index' e vai até 'qtd_palavras' - 1
        for (int i = index; i < dicionario->qtd_palavras; i++) {
            // Move o ponteiro i+1 para a posição i
            dicionario->significados[i] = dicionario->significados[i + 1];
        }

        // garante que o último elemento da "antiga" lista (que foi movido) seja NULL
        dicionario->significados[dicionario->qtd_palavras] = NULL; 
        dicionario->qtd_palavras--; // Decrementa a contagem
    }
    return true;
}

// busca uma palavra e o respectivo significado do dicionário
char *dict_busca_palavra(Dict *dicionario, char *palavra){
    if(!tr_busca(dicionario->palavras, palavra)) return NULL;
    
    int index = tr_indice_palavra(dicionario->palavras, palavra);
    if (index < 0 || index >= dicionario->cap) return NULL;
    if (dicionario->significados[index] == NULL) return NULL;
    
    printf("%s: %s\n", palavra, dicionario->significados[index]);
    return dicionario->significados[index]; //retorno o significado para a função chamadora
}

// imprime o dicionário inteiro
void dict_imprime(Dict *dicionario){
    // tr_palavras retorna as palavras em ordem de travessia (corretamente 4 palavras)
    char **lista_de_palavras = tr_palavras(dicionario->palavras);
    
    // tr_palavras usa a contagem da Trie, que é a mesma de dicionario->qtd_palavras (4)
    int qtd = dicionario->qtd_palavras; 

    for(int i=0; i < qtd; i++) {
        // Para cada palavra da lista, devemos ENCONTRAR SEU ÍNDICE ATUAL no vetor 'significados'
        int index = tr_indice_palavra(dicionario->palavras, lista_de_palavras[i]);
        
        // Verificação de segurança: se o índice for válido e o significado existir
        if (index >= 0 && index < dicionario->cap && dicionario->significados[index] != NULL) {
            printf("%s: %s\n", lista_de_palavras[i], dicionario->significados[index]);
        } 
    }

    // libera o vetor retornado
    for (int i = 0; i < qtd; i++)
        free(lista_de_palavras[i]);
    free(lista_de_palavras);
}