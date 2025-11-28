/* TAD: C�rculo */
/* Depend�ncia de m�dulos */
#include "ponto.h"

/* Tipo exportado */
typedef struct circulo Circulo;


/* Fun��es exportadas */
/* Fun��o cria - Aloca e retorna um c�rculo com centro (x,y) e raio r */
Circulo* circ_cria (float x, float y, float r);

/* Fun��o libera - Libera a mem�ria de um c�rculo previamente criado */
void circ_libera (Circulo* c);

/* Fun��o area - Retorna o valor da �rea do c�rculo */
float circ_calcula (Circulo* c);

/* Fun��o interior - Verifica se um dado ponto p est� dentro do c�rculo c1*/
int circ_verifica_ponto_interno (Circulo* c, Ponto* p);

// prestar mais atenção na delcaração das funções, faltou inserir o circulo.h no envio da atividade
// ativdade 7
// nota 90/100
// falta o prototipo da função circ_verifica_ponto_interno
// 10 pontos