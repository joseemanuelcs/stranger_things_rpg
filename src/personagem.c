#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personagem.h"
#include "entrada.h"

int criarPersonagem(Personagem *p) {
    int opcao;
    printf("Digite o nome do seu Jogador: ");
    if (!lerLinha(p->nome, (int)sizeof(p->nome))) return 0;
    if (p->nome[0] == '\0') strcpy(p->nome, "Sobrevivente");
    puts("\nEscolha o seu Personagem:");
    puts("1. Eleven (Vida: 85  | Forca: 5  | Defesa: 6)");
    puts("2. Dustin (Vida: 100 | Forca: 8  | Defesa: 12)");
    puts("3. Hopper (Vida: 130 | Forca: 15 | Defesa: 9)");
    if (!lerOpcao(1, 3, &opcao)) return 0;
    p->classe = (ClasseHeroi)opcao;
    p->nivel = 1;
    p->xp = 0;
    switch (p->classe) {
        case CLASSE_ELEVEN:
            p->vidaMax = 85; p->forca = 5; p->defesa = 6;
            p->agilidade = 12; p->inteligencia = 15;
            strcpy(p->arma, "Poderes Telecineticos");
            strcpy(p->armadura, "Roupa Reforcada");
            break;
        case CLASSE_DUSTIN:
            p->vidaMax = 100; p->forca = 8; p->defesa = 12;
            p->agilidade = 10; p->inteligencia = 14;
            strcpy(p->arma, "Estilingue");
            strcpy(p->armadura, "Colete de Protecao");
            break;
        case CLASSE_HOPPER:
            p->vidaMax = 130; p->forca = 15; p->defesa = 9;
            p->agilidade = 7; p->inteligencia = 9;
            strcpy(p->arma, "Revolver");
            strcpy(p->armadura, "Colete Policial");
            break;
        default: return 0;
    }
    p->vida = p->vidaMax;
    return 1;
}

void exibirStatus(const Personagem *p) {
    printf("\n------------------------------------------\n");
    printf("JOGADOR: %s | Nivel: %d | XP: %d\n", p->nome, p->nivel, p->xp);
    printf("Vida: %d/%d | Forca: %d | Defesa: %d\n", p->vida, p->vidaMax, p->forca, p->defesa);
    printf("Agilidade: %d | Inteligencia: %d\n", p->agilidade, p->inteligencia);
    printf("Arma: %s | Armadura: %s\n", p->arma, p->armadura);
    puts("------------------------------------------");
}

void receberDanoHeroi(Personagem *p, int dano) {
    if (dano <= 0) return;
    p->vida -= dano;
    if (p->vida < 0) p->vida = 0;
}

void ganharXP(Personagem *p, int xp) {
    if (xp <= 0) return;
    p->xp += xp;
    printf(">> Voce ganhou %d de XP!\n", xp);
    while (p->xp >= p->nivel * 50) {
        p->nivel++;
        p->vidaMax += 15;
        p->forca += 2;
        p->defesa += 1;
        p->vida = p->vidaMax;
        printf(">> EVOLUIU! Nivel %d: +15 vida maxima, +2 forca e +1 defesa.\n", p->nivel);
    }
}

void aplicarBonusAleatorio(Personagem *p) {
    switch (rand() % 5) {
        case 0: p->forca++; puts(">> BONUS: +1 de Forca!"); break;
        case 1: p->defesa++; puts(">> BONUS: +1 de Defesa!"); break;
        case 2: p->agilidade++; puts(">> BONUS: +1 de Agilidade!"); break;
        case 3: p->inteligencia++; puts(">> BONUS: +1 de Inteligencia!"); break;
        default:
            p->vidaMax += 5;
            p->vida += 5;
            puts(">> BONUS: +5 de Vida Maxima!");
            break;
    }
}
