#ifndef FASE_H
#define FASE_H
#include "personagem.h"

#define TOTAL_CASAS 20
#define TOTAL_OBJETIVOS 3

typedef enum { CASA_VAZIA, CASA_CURA, CASA_ARMADILHA, CASA_MONSTRO, CASA_OBJETIVO, CASA_CHEFE } TipoCasa;
typedef struct {
    int faseAtual, posicaoAtual, totalCasas;
    TipoCasa mapa[TOTAL_CASAS];
    int objetivosColetados, objetivosEncontrados[TOTAL_CASAS];
    int chefeDerrotado;
    int monstrosDerrotados[3];
} Tabuleiro;

void iniciarNovaFase(Tabuleiro *t, int numeroFase);
int rolarDado(void);
void desenharTabuleiro(const Tabuleiro *t);
void coletarObjetivos(Tabuleiro *t, int posicaoAnterior);
int executarEventoCasa(Tabuleiro *t, Personagem *p);
int missaoCumprida(const Tabuleiro *t);
const char *nomeObjetivo(int fase);
const char *nomeChefe(int fase);

#endif
