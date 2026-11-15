#include <stdio.h>
#include <stdlib.h>
#include "combate.h"
#include "entrada.h"

static int maximo(int a, int b) { return a > b ? a : b; }

ResultadoCombate iniciarCombate(Personagem *p, Monstro *m, int ehChefe) {
    int turno = 1, usosEspeciais = 2;
    printf("\n==========================================\n");
    printf("   BATALHA: %s VS %s!\n", p->nome, m->nome);
    puts("==========================================");
    exibirMonstro(m);
    while (p->vida > 0 && m->vida > 0) {
        int opcao, defesaAtiva = 0, dano = 0;
        printf("\n--- TURNO %d ---\n", turno);
        printf("%s: %d/%d HP | %s: %d HP\n", p->nome, p->vida, p->vidaMax, m->nome, m->vida);
        puts("1. Atacar\n2. Defender\n3. Habilidade Especial\n4. Tentar Fugir");
        printf("Habilidades restantes nesta batalha: %d\n", usosEspeciais);
        if (!lerOpcao(1, 4, &opcao)) return COMBATE_ENCERRADO;
        switch ((AcaoCombate)opcao) {
            case ACAO_ATACAR:
                dano = maximo(1, (rand() % 20 + 1) + p->forca - m->defesa);
                receberDanoMonstro(m, dano);
                printf(">> Ataque comum: %d de dano no %s!\n", dano, m->nome);
                break;
            case ACAO_DEFENDER:
                defesaAtiva = 1;
                puts(">> Voce se defendeu! Reducao do proximo ataque em 50%.");
                break;
            case ACAO_ESPECIAL:
                if (usosEspeciais == 0) {
                    puts(">> Sem habilidades especiais restantes! Escolha outra acao.");
                    continue;
                }
                usosEspeciais--;
                if (p->classe == CLASSE_ELEVEN) {
                    dano = maximo(1, p->inteligencia * 2 + (rand() % 12 + 1) - m->defesa);
                    puts(">> Eleven usou PODER TELECINETICO!");
                    receberDanoMonstro(m, dano);
                } else if (p->classe == CLASSE_DUSTIN) {
                    int cura = 10 + p->inteligencia / 2;
                    p->vida += cura;
                    if (p->vida > p->vidaMax) p->vida = p->vidaMax;
                    dano = maximo(1, p->agilidade + (rand() % 12 + 1) - m->defesa);
                    puts(">> Dustin usou ESTRATEGIA COM RADIO: distração e cura!");
                    printf(">> Recuperou ate %d de vida.\n", cura);
                    receberDanoMonstro(m, dano);
                } else {
                    dano = maximo(1, p->forca * 2 + (rand() % 12 + 1) - m->defesa);
                    puts(">> Hopper usou ATAQUE COM ESPINGARDA!");
                    receberDanoMonstro(m, dano);
                }
                printf(">> Habilidade causou %d de dano!\n", dano);
                break;
            case ACAO_FUGIR:
                if (!ehChefe && (rand() % 100) < 35 + p->agilidade) {
                    puts(">> FUGA BEM-SUCEDIDA! Sem recompensa.");
                    return COMBATE_FUGA;
                }
                if (ehChefe && (rand() % 100) < 30) {
                    puts(">> Voce fugiu do chefe. Ele continua vivo!");
                    return COMBATE_FUGA;
                }
                puts(">> Falhou ao fugir. O inimigo vai atacar!");
                break;
        }
        if (m->vida <= 0) break;
        dano = maximo(1, (rand() % 20 + 1) + m->ataque - p->defesa);
        if (defesaAtiva) dano = maximo(1, (dano + 1) / 2);
        receberDanoHeroi(p, dano);
        printf(">> %s contra-atacou: %d de dano.\n", m->nome, dano);
        turno++;
    }
    if (p->vida <= 0) {
        printf("\n>> DERROTA! %s venceu.\n", m->nome);
        return COMBATE_DERROTA;
    }
    printf("\n>> VITORIA! %s foi derrotado!\n", m->nome);
    ganharXP(p, m->xpRecompensa);
    aplicarBonusAleatorio(p);
    return COMBATE_VITORIA;
}
