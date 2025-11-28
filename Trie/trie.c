//implementação de TAD Trie com suporte a UTF-8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"
#include "utf-8.h"

// cria nós na Trie
static No *tr_cria_no(uint32_t codepoint) {
    No *n = malloc(sizeof(No));
    n->codepoint = codepoint;
    // inicializa ponteiros e flag de fim de palavra
    n->filho = NULL;
    n->irmao = NULL;
    n->fimPalavra = false;
    return n;
}

// cria uma Trie vazia
Trie *tr_cria(void) {
    Trie *t = malloc(sizeof(Trie));

    //inicia campos da estrutura
    t->raiz = tr_cria_no(0); // raiz vazia
    t->qtd_nos = 0;
    t->qtd_palavras = 0;
    return t;
}

// libera todos os nós recursivamente
static void no_libera(No *n) {
    if (n == NULL) return;
    no_libera(n->filho);
    no_libera(n->irmao);
    free(n);
}

// libera e destrói o espaço de toda a Trie
void tr_destroi(Trie *t){
    //destrói a Trie
    no_libera(t->raiz);
    free(t);
}

// insere uma palavra na Trie
void tr_inserir(Trie *t, char *palavra){
    No *atual = t->raiz;
    unsigned char *p = (unsigned char *)palavra;
    uint32_t cp;

    // enquanto houver bytes na string
    while (*p != '\0') {

        // decodifica um caractere UTF-8
        int n = utf8_decode(p, &cp);

        //sequência inválida
        if (n < 0) return;

        p += n; // avança o ponteiro pelos bytes lidos

        // procura se já existe um filho com esse codepoint
        No *filho = atual->filho;
        No *anterior = NULL;

        while (filho != NULL && filho->codepoint != cp) {
            anterior = filho;
            filho = filho->irmao;
        }

        // se não encontramos, criamos um novo nó
        if (filho == NULL) {
            filho = tr_cria_no(cp);        // cria o novo nó e coloca o caractere cp
            t->qtd_nos++;                // incrementa total de nós

            //atualiza ponteiros (pai e irmaos)
            if (anterior == NULL) atual->filho = filho; 
            else anterior->irmao = filho;
        }

        // avança para o próximo nó
        atual = filho;
    }

    //se não for fim de palavra -> agora se torna
    if (!atual->fimPalavra) {
        atual->fimPalavra = true; //marcamos como fim da palavra
        t->qtd_palavras++; //palavra inserida, atualizamos qtd_palavras
    }
}

//função auxiliar que remove nós desnecessários (sem filhos e não fim de palavra)
static void tr_remove_nos(No **no, Trie *t) {
    if(t == NULL) return; //árvore vazia
    if (no == NULL || *no == NULL) return; //nó vazio

    // primeiro processa filhos, depois irmãos
    tr_remove_nos(&(*no)->filho, t);
    tr_remove_nos(&(*no)->irmao, t);

    // se nó não é fim de palavra e não tem filhos, remove-o
    if ((*no)->filho == NULL && !(*no)->fimPalavra) {
        No *tmp = *no;
        *no = tmp->irmao;
        free(tmp);
        t->qtd_nos--;
    }
}

// remove palavra de uma Trie
bool tr_remove(Trie *t, char *palavra){
    No *atual = t->raiz;
    unsigned char *p = (unsigned char *)palavra;
    uint32_t cp;

    // enquanto houver bytes na string
    while (*p != '\0') {

        // decodifica um caractere UTF-8
        int n = utf8_decode(p, &cp);

        //sequência inválida
        if (n < 0) return false;

        p += n; // avança o ponteiro pelos bytes lidos

        // procura se já existe um filho com esse codepoint
        No *filho = atual->filho;

        while (filho != NULL && filho->codepoint != cp)
            filho = filho->irmao;

        // se não encontramos, a palavra não existe
        if (filho == NULL) return false;

        // avança para o próximo nó
        atual = filho;
    }

    // se chegamos aqui, a palavra foi encontrada
    if (atual->fimPalavra) {
        atual->fimPalavra = false; // desmarca como fim da palavra
        t->qtd_palavras--; // decrementa o total de palavras
        return true;
    }

    tr_remove_nos(&t->raiz->filho, t); // remove nós desnecessários
    return false; // palavra não existia como tal
}

