#ifndef COMBATE_H
#define COMBATE_H
#include "personagem.h"
#include "monstro.h"

typedef enum { COMBATE_DERROTA = 0, COMBATE_VITORIA = 1, COMBATE_FUGA = 2, COMBATE_ENCERRADO = 3 } ResultadoCombate;
typedef enum { ACAO_ATACAR = 1, ACAO_DEFENDER, ACAO_ESPECIAL, ACAO_FUGIR } AcaoCombate;
ResultadoCombate iniciarCombate(Personagem *p, Monstro *m, int ehChefe);
#endif
