#include <stdio.h>
#include <stdlib.h>

struct aluno {
   int mat;
   char nome[81];
   char end[121];
   char tel[21];
};

typedef struct aluno Aluno;

void inicializa (int n, Aluno** tab)
{
   int i;
   for (i=0; i<n; i++)
      tab[i] = NULL;
}


void retira (int n, Aluno** tab, int i)
{
   if (i<0 || i>=n) {
      printf("Indice fora do limite do vetor\n");
      exit(1);	/* aborta o programa */
   }

   if (tab[i] != NULL){
      free(tab[i]);
      tab[i] = NULL;  /* indica que na posi��o n�o mais existe dado */
   }
}

void imprime (int n, Aluno** tab, int i)
{
   if (i<0 || i>=n) {
      printf("Indice fora do limite do vetor\n");
      exit(1);	/* aborta o programa */
   }

   if (tab[i] != NULL){
      printf("Matricula: %d\n", tab[i]->mat);
      printf("Nome: %s\n", tab[i]->nome);
      printf("Endereco: %s\n", tab[i]->end);
      printf("Telefone: %s\n", tab[i]->tel);
      printf("-----------------------------\n");
   }
}

void imprime_tudo (int n, Aluno** tab)
{
   int i;
   printf("-----------------------------\n");
   for (i=0; i<n; i++)
      imprime(n,tab,i);
}

// • A função preenche é responsável tanto por fazer a leitura
// dos dados de um aluno quanto por inseri-lo no vetor
// • Quebre essa função nas duas funções seguintes
// • Aluno* cria_aluno()
// • Usada para realizar a entrada dos dados de um aluno
// • void preenche (int n, Aluno** tab, int i, Aluno * aluno )
// • Usada para adicionar um aluno (passado como último parâmetro) no
// vetor

Aluno* cria_aluno()
{
   Aluno* aluno = (Aluno*)malloc(sizeof(Aluno)); // aloca memória pra um aluna do tamanho da struct Aluno
   if (aluno == NULL) {
      printf("Erro de alocacao.\n"); 
      return NULL;
   }
   printf("Entre com a matricula: ");
   scanf("%d", &aluno->mat);
   printf("Entre com o nome: ");
   scanf(" %[^\n]", aluno->nome);
   printf("Entre com o endereco: ");
   scanf(" %[^\n]", aluno->end);
   printf("Entre com o telefone: ");
   scanf(" %[^\n]", aluno->tel);
   return aluno;
}

// para i sendo o indice do vetor de alunos que vai receber o aluno passado
// para n sendo o tamanho do vetor de alunos
// para tab sendo o vetor de ponteiros para alunos

void preenche(int n, Aluno **tab, int i, Aluno *aluno)
{
   if (i < 0 || i >= n) { // se o índice for negativo ou maior que o tamanho do vetor
      printf("Indice fora do limite do vetor\n"); 
      return;  
   }

   if (tab[i] == NULL) { // como inicializou tudo com NULL, se for NULL, significa q tá vazio
      tab[i] = aluno;  // adiciona o aluno na posição i
   } else {
      printf("Posicao ja ocupada. Use outra posicao.\n");
   }
}

// • Faça uma função que insira um aluno na primeira posição
// do vetor e mova todos os demais alunos uma posição
// adiante.
// • O aluno que ocupar a última posição do vetor pode ser
// descartado.
// • O protótipo da função deve ser:
// • void adiciona(int n, Aluno ** tab, Aluno * al)
// • Onde
// • n = número de alunos
// • tab =vetor de ponteiros para aluno
// • al = aluno a ser adicionado

void adiciona(int n, Aluno **tab, Aluno *al)
{
   if (n <= 0) { // se ainda não tem nenhum aluno
      printf("Vetor vazio ou inválido.\n");
      return;
   }

   // desloca todos os alunos uma posição pra direita
   for (int i = n - 1; i > 0; i--) {
      tab[i] = tab[i - 1];
   }

   // insere o novo aluno na primeira posição
   tab[0] = al;
}


int main(void)
{
   int n = 3;  // tamanho do vetor de alunos
   Aluno* tab[n];

   // inicializa tudo com null
   inicializa(n, tab);

   printf(" Criando aluno na posicao 1 \n");
   Aluno* a1 = cria_aluno();
   preenche(n, tab, 0, a1);
   puts("");

   printf(" Criando aluno na posicao 2 \n");
   Aluno* a2 = cria_aluno();
   preenche(n, tab, 1, a2);
   puts("");

   printf(" Adicionando novo aluno na primeira posicao \n");
   Aluno* a3 = cria_aluno();
   adiciona(n, tab, a3);
   puts("");

   printf(" Removendo aluno da posicao 3 \n");
   retira(n, tab, 2);  // remove o aluno da última posição
   puts("");

   printf(" Estado final do vetor \n");
   imprime_tudo(n, tab);
}


