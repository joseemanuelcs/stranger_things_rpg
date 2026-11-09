#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "personagem.h"
#include "monstro.h"
#include "fase.h"

int main(void) {
    srand((unsigned int)time(NULL));

    printf("==========================================\n");
    printf("   STRANGER THINGS: ESCAPE FROM HAWKINS   \n");
    printf("==========================================\n");

    Personagem jogador;
    criarPersonagem(&jogador);

    Tabuleiro mapa;
    inicializarTabuleiro(&mapa);

    // Loop do mapa: anda ate chegar a ultima casa
    while (mapa.posicaoAtual < mapa.totalCasas - 1 && jogador.vida > 0) {
        exibirStatus(&jogador);
        desenharTabuleiro(&mapa);

        printf("\nPressione ENTER para rolar o dado (d6)...");
        getchar(); getchar();

        int dado = rolarDado();
        printf("\n>> Voce tirou %d no dado!\n", dado);

        mapa.posicaoAtual += dado;
        if (mapa.posicaoAtual >= mapa.totalCasas - 1) {
            mapa.posicaoAtual = mapa.totalCasas - 1;
        }

        executarEventoCasa(&mapa, &jogador);
    }

    if (jogador.vida > 0) {
        printf("\n==========================================\n");
        printf("   VOCE CHEGOU AO FINAL DO MAPA!   \n");
        printf("==========================================\n");
    } else {
        printf("\n>> GAME OVER! O Mundo Invertido consumiu voce...\n");
    }

    return 0;
}
