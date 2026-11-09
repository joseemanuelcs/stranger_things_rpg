#include <stdio.h>
#include <string.h>
#include "personagem.h"

void criarPersonagem(Personagem *p) {
    printf("Digite o nome do seu Jogador: ");
    if (scanf("%29s", p->nome) != 1) {
        strcpy(p->nome, "Sobrevivente");
    }

    printf("\nEscolha o seu Personagem:\n");
    printf("1. Eleven (Vida: 85 | Forca: 5 | Defesa: 6)\n");
    printf("2. Dustin (Vida: 100 | Forca: 8 | Defesa: 12)\n");
    printf("3. Hopper (Vida: 130 | Forca: 15 | Defesa: 9)\n");
    printf("Opcao: ");
    
    int op;
    scanf("%d", &op);
    if (op < 1 || op > 3) op = 1;

    p->classe = (ClasseHeroi)op;
    p->nivel = 1;
    p->xp = 0;

    switch (p->classe) {
        case CLASSE_ELEVEN:
            p->vidaMax = 85; p->vida = 85; p->forca = 5; p->defesa = 6;
            break;
        case CLASSE_DUSTIN:
            p->vidaMax = 100; p->vida = 100; p->forca = 8; p->defesa = 12;
            break;
        case CLASSE_HOPPER:
            p->vidaMax = 130; p->vida = 130; p->forca = 15; p->defesa = 9;
            break;
    }
}

void exibirStatus(const Personagem *p) {
    printf("\n------------------------------------------\n");
    printf("JOGADOR: %s | Nivel: %d | XP: %d\n", p->nome, p->nivel, p->xp);
    printf("Vida: %d/%d | Forca: %d | Defesa: %d\n", p->vida, p->vidaMax, p->forca, p->defesa);
    printf("------------------------------------------\n");
}

void receberDanoHeroi(Personagem *p, int dano) {
    p->vida -= dano;
    if (p->vida < 0) p->vida = 0;
}

void ganharXP(Personagem *p, int xp) {
    p->xp += xp;
    printf(">> Voce ganhou %d de XP!\n", xp);
    if (p->xp >= p->nivel * 50) {
        p->nivel++;
        p->vidaMax += 15;
        p->vida = p->vidaMax;
        printf(">> EVOLUIU! Agora voce esta no Nivel %d!\n", p->nivel);
    }
}
