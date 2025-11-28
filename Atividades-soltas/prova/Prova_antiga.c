#include <stdlib.h>

// crie uma função que retorne um vetor com n elementos. O vetor deverá conter, na posição i, o número
// de caracteres repetidos na linha i de uma matriz com n palavras. A matriz e o número de linhas são passados como parâmetro.

// O protótipo da função é:
// int *encontra_maior_repeticao (char **matriz, int n);


// Exemplo:
// matriz original vetor gerado
// ({"abcaa\0","abcb\0","aaaa\0"}) => {1,1,4}
// ({"abc\0","aaabb\0","d\0"}) => {1,3,1}

// a linha sempre termina com /0
// o número de linhas é o n passado como parametro
// i é a quantidade de repetição


// refazer pra só contar as repetições consecutivas

int *encontra_maior_repeticao(char **matriz, int n) {
    int *vetor = malloc(n * sizeof(int)); // vetor que será retornado
    if(!vetor) return NULL;

    for(int l = 0; l < n; l++) { // itera em cada linha
        int mais_aparece = 0; // maior qtd de repetições da linha

        for(int c = 0; matriz[l][c] != '\0'; c++) { // itera passando por cada coluna da linha até chegar no final
            char atual = matriz[l][c]; // caractere atual que está contando as repetições
            int qtd = 0; // quantidade do caractere atual

            for(int x = c; matriz[l][c] != '\0'; x++) { // itera mais uma vez começando pelo caractere atual
                if(atual == matriz[l][x]) {
                    qtd++;
                }
            }

            if(qtd > mais_aparece) {
                mais_aparece = qtd;
            }
        }
        vetor[l] = mais_aparece;
    }

    return vetor;
}

int encontra_maior_repeticao_consecutiva(char **matriz, int n) {
    int *vetor = malloc(n * sizeof(int));
    if(vetor == NULL) return NULL;

    for(int l = 0; l < n; l++) { // itera em cada linha
        int mais_aparece = 0; // maior qtd de repetições em cada linha
        
        for(int c = 0; matriz[l][c] != '\0'; c++) { // itera em cada coluna
            
            char atual = matriz[l][c]; // caractere atual que está servindo de comparação
            int qtd = 0; // quantidade de vezes que ele repete

            for(int x = c; matriz[l][c] != '\0'; x++) { // começa a iterar naquele caractere e vai até o final da linha
                if((x == c) && (atual == matriz[l][c])) { // se é o primeiro 
                    qtd++;
                    continue; // volta pro loop
                }

                // se é igual ao caractere que está sendo comparado e também é igual ao caractere anterior a ele
                if((atual == matriz[l][c]) && matriz[l][c] == matriz[l][c - 1]) {
                    qtd++;
                }
            }

            // se a quantidade do caractere atual fo maior que a quantidade que mais aparece
            if(qtd > mais_aparece) {
                mais_aparece = qtd;
            }
        }
        vetor[l] = mais_aparece;
    }
    return vetor;
}

void imprime_vetor(int *vetor, int tam) {
    printf("Imprimindo vetor\n");
    for(int i = 0; i < tam; i++) {
        printf("Elemento %d: %d\n", i + 1, vetor[i]);
    }
}


// tipos a serem usados nas questões 2 e 3
typedef struct no {
    int valor;
    struct no* prox;
} No;

typedef struct lista {
    No *ini;
} Lista;

// suponha que l seja uma lista circular que guarde tarefas, sendo que cada tarefa possui um tempo para sua execução (campo valor).
// Crie uma função de escalonamento de tarefas. Essa função deve percorrer as tarefas de forma circular, dando a uma dela sa chance de ser executada.
// Quando a tarefa é acessada, ela é executada, o que significa que devem ser descontadas 5 horas do seu tempo total para execução.
// Tarefas que forem completamente executadas devem sair da lista. A função encerra quando todas as tarefas forem completadas, ou seja, quando a lista
// ficar vazia. Crie mensagens, avisando quantas horas cada atividade executou, e quando cada atividade terminou.
// // Exemplo: A1(20h), A2(7h), A3(13h), A4(4h)
// Saída: ‘A1 5h’, ‘A2 5h’, ‘A3 5h’, ‘A4 4h’, ‘A4 encerrou’, ‘A1 5h’, ‘A2 2h’,
// ‘A2 encerrou’, ‘A3 5h’, ‘A1 5h’, ‘A3 3h’, ‘A3 encerrou’, ‘A1 5h’, ‘A1 encerrou’

