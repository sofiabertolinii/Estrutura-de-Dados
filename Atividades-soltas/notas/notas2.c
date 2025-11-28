// • Os arquivos notas.c e notas.h trazem respectivamente a
// implementação de funções que manipulam informações de notas
// de alunos e a interface com os tipos de dados e funções
// disponibilizada para uso.

// • Além disso, main.c mostra um exemplo de como usar as
// funções do módulo notas.
// • Com base nesses arquivos

// • crie um módulo chamado notas2.c que implemente as funções
// disponibilizadas pela interface notas.h
// • usando um vetor de dois inteiros em vez de duas variáveis do tipo inteiro.
// • Mostre seu uso no main.

#include "notas.h"

struct notas
{
    int n[2];
};

// aloca e retorna um novo struct notas
Notas* ntn_cria_notas (int n1, int n2){
    Notas* n = (Notas*)malloc(sizeof(Notas));
    n->n[0] = n1;
    n->n[1] = n2;
    return n;
}

// libera a memória alocada para o struct notas
void ntn_libera_notas (Notas* n){
    free(n);
}

// modifica a primeira nota
ntn_modifica_nota1 (Notas * n, int n1){
    n->n[0] = n1;
}

// modifica a segunda nota
ntn_modifica_nota2 (Notas * n, int n2){
    n->n[1] = n2;
}

// retorna as duas notas nos dos ponteiros passados como parametros
ntn_retorna_notas (Notas * n, int * n1, int * n2){
    *n1 = n->n[0];
    *n2 = n->n[1];
}

// calcula e retorna a média das duas notas
int ntn_calcula_media (Notas * n){
    return (n->n[0] + n->n[1])/2;
}
