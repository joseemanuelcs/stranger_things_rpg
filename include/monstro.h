#ifndef MONSTRO_H
#define MONSTRO_H

typedef struct {
    char nome[50];
    char descricao[120];
    int vida, ataque, defesa, nivel, xpRecompensa;
} Monstro;

Monstro criarMonstro(int fase, int indice);
void receberDanoMonstro(Monstro *m, int dano);
void exibirMonstro(const Monstro *m);

#endif
