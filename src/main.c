#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "personagem.h"
#include "fase.h"
#include "entrada.h"

int main(void) {
    Personagem jogador;
    Tabuleiro mapa;
    int fase, dado, anterior;
    srand((unsigned int)time(NULL));
    limparTela();
    puts("==========================================");
    puts("   STRANGER THINGS: ESCAPE FROM HAWKINS");
    puts("==========================================");
    if (!criarPersonagem(&jogador)) {
        puts("Entrada encerrada. Jogo finalizado.");
        return 1;
    }
    for (fase = 1; fase <= 3 && jogador.vida > 0; fase++) {
        limparTela();
        iniciarNovaFase(&mapa, fase);
        if (!esperarEnter("\nPressione ENTER para iniciar a fase...")) return 1;
        while (jogador.vida > 0 && !missaoCumprida(&mapa)) {
            limparTela();
            exibirStatus(&jogador);
            desenharTabuleiro(&mapa);
            if (!esperarEnter("\nPressione ENTER para rolar o dado (d6)...")) return 1;
            dado = rolarDado();
            printf("\n>> Voce tirou %d no dado!\n", dado);
            anterior = mapa.posicaoAtual;
            mapa.posicaoAtual += dado;
            if (mapa.posicaoAtual >= mapa.totalCasas) mapa.posicaoAtual = mapa.totalCasas - 1;
            coletarObjetivos(&mapa, anterior);
            if (!executarEventoCasa(&mapa, &jogador)) return 1;
            if (mapa.posicaoAtual == mapa.totalCasas - 1 && !missaoCumprida(&mapa) && jogador.vida > 0) {
                mapa.posicaoAtual = mapa.totalCasas - 4;
                puts("\n>> Voce recuou tres casas para tentar novamente.");
            }
            if (!esperarEnter("\nPressione ENTER para continuar...")) return 1;
        }
        if (jogador.vida > 0) {
            limparTela();
            printf("\n==========================================\n  FASE %d CONCLUIDA!\n==========================================\n", fase);
            printf("Missao concluida: 3 %s e %s derrotado!\n", nomeObjetivo(fase), nomeChefe(fase));
            exibirStatus(&jogador);
            if (fase < 3) {
                jogador.vida += 30;
                if (jogador.vida > jogador.vidaMax) jogador.vida = jogador.vidaMax;
                puts("\nVoce recuperou ate 30 de vida antes da proxima fase.");
                if (!esperarEnter("Pressione ENTER para continuar...")) return 1;
            }
        }
    }
    if (jogador.vida > 0) {
        puts("\n==========================================");
        puts("   VITORIA FINAL! HAWKINS FOI SALVA!");
        puts("==========================================");
        exibirStatus(&jogador);
    } else {
        puts("\n>> GAME OVER! O Mundo Invertido consumiu voce...");
    }
    return 0;
}
