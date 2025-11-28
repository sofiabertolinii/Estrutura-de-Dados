#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ortografico.h"
#include "utf-8.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funções de uso interno para strings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// função de uso interno que converte caractere para minúscula (UTF-8)
static unsigned char minusculas_utf8(unsigned char c) {
    if(c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

// funções de uso interno para verificar se o caractere é uma letra
static bool eh_letra_utf8(unsigned char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= 0xC0);
}

// função de uso interno para verificar se o caractere é espaço ou pontuação
static bool eh_espaco_utf8(unsigned char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

// compara os primeiros n caracteres de duas strings
// retorna 0 se iguais, <0 se s1 < s2, >0 se s1 > s2
static int compara(const char *s1, const char *s2, int n) {
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0') {
            return s1[i] - s2[i];
        }
    }
    return 0;
}

// copia string src para dest e retorna dest
// não é static pra usar na main.c
char *retorna_copia(char *dest, const char *src) {
    char *ptr = dest;
    while (*src != '\0') {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return dest;
}

// duplica uma string (aloca nova memória) e retorna o ponteiro
static char *duplica(const char *s) {
    int tamanho = utf8_len_chars(s);
    char *novo = malloc((tamanho + 1) * sizeof(char));
    if (novo) {
        retorna_copia(novo, s);
    }
    return novo;
}

// copia n caracteres de src para dest
static void copia(char *dest, const char *src, int n) {
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';  // termina logo após o último char copiado
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funções principais do corretor ortográfico
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// normaliza a palavra (remove pontuação, converte para minúsculas)
void normalizar_palavra(char *palavra) {
    int i = 0;
    int j = 0;
    while (palavra[i]) {
        unsigned char c = palavra[i];
        if (eh_letra_utf8(c)) { // letras acentuadas
            palavra[j] = minusculas_utf8(c);
            j++;
        }
        else if (eh_espaco_utf8(c)) {
            break; // separa palavras
        }
        i++;
    }
    palavra[j] = '\0';
}

// carrega as palavras do dicionário em uma trie
Trie *carregar_dicionario(const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "r");
    if (!f) {
        printf("Erro ao abrir dicionario");
        return NULL;
    }

    Trie *dicionario = tr_cria();
    char palavra[256];

    // lê cada palavra do arquivo (até 255 chars com espaço pro \0) e guarda em palavra
    while (fscanf(f, "%255s", palavra) == 1) {
        normalizar_palavra(palavra); // normaliza a palavra (tira pontuação, minúsculas)
        // insere a palavra na trie se não estiver vazia
        if ((palavra) > 0)
            tr_inserir(dicionario, palavra);
    }

    fclose(f);
    return dicionario;
}

// retorna uma lista de sugestões de palavras com o mesmo prefixo
char **tr_autocompletar(Trie *t, const char *prefixo, int *n) {
    if (!t || !prefixo) return NULL;

    // pega todas as palavras da trie
    char **todas = tr_palavras(t);
    *n = t->qtd_palavras;

    // cria um vetor de vetores para armazenar sugestões
    char **sugestoes = malloc((*n) * sizeof(char*));
    if (!sugestoes) {
        free(todas);
        return NULL;
    }

    // conta quantas palavras começam com o prefixo
    int cont = 0;
    int tam_prefixo = utf8_len_chars(prefixo);

    // enquanto houver palavras, verifica o prefixo
    for(int i = 0; i < *n; i++) {
        // se a palavra começa com o prefixo, adiciona às sugestões
        if (compara(todas[i], prefixo, tam_prefixo) == 0) {
            sugestoes[cont] = duplica(todas[i]);
            cont++;
        }
        free(todas[i]);
    }
    free(todas);

    *n = cont;
    return sugestoes;
}

// distância de Levenshtein entre duas strings
int distancia_levenshtein(const char *a, const char *b) {
    int lenA = utf8_len_chars(a);
    int lenB = utf8_len_chars(b);

    // aloca a matriz do tamanho (lenA+1) x (lenB+1)
    // lenA+1 linhas e lenB+1 colunas
    // cada célula matriz[i][j] vai representar o custo mínimo para transformar
    // os primeiros i caracteres de a nos primeiros j caracteres de b
    int **matriz = malloc((lenA + 1) * sizeof(int *));
    if(!matriz) return -1;

    // aloca as colunas
    for (int i = 0; i <= lenA; i++) {
        matriz[i] = malloc((lenB + 1) * sizeof(int));
        if(!matriz[i]) return -1;
    }

    // inicializa a matriz com os valores base

    // primeira linha recebe valores de 0 a lenB
    for (int i = 0; i <= lenA; i++) matriz[i][0] = i;
    // primeira coluna recebe valores de 0 a lenA
    for (int j = 0; j <= lenB; j++) matriz[0][j] = j;

    for (int i = 1; i <= lenA; i++) {
        for (int j = 1; j <= lenB; j++) {
            // calcula o custo da substituição
            int custo;
            // se os caracteres são iguais, custo 0, senão custo 1
            if (a[i - 1] == b[j - 1]) {
                custo = 0;
            } else {
                custo = 1;
            }

            // CÁLCULO DO CUSRTO MÍNIMO
            // cada célula matriz[i][j] vai representar o custo mínimo para transformar 
            // os primeiros i caracteres de a nos primeiros j caracteres de b
            // calcula o custo da inserção, remoção e substituição e pega o menor
            // se substituição < remoção e inserção
            // substituição: transformou até o caractere anterior das duas palavras + custo da substituição
            // pega a célula 
            int minimo = matriz[i - 1][j - 1] + custo; 
            // remoção de um caractere de a: transformou até o caractere anterior de a + 1 
            if (matriz[i - 1][j] + 1 < minimo) minimo = matriz[i - 1][j] + 1; // remoção
            // inserção de um caractere em a: transformou até o caractere anterior de b + 1
            if (matriz[i][j - 1] + 1 < minimo) minimo = matriz[i][j - 1] + 1; // inserção   
            matriz[i][j] = minimo;
        }
    }

    // resultado está na última célula (canto inferior direito, quando a e b estão completos)
    int resultado = matriz[lenA][lenB];
    for (int i = 0; i <= lenA; i++) free(matriz[i]); // libera colunas
    free(matriz); // libera matriz
    return resultado;
}

// sugere a melhor correção para uma palavra incorreta
char *melhor_sugestao(Trie *t, const char *palavra) {
    if (!t || !palavra) return NULL;

    // pega as 3 primeiras letras para o prefixo
    char prefixo[4];
    copia(prefixo, palavra, 3);
    prefixo[3] = '\0';

    int n;
    // pega as sugestões com o mesmo prefixo
    char **sugestoes = tr_autocompletar(t, prefixo, &n);

    // se não achou nada com o prefixo, busca em TODO o dicionário
    if (n == 0) {
        free(sugestoes);
        sugestoes = tr_palavras(t);
        n = t->qtd_palavras;
    }

    int menor = 1000000000;  // um bilhão (número grande pra comparar)
    char *melhor = NULL;

    // percorre as sugestões e calcula a distância de Levenshtein
    for (int i = 0; i < n; i++) {
        int d = distancia_levenshtein(palavra, sugestoes[i]);
        if (d < menor) {
            menor = d;
            free(melhor);
            melhor = duplica(sugestoes[i]);
        }
        free(sugestoes[i]);
    }
    free(sugestoes);
    return melhor;
}

// corrige um texto em um arquivo, salvando o resultado em outro arquivo
void corrigir_texto(Trie *t, const char *arquivo_texto, const char *arquivo_saida) {
    // abre o arquivo de texto para leitura
    FILE *texto = fopen(arquivo_texto, "r");
    if (!texto) {
        printf("Erro ao abrir texto");
        return;
    }

    // abre o arquivo de saída para escrita
    FILE *corrigido = fopen(arquivo_saida, "w");
    if (!corrigido) {
        printf("Erro ao criar arquivo corrigido");
        fclose(texto);
        return;
    }

    char palavra[256];
    int erros = 0;

    // enquanto houver palavras no texto
    // lê cada palavra (até a quebra de espaço), normaliza e verifica se está na trie
    while (fscanf(texto, "%255s", palavra) == 1) {
        char original[256];
        copia(original, palavra, 255);
        normalizar_palavra(palavra);

        // se a palavra normalizada estiver vazia, mantém a original
        if ((palavra) == 0) {
            fprintf(corrigido, "%s ", original);
            continue;
        }

        // verifica se a palavra está no dicionário
        if (tr_busca(t, palavra)) {
            fprintf(corrigido, "%s ", original);

        // se não estiver, sugere a melhor correção
        } else {
            erros++;
            char *sug = melhor_sugestao(t, palavra);
            // se houver sugestão, escreve no arquivo corrigido
            if (sug) {
                fprintf(corrigido, "%s ", sug);
                free(sug);
            // se não houver sugestão, mantém a palavra original
            } else {
                fprintf(corrigido, "%s ", original);
            }
        }
    }

    printf("Total de palavras incorretas: %d\n", erros);
    fclose(texto);
    fclose(corrigido);
}
