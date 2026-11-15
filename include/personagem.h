#ifndef PERSONAGEM_H
#define PERSONAGEM_H

typedef enum { CLASSE_ELEVEN = 1, CLASSE_DUSTIN, CLASSE_HOPPER } ClasseHeroi;

typedef struct {
    char nome[30];
    ClasseHeroi classe;
    int vida, vidaMax, forca, defesa, agilidade, inteligencia;
    char arma[50], armadura[50];
    int xp, nivel;
} Personagem;

int criarPersonagem(Personagem *p);
void exibirStatus(const Personagem *p);
void receberDanoHeroi(Personagem *p, int dano);
void ganharXP(Personagem *p, int xp);
void aplicarBonusAleatorio(Personagem *p);

#endif
