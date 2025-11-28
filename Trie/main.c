// ExemploUso.c
#include <stdio.h>
#include <stdlib.h>
#include "ortografico.h"

bool strings_iguais(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return false;
        i++;
    }
    return s1[i] == '\0' && s2[i] == '\0';
}

void copia_string(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

// função para interagir com o usuário no modo interativo
// permite digitar palavras e obter correções em tempo real
void modo_interativo(Trie *dicionario) {
    char palavra[256];
    printf("\n=== MODO INTERATIVO ===\n");
    printf("Digite uma palavra (ou 'sair' para encerrar):\n");

    while (1) {
        printf("> ");
        scanf("%255s", palavra);

        // verifica se o usuário quer sair
        if (strings_iguais(palavra, "sair")) break;

        // se a palavra estiver no dicionário está correta
        if (tr_busca(dicionario, palavra)) {
            printf("'%s' está correta!\n", palavra);
        } else {
            // sugere a melhor correção se não estiver no dicionário
            char *sug = melhor_sugestao(dicionario, palavra);
            if (sug) {
                printf("'%s' não está no dicionário. Você quis dizer: '%s'?\n", palavra, sug);
                free(sug);
            } else {
                printf("'%s' não está no dicionário e não há sugestões.\n", palavra);
            }
        }
    }
}

// função para verificar a ortografia de um texto em um arquivo
void verificar_texto(Trie *dicionario, const char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("\n=== VERIFICADOR DE TEXTO (%s) ===\n", arquivo);
    char palavra[256];
    int erros = 0;

    while (fscanf(f, "%255s", palavra) == 1) {
        char original[256];
        // copia a palavra original
        copia_string(original, palavra);
        normalizar_palavra(palavra);

        // se a palavra não estiver no dicionário conta como erro e sugere correção
        if (!tr_busca(dicionario, palavra)) {
            erros++;
            char *sug = melhor_sugestao(dicionario, palavra);
            if (sug) {
                printf(" '%s' possivelmente incorreta. Sugestão: '%s'\n", original, sug);
                free(sug);
            } else {
                printf(" '%s' incorreta, sem sugestão.\n", original);
            }
        }
    }

    printf("\nTotal de palavras incorretas: %d\n", erros);
    fclose(f);
}

// função para testar o autocompletar a partir de um prefixo
void testar_autocompletar(Trie *dicionario) {
    printf("\n=== TESTE DE AUTOCOMPLETAR ===\n");
    char prefixo[32];
    printf("Digite um prefixo: ");
    scanf("%31s", prefixo);

    int n;
    // obtém as sugestões de autocompletar
    char **sugestoes = tr_autocompletar(dicionario, prefixo, &n);

    if (n == 0) {
        printf("Nenhuma palavra começa com '%s'\n", prefixo);
    } else {
        printf("Palavras que começam com '%s':\n", prefixo);
        for (int i = 0; i < n; i++) {
            printf("  - %s\n", sugestoes[i]);
            free(sugestoes[i]);
        }
    }
    free(sugestoes);
}

int main(void) {

    printf("=== DEMONSTRADOR DO CORRETOR ORTOGRÁFICO ===\n\n");
    Trie *dicionario = carregar_dicionario("dicionario.txt");
    if (!dicionario) {
        printf("Erro ao carregar o dicionário.\n");
        return 1;
    }

    int opcao;
    do {
        printf("\nEscolha uma opção:\n");
        printf("1 - Corrigir um arquivo de texto\n");
        printf("2 - Verificar erros em um arquivo\n");
        printf("3 - Testar autocompletar\n");
        printf("4 - Modo interativo (digitar palavras)\n");
        printf("0 - Sair\n");
        printf("> ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            corrigir_texto(dicionario, "texto.txt", "corrigido.txt");
            printf("Arquivo 'corrigido.txt' gerado!\n");
        } else if (opcao == 2) {
            verificar_texto(dicionario, "texto.txt");
        } else if (opcao == 3) {
            testar_autocompletar(dicionario);
        } else if (opcao == 4) {
            modo_interativo(dicionario);
        }
    } while (opcao != 0);

    printf("\nEncerrando...\n");
    tr_destroi(dicionario);
    return 0;
}
