#include "monstro.h"

Monstro criarDemocao(void) {
    Monstro m = {"Democao", 40, 8, 3, 30};
    return m;
}

Monstro criarDemogorgon(void) {
    Monstro m = {"Demogorgon", 75, 14, 6, 70};
    return m;
}

Monstro criarVecna(void) {
    Monstro m = {"Vecna", 130, 18, 8, 200};
    return m;
}

void receberDanoMonstro(Monstro *m, int dano) {
    m->vida -= dano;
    if (m->vida < 0) {
        m->vida = 0;
    }
}
