#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 5

char* lelinha (void);
char* duplica (char* s);
int le_qtd ();
void lenomes (char** alunos, int n);
int qtde_comeca_letra (int n, char** alunos, char c);
void liberanomes (int n, char** alunos);
void imprimenomes (int n, char** alunos);
void imprimenomes2 (int n, char alunos[][81]);

char* lelinha (void)
{
   char linha[121];                  /* variável auxiliar para ler linha */
   printf("Digite um nome: ");
   scanf(" %120[^\n]",linha);
   return duplica(linha);
}

char* duplica (char* s)
{
   int n = strlen(s);
   char* d = (char*) malloc ((n+1)*sizeof(char));
   strcpy(d,s);
   return d;
}

// • A função le_nomes é responsável tanto por descobrir o número de alunos quanto por fazer a leitura do nome de cada um
// • Quebre essa função nas duas funções seguintes
// • int le_qtd ()
// • Descobre o número de alunos a serem lidos e retorna essa informação
// • void lenomes (char** alunos, int n)
// • Usada para ler nomes de n alunos na matriz alunos
int le_qtd ()
{
   int n;
   printf("Digite o numero de alunos: ");
   scanf("%d",&n);
   return n;
}

void lenomes (char** alunos, int n)
{
   int i;
   for (i=0; i<n; i++) {
      alunos[i] = lelinha();
   }
}

// • Faça uma função que descubra quantos alunos têm nomes que começam com alguma letra
// • O protótipo da função deve ser:
// • int qtde_comeca_letra (int n, char** alunos, char c)
// • Onde
// • n = número de alunos
// • alunos = matriz de alunos
// • c = caractere a ser pesquisado

int qtde_comeca_letra(int n, char** alunos, char c)
{
   int i, cont = 0;
   for(i = 0; i < n; i++) {
      if(alunos[i][0] == c || alunos[i][0] == c + 32 || alunos[i][0] == c - 32) { // pro caso de ser uma letra maiúscula ou minúscula
         cont++;
      }
   }
   return cont;
}

// • Faça uma função que gere uma nova matriz contendo os x primeiros alunos de uma matriz original
// • O protótipo da função deve ser:
// • char ** separa_melhores (int n, char** alunos, int x)
// • Onde
// • n = número de alunos
// • alunos = matriz de alunos
// • x = número de alunos a serem copiados para a nova matriz

char** separa_melhores(int n, char** alunos, int x)
{
   if (x > n) { // se o numero de alunos que vao ser passados pra matriz for maior que o numero de alunos existentes
      printf("Erro: o numero de alunos passados nao pode ser maior que o numero de alunos existentes.\n");
      return NULL;
   }

   // alocando a memoria necessaria pra retornar os primeiros x alunos
   char** melhores = malloc(x * sizeof(char*));
   if (melhores == NULL) {
      printf("Erro de alocacao.\n");
      return NULL;
   }

   // copiando os primeiros x alunos
   for (int i = 0; i < x; i++) {
      melhores[i] = duplica(alunos[i]);
   }

   return melhores;
}

void liberanomes (int n, char** alunos)
{
   int i;
   for (i=0; i<n; i++)
      free(alunos[i]);
}

void imprimenomes (int n, char** alunos)
{
   int i;
   for (i=0; i<n; i++)
      printf("%s\n", alunos[i]);
}

//essa versao nao funciona. Voce consegue entender porque?
// sim, pois como cada nome tem um tamanho fixo, se o nome for menor que 81 caracteres, o restante do vetor vai ficar vazio e pode imprimir lixo na tela
void imprime (int n, char alunos[][81])
{
   int i;
   for (i=0; i<n; i++)
      printf("%s\n", alunos[i]);
}

// main que testa as funções

int main (void)
{
   int n = le_qtd();  // lê a quantidade de alunos

   char** alunos = malloc(n * sizeof(char*));
   if (alunos == NULL) {
      printf("Erro de alocacao.\n");
      return 0;
   }

   lenomes(alunos, n);  // lê os nomes dos alunos

   imprimenomes(n, alunos);  // imprime os nomes

   char letra;
   printf("\nDigite uma letra para verificar quantos alunos comecam com ela: ");
   scanf(" %c", &letra);
   int qtd = qtde_comeca_letra(n, alunos, letra);
   printf("Quantidade de alunos que comecam com '%c': %d\n", letra, qtd);

   int x;
   printf("\nDigite quantos alunos deseja separar: ");
   scanf("%d", &x);
   char** melhores = separa_melhores(n, alunos, x);
   if (melhores == NULL) {
      printf("Erro de alocacao.");
   }

   printf("\nPrimeiros %d alunos:\n", x);
   imprimenomes(x, melhores);
   liberanomes(x, melhores);
   free(melhores);
   liberanomes(n, alunos);  // libera memória dos nomes
   free(alunos);  // libera memória do vetor de alunos
}

