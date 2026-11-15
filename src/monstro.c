#include <stdio.h>
#include "monstro.h"

Monstro criarMonstro(int fase, int indice) {
    static const Monstro base[3][3] = {
        {
            {"Democao", "Predador veloz de Hawkins", 32, 7, 3, 1, 30},
            {"Rastejante do Mundo Invertido", "Criatura que se esconde entre as raizes", 42, 9, 4, 2, 40},
            {"Demogorgon", "Predador supremo da primeira temporada", 75, 12, 6, 3, 90}
        },
        {
            {"Democao Alfa", "Versao mais perigosa do Democao", 65, 13, 6, 4, 65},
            {"Hospedeiro", "Morador dominado pelo Devorador de Mentes", 82, 15, 8, 5, 75},
            {"Devorador de Mentes", "Manifestacao da ameaca do Mundo Invertido", 135, 19, 9, 6, 160}
        },
        {
            {"Morcego do Mundo Invertido", "Criatura alada que protege a fortaleza", 105, 18, 10, 7, 95},
            {"Guardiao de Vecna", "Servo poderoso dos portais", 135, 21, 12, 8, 110},
            {"Vecna", "Senhor das visoes e portais", 210, 25, 13, 9, 250}
        }
    };
    if (fase < 1 || fase > 3 || indice < 0 || indice > 2) return base[0][0];
    return base[fase - 1][indice];
}

void receberDanoMonstro(Monstro *m, int dano) {
    if (dano <= 0) return;
    m->vida -= dano;
    if (m->vida < 0) m->vida = 0;
}

void exibirMonstro(const Monstro *m) {
    printf("%s (Nivel %d) - %s\n", m->nome, m->nivel, m->descricao);
    printf("Vida: %d | Ataque: %d | Defesa: %d | XP: %d\n", m->vida, m->ataque, m->defesa, m->xpRecompensa);
}
