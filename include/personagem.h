#ifndef PERSONAGEM_H
#define PERSONAGEM_H

typedef enum {
    CLASSE_ELEVEN = 1,
    CLASSE_DUSTIN,
    CLASSE_HOPPER
} ClasseHeroi;

typedef struct {
    char nome[30];
    ClasseHeroi classe;
    int vida;
    int vidaMax;
    int forca;
    int defesa;
    int xp;
    int nivel;
} Personagem;

void criarPersonagem(Personagem *p);
void exibirStatus(const Personagem *p);
void receberDanoHeroi(Personagem *p, int dano);
void ganharXP(Personagem *p, int xp);

#endif
