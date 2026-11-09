#include <stdio.h>
#include <stdlib.h>
#include "fase.h"
#include "combate.h"

void inicializarTabuleiro(Tabuleiro *t) {
    t->posicaoAtual = 0;
    t->totalCasas = 20;
    t->bateriasColetadas = 0;

    for (int i = 0; i < t->totalCasas; i++) {
        t->mapa[i] = CASA_VAZIA;
    }

    // Posições dos eventos no mapa de Hawkins
    t->mapa[3]  = CASA_ARMADILHA;
    t->mapa[5]  = CASA_CURA;       // Kit de Vida / Bateria
    t->mapa[9]  = CASA_MONSTRO;
    t->mapa[12] = CASA_CURA;       // Kit de Vida / Bateria
    t->mapa[15] = CASA_ARMADILHA;
    t->mapa[17] = CASA_CURA;       // Kit de Vida / Bateria
    t->mapa[19] = CASA_CHEFÃO;     // Portal do Vecna
}

int rolarDado(void) {
    return (rand() % 6) + 1;
}

void desenharTabuleiro(const Tabuleiro *t) {
    printf("\nMAPA DE HAWKINS:\n");
    for (int i = 0; i < t->totalCasas; i++) {
        if (i == t->posicaoAtual) {
            printf("[ P ] "); // P = Posição do Jogador
        } else if (t->mapa[i] == CASA_CHEFÃO) {
            printf("[ V ] "); // V = Vecna (Boss)
        } else {
            printf("[   ] ");
        }
    }
    printf("\nBaterias do Walkie-Talkie: %d/3\n", t->bateriasColetadas);
}

void executarEventoCasa(Tabuleiro *t, Personagem *p) {
    printf("\n[LOCALIZACAO] Casa %d de %d.\n", t->posicaoAtual + 1, t->totalCasas);

    switch (t->mapa[t->posicaoAtual]) {
        case CASA_VAZIA:
            printf(">> Tudo quieto nas ruas de Hawkins... Continue atento!\n");
            break;

        case CASA_CURA:
            printf(">> VOCE ENCONTROU UMA BATERIA E WAFFLES!\n");
            t->bateriasColetadas++;
            p->vida += 20;
            if (p->vida > p->vidaMax) p->vida = p->vidaMax;
            printf(">> Recuperou 20 de vida! Baterias para chamar reforcos: %d/3\n", t->bateriasColetadas);
            break;

        case CASA_ARMADILHA:
            printf(">> ALERTA! Tentaculos do Mundo Invertido surgiram do chao!\n");
            receberDanoHeroi(p, 15);
            printf(">> Voce perdeu 15 de vida ao escapar!\n");
            break;

        case CASA_MONSTRO: {
            // Sorteia entre Democão (0) e Demogorgon (1)
            int sorteio = rand() % 2;
            Monstro inimigo;

            if (sorteio == 0) {
                printf(">> ALERTA! Um BANDO DE DEMOCÃES emboscou voce!\n");
                inimigo = criarDemocao();
            } else {
                printf(">> UIVO NO CORREDOR! Um DEMOGORGON apareceu diante de voce!\n");
                inimigo = criarDemogorgon();
            }

            iniciarCombate(p, &inimigo);
            break;
        }

        case CASA_CHEFÃO: {
            printf(">> O RELOGIO BADALA... VECNA ESTA ESPERANDO POR VOCE!\n");
            Monstro vecna = criarVecna(); // Usa o construtor do chefe final
            iniciarCombate(p, &vecna);
            break;
        }
    }
}
