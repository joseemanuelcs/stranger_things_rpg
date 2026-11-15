#include <assert.h>
#include <stdio.h>
#include "personagem.h"
#include "monstro.h"
#include "fase.h"

int main(void) {
    Tabuleiro t;
    Personagem p = {0};
    Monstro m;
    int fase;
    p.vida = 100;
    p.vidaMax = 100;
    p.nivel = 1;
    for (fase = 1; fase <= 3; fase++) {
        iniciarNovaFase(&t, fase);
        assert(t.faseAtual == fase);
        assert(t.objetivosColetados == 0);
        assert(t.chefeDerrotado == 0);
        assert(!missaoCumprida(&t));
        t.posicaoAtual = 19;
        coletarObjetivos(&t, 0);
        assert(t.objetivosColetados == 3);
        coletarObjetivos(&t, 0);
        assert(t.objetivosColetados == 3);
        assert(!missaoCumprida(&t));
        t.chefeDerrotado = 1;
        assert(missaoCumprida(&t));
        m = criarMonstro(fase, 2);
        assert(m.nivel > 0 && m.xpRecompensa > 0);
        receberDanoMonstro(&m, 10000);
        assert(m.vida == 0);
    }
    receberDanoHeroi(&p, 150);
    assert(p.vida == 0);
    ganharXP(&p, 200);
    assert(p.nivel == 5 && p.xp == 200);
    assert(p.vida == p.vidaMax);
    puts("TESTES DE LOGICA: OK");
    return 0;
}
