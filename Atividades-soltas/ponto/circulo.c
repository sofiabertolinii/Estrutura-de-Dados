#include <stdlib.h>
#include "circulo.h"
#include <stdbool.h>
#define PI 3.14159

struct circulo {
   Ponto* p;
   float r;
};

Circulo* circ_cria (float x, float y, float r){
   Circulo* c = (Circulo*)malloc(sizeof(Circulo));
   c->p = pto_cria(x,y);
   c->r = r;
   return c;
}

float circ_calcula (Circulo* c){
   return PI*c->r*c->r;
}



int circ_verifica_ponto_interno (Circulo* c, Ponto* p){
   float d = pto_calcula_distancia(c->p,p);
   return (d < c->r);
}


void circ_libera (Circulo* c){
   pto_libera(c->p);
   free(c);
}

// Crie uma função no módulo círculo que verifique se um círculo c2 está
// contido dentro do outro círculo c1.
// • Para que isso ocorra, é necessário que a distância entre os centro dos
// círculos seja menor do que a diferença entre o raio dos dois círculos.
// • A função deve implementar o seguinte protótipo:
// int circ_verifica_circ_interno (Circulo* c1, Circulo* c2)
// • Teste a função no main

bool circ_verifica_circ_interno (Circulo* c1, Circulo* c2) {
   float d = pto_calcula_distancia(c1->p, c2->p); // distancia entre os centros dos circulos
   if (d < (c1->r - c2->r)) {
       return true; // c2 está dentro de c1
   } else {
       return false; // c2 não está dentro de c1
   }
}