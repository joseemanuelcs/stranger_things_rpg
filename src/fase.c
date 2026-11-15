#include <stdio.h>
#include <stdlib.h>
#include "fase.h"
#include "combate.h"

const char *nomeObjetivo(int fase) {
    switch (fase) {
        case 1: return "Baterias de Walkie-Talkie";
        case 2: return "Componentes do Portal";
        case 3: return "Fragmentos de Protecao";
        default: return "Itens";
    }
}
const char *nomeChefe(int fase) {
    switch (fase) {
        case 1: return "Demogorgon";
        case 2: return "Devorador de Mentes";
        case 3: return "Vecna";
        default: return "Chefe";
    }
}

void iniciarNovaFase(Tabuleiro *t, int numeroFase) {
    int i;
    t->faseAtual = numeroFase;
    t->posicaoAtual = 0;
    t->totalCasas = TOTAL_CASAS;
    t->objetivosColetados = 0;
    t->chefeDerrotado = 0;
    for (i = 0; i < 3; i++) t->monstrosDerrotados[i] = 0;
    for (i = 0; i < TOTAL_CASAS; i++) {
        t->mapa[i] = CASA_VAZIA;
        t->objetivosEncontrados[i] = 0;
    }
    /* Os objetivos sao encontrados ao passar pelas casas: nunca ficam inacessiveis. */
    t->mapa[5] = CASA_OBJETIVO;
    t->mapa[12] = CASA_OBJETIVO;
    t->mapa[17] = CASA_OBJETIVO;
    t->mapa[3] = CASA_ARMADILHA;
    t->mapa[7] = CASA_CURA;
    t->mapa[9] = CASA_MONSTRO;
    t->mapa[14] = CASA_MONSTRO;
    t->mapa[16] = CASA_CURA;
    t->mapa[19] = CASA_CHEFE;
    printf("\n==========================================\n");
    printf("      FASE %d / 3\n", numeroFase);
    puts("==========================================");
    if (numeroFase == 1) puts("O DESAPARECIMENTO EM HAWKINS");
    else if (numeroFase == 2) puts("A AMEACA DO DEVORADOR DE MENTES");
    else puts("O CONFRONTO FINAL: VECNA");
    printf("Missao: encontre 3 %s e derrote %s.\n", nomeObjetivo(numeroFase), nomeChefe(numeroFase));
    puts("Regras: os itens sao coletados ao atravessar as casas; a luta contra o chefe exige os tres itens.");
}

int rolarDado(void) { return rand() % 6 + 1; }

void desenharTabuleiro(const Tabuleiro *t) {
    int i;
    printf("\nMAPA DE HAWKINS - FASE %d\n", t->faseAtual);
    for (i = 0; i < t->totalCasas; i++) {
        if (i == t->posicaoAtual) printf("[P]");
        else if (t->mapa[i] == CASA_CHEFE) printf("[C]");
        else if (t->mapa[i] == CASA_OBJETIVO && !t->objetivosEncontrados[i]) printf("[?]");
        else printf("[ ]");
        if ((i + 1) % 10 == 0) putchar('\n');
    }
    printf("Posicao: %d/%d | %s: %d/3 | Chefe: %s\n",
           t->posicaoAtual + 1, t->totalCasas, nomeObjetivo(t->faseAtual),
           t->objetivosColetados, t->chefeDerrotado ? "derrotado" : "vivo");
}

void coletarObjetivos(Tabuleiro *t, int posicaoAnterior) {
    int i;
    for (i = posicaoAnterior + 1; i <= t->posicaoAtual; i++) {
        if (t->mapa[i] == CASA_OBJETIVO && !t->objetivosEncontrados[i]) {
            t->objetivosEncontrados[i] = 1;
            t->objetivosColetados++;
            printf(">> Voce encontrou um item: %s! (%d/3)\n", nomeObjetivo(t->faseAtual), t->objetivosColetados);
        }
    }
}

int missaoCumprida(const Tabuleiro *t) {
    return t->objetivosColetados == TOTAL_OBJETIVOS && t->chefeDerrotado;
}

/* Retorna 0 quando a entrada foi encerrada; 1 nos demais casos. */
int executarEventoCasa(Tabuleiro *t, Personagem *p) {
    int indice;
    Monstro inimigo;
    ResultadoCombate resultado;
    printf("\n[LOCALIZACAO] Casa %d de %d.\n", t->posicaoAtual + 1, t->totalCasas);
    switch (t->mapa[t->posicaoAtual]) {
        case CASA_VAZIA:
            puts(">> Tudo quieto... por enquanto!");
            break;
        case CASA_OBJETIVO:
            puts(">> Esta area continha um dos itens da missao.");
            break;
        case CASA_CURA:
            p->vida += 20;
            if (p->vida > p->vidaMax) p->vida = p->vidaMax;
            puts(">> Voce encontrou Waffles e recuperou ate 20 de vida!");
            break;
        case CASA_ARMADILHA:
            receberDanoHeroi(p, 10 + 5 * t->faseAtual);
            printf(">> Armadilha do Mundo Invertido! Vida atual: %d.\n", p->vida);
            break;
        case CASA_MONSTRO:
            /* Casas 9 e 14 representam os dois inimigos comuns de cada fase. */
            indice = t->posicaoAtual == 9 ? 0 : 1;
            if (t->monstrosDerrotados[indice]) {
                puts(">> Este monstro ja foi derrotado. Caminho livre!");
                break;
            }
            inimigo = criarMonstro(t->faseAtual, indice);
            resultado = iniciarCombate(p, &inimigo, 0);
            if (resultado == COMBATE_ENCERRADO) return 0;
            if (resultado == COMBATE_VITORIA) t->monstrosDerrotados[indice] = 1;
            break;
        case CASA_CHEFE:
            if (t->chefeDerrotado) {
                puts(">> Chefe ja derrotado!");
                break;
            }
            if (t->objetivosColetados < TOTAL_OBJETIVOS) {
                puts(">> Falta concluir a coleta! O chefe nao pode ser enfrentado ainda.");
                break;
            }
            inimigo = criarMonstro(t->faseAtual, 2);
            resultado = iniciarCombate(p, &inimigo, 1);
            if (resultado == COMBATE_ENCERRADO) return 0;
            if (resultado == COMBATE_VITORIA) t->chefeDerrotado = 1;
            break;
    }
    return 1;
}
