#ifndef FASE_H
#define FASE_H

#include "personagem.h"

typedef enum {
    CASA_VAZIA,
    CASA_CURA,
    CASA_ARMADILHA,
    CASA_MONSTRO,
    CASA_CHEFÃO
} TipoCasa;

typedef struct {
    int posicaoAtual;
    int totalCasas;
    TipoCasa mapa[20];
    int bateriasColetadas; // Missão principal: juntar 3 baterias
} Tabuleiro;

// Protótipos das funções
void inicializarTabuleiro(Tabuleiro *t);
int rolarDado(void);
void desenharTabuleiro(const Tabuleiro *t);
void executarEventoCasa(Tabuleiro *t, Personagem *p);

#endif