// precisa liberar quando a tarefa já está completa
// na lista circular, o último aponta para o primeiro
// as tarefas só executam 5 horas por vez

void libera(Lista *l, No *liberar) {
    No *fim = l->ini;
    while(fim->prox != l->ini) {
        fim = fim->prox;
    }

    // se vai liberar o primeiro
    if(liberar == l->ini) {
        fim->prox = l->ini->prox;
        l->ini = liberar->prox;
        free(liberar);
        return;
    }

    // se só tem um nó
    if(liberar == l->ini && l->ini->prox == l->ini) {
        l->ini = NULL;
        free(liberar);
    } 

    // acha o anterior do que vai ser liberado pra poder atualizar
    No *anterior = l->ini;
    while(anterior->prox != liberar) {
        anterior = anterior->prox;
    }

    // casos normais
    anterior->prox = liberar->prox;
    free(liberar);
}

// TAREFAS QUE FOREM COMPLETAMENTE EXECUTADAS DEVEM SAIR DA LISTA
void escalona_tarefas(Lista *l) {
    // se o ponteiro pro início for nulo a lista ainda está sem tarefas
    if(l->ini == NULL) {
        printf("Erro: lista vazia\n");
        return;
    }

    No *iterador = l->ini;

    // enquanto a lista não estiver vazia
    while(l->ini != NULL) {
        int idx = 1;
        do {
            if(iterador->valor >= 5) {
                printf("A%d 5h\n", idx);

            } else {
                printf("A%d %dh\n", idx, iterador->valor);
                printf("A%d encerrou\n");
                No *liberado = iterador;
                libera(l, liberado);
            }

            iterador = iterador->prox;
            idx++;
        } while(iterador->prox != l->ini);

        iterador = l->ini; // recomeça até que a lista esteja vazia
    }

}


// crie uma função que verifiqu se uma lista contém elementos cujo valor staisfaça a sequência de Fibonacci
// a função deve remover os elementos inválidos e retornar uma outra lista contendo todos os elementos inválidos
// cada elemento corresponde a soma dos dois anteriores

// considerar uma lista encadeada simples

void libera_simples(Lista *l, No *liberar) {
    // só tem um elemento
    if(liberar == l->ini && liberar->prox == NULL) {
        l->ini = NULL;
        free(liberar);
        return;
    }

    // vai liberar o começo
    if(liberar == l->ini) {
        l->ini = liberar->prox;
        free(liberar);
    }

    // outros casos
    No *anterior = l->ini;
    while(anterior->prox != liberar) {
        liberar = liberar->prox;
    }

    anterior->prox = liberar->prox;
    free(liberar);
}

Lista *encontra_invalidos(Lista *l) {
    if(l->ini == NULL) {
        printf("Erro: lista vazia\n");
        return NULL;
    }

    No *iterador = l->ini;
    No *primeiro = l->ini;
    No *segundo = l->ini->prox;

    while(iterador != NULL) {
        // se for o primeiro ou o segundo
        if(iterador == l->ini || iterador == l->ini->prox) {
            iterador = iterador->prox;
            continue;
        }

        int valor_certo = primeiro->valor + segundo->valor;
        if(iterador->valor != valor_certo) {
            // função insere auxiliar esse valor que eu nao fiz
            libera_simples(l, iterador);
        }

        primeiro = segundo;
        segundo = iterador;
        iterador = iterador->prox;
    }

    // libera a lista
}