// busca palavra na Trie
bool tr_busca(Trie *t, char *palavra) {
    No *atual = t->raiz; //nó atual
    unsigned char *p = (unsigned char *)palavra; //ponteiro para a palavra

    //enquanto houver bytes na string, p nao esta apontando para '\0'
    while (*p != '\0') {
        uint32_t cp; //caractere decodificado

        //decodifica um caractere (le 1-4 bytes a partir de p)
        int n = utf8_decode(p, &cp);

        //sequencia invalida
        if (n < 0) return false;
        
        //avança n bytes lidos na decodificação
        p += n;

        No *filho = atual->filho;

        while (filho != NULL && filho->codepoint != cp)
        //se o no filho for diferente do cp, testa com o irmao
            filho = filho->irmao;

        if (filho == NULL) return false; //não achamos
        atual = filho; //testamos o proximo caractere (filho do caractere encontrado - cp)
    }

    return atual->fimPalavra; //se for true/false
}

// função auxiliar para imprimir os nós
static void tr_no_imprimir(No *no, char *buffer, int pos){
    if (no == NULL) return;
    char utf8[5]; //guarda um caractere UTF-8

    //transforma o unicode (contido no nó) em caractere
    int len = utf8_encode(no->codepoint, utf8);

    //coloca cada byte do caractere na posição adequada do buffer
    for (int i = 0; i < len; i++)
        buffer[pos + i] = utf8[i];

    //se for o fim da palavra, add o '\0' ao fim e imprime
    if (no->fimPalavra) {
        buffer[pos + len] = '\0';
        printf("%s\n", buffer); //imprime palavra se for fim
    }

    //se nao for o fim, faz o mesmo com irmaos e filhos (de modo a imprimir todas as palavras)
    tr_no_imprimir(no->filho, buffer, pos + len);
    tr_no_imprimir(no->irmao, buffer, pos);
}

// imprime todas as palavras
void tr_imprimir(Trie *t){
    //imprime todas as palavras
    if(t->qtd_palavras == 0) return;

    char buf[256]; 
    tr_no_imprimir(t->raiz->filho, buf, 0);//começamos no primeiro no com caracteres (primeiro filho da raiz)
}

// função auxiliar para encontrar indice
// retorna -1 se não encontrar
// retorna o índice da palavra se encontrar
static int tr_no_indice_palavra(No *no, char *palavra, char *buffer, int pos, int *contador) {
    if (no == NULL) return -1;

    char utf8[5];
    int tam = utf8_encode(no->codepoint, utf8); //bytes

    // copia o caractere atual pro buffer
    for (int i = 0; i < tam; i++)
        buffer[pos + i] = utf8[i];

    // se o caractere representa o fim da palavra
    if (no->fimPalavra) {
        buffer[pos + tam] = '\0'; // finaliza string

        // se a palavra for igual, retornamos o índice atual
        if (strcmp(buffer, palavra) == 0)
            return *contador;

        (*contador)++; // conta mais uma palavra visitada
    }

    //percorre o filho (próxima letra)
    int continua = tr_no_indice_palavra(no->filho, palavra, buffer, pos + tam, contador);
    if (continua != -1) return continua;

    // percorre o irmão (outra palavra)
    return tr_no_indice_palavra(no->irmao, palavra, buffer, pos, contador);
}

// retorna o indíce da palavra armazenada na trie de acordo com a ordem de percorrimento
int tr_indice_palavra(Trie *t, char *palavra) {
    if (t == NULL || t->raiz == NULL) return -1;

    char buffer[256];
    int contador = 0;

    //retorna indice
    return tr_no_indice_palavra(t->raiz->filho, palavra, buffer, 0, &contador);
}

// função auxiliar que percorre os nós e os coleta (faz uma copia para o vetor de palavras)
static void tr_percorre_coleta_nos(No *no, char *buffer, int pos, char ***vetor, int *cont) {
    if (no == NULL) return;

    char utf8[5];
    int len = utf8_encode(no->codepoint, utf8);

    // copia bytes do caractere atual para o buffer
    for (int i = 0; i < len; i++)
        buffer[pos + i] = utf8[i];

    // se for fim de palavra, adiciona ao vetor
    if (no->fimPalavra) {
        buffer[pos + len] = '\0';

        // adiciona uma cópia da palavra
        (*vetor)[*cont] = strdup(buffer);
        (*cont)++;
    }

    // percorre filhos e irmãos
    tr_percorre_coleta_nos(no->filho, buffer, pos + len, vetor, cont);
    tr_percorre_coleta_nos(no->irmao, buffer, pos, vetor, cont);
}

// retorna um vetor com todas as palavras armazenadas na Trie
char **tr_palavras(Trie *t){

    char **vet = calloc(t->qtd_palavras, sizeof(char*));
    if(vet == NULL) return NULL;

    char buffer[256];

    int cont = 0;
    tr_percorre_coleta_nos(t->raiz->filho, buffer, 0, &vet, &cont);

    return vet;
}

