#ifndef MONSTRO_H
#define MONSTRO_H

typedef struct {
    char nome[30];
    int vida;
    int ataque;
    int defesa;
    int xpRecompensa;
} Monstro;

Monstro criarDemocao(void);
Monstro criarDemogorgon(void);
Monstro criarVecna(void);
void receberDanoMonstro(Monstro *m, int dano);

#endif
