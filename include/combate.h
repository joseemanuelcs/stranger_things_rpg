#ifndef COMBATE_H
#define COMBATE_H

#include "personagem.h"
#include "monstro.h"

// Protótipo da função principal de batalha por turnos
// Retorna 1 se o herói venceu, ou 0 se foi derrotado/fugiu
int iniciarCombate(Personagem *p, Monstro *m);

#endif
