#include <stdio.h>
#include <stdlib.h>
#include "combate.h"  // <--- ESTA LINHA É A QUE FALTA!

int iniciarCombate(Personagem *p, Monstro *m) {
    printf("\n==========================================\n");
    printf("   BATALHA: %s VS %s!   \n", p->nome, m->nome);
    printf("==========================================\n");

    int turno = 1;
    int especialUsos = 2; // O jogador pode usar o especial 2 vezes por batalha

    while (p->vida > 0 && m->vida > 0) {
        printf("\n--- TURNO %d ---\n", turno);
        printf("%s - Vida: %d/%d\n", p->nome, p->vida, p->vidaMax);
        printf("%s - Vida: %d\n", m->nome, m->vida);
        
        printf("\nEscolha sua acao:\n");
        printf("1. Atacar\n");
        printf("2. Usar Habilidade Especial (Usos restantes: %d)\n", especialUsos);
        printf("3. Tentar Fugir\n");
        printf("Opcao: ");

        int opcao;
        scanf("%d", &opcao);

        if (opcao == 1) {
            int sorte = (rand() % 6) + 1;
            int danoCausado = (p->forca + sorte) - m->defesa;
            if (danoCausado < 2) danoCausado = 2;

            receberDanoMonstro(m, danoCausado);
            printf("\n>> %s atacou o %s e causou %d de dano!\n", p->nome, m->nome, danoCausado);

        } else if (opcao == 2) {
            if (especialUsos > 0) {
                especialUsos--; // Gasta 1 uso
                int danoEspecial = 0;
                
                if (p->classe == CLASSE_ELEVEN) {
                    printf("\n>> Eleven usou PODER TELEQUINÉTICO!\n");
                    danoEspecial = p->forca * 3;
                } else if (p->classe == CLASSE_DUSTIN) {
                    printf("\n>> Dustin usou ESTRATÉGIA COM RADIO!\n");
                    danoEspecial = p->forca * 2 + 5;
                } else {
                    printf("\n>> Hopper usou ATAQUE COM ESPINGARDA!\n");
                    danoEspecial = p->forca * 2 + 10;
                }

                receberDanoMonstro(m, danoEspecial);
                printf(">> Dano devastador de %d no %s!\n", danoEspecial, m->nome);
            } else {
                printf("\n>> Voce ja usou todas as suas habilidades especiais nesta batalha!\n");
                continue; // Volta para o inicio do menu sem gastar o turno
            }

        } else if (opcao == 3) {
            int chance = rand() % 2;
            if (chance == 1) {
                printf("\n>> VOCE CONSEGUIU FUGIR DO COMBATE!\n");
                return 1;
            } else {
                printf("\n>> FALHA NA FUGA! O %s bloqueou seu caminho!\n", m->nome);
            }
        } else {
            printf("\n>> Opcao invalida! Voce hesitou e perdeu a vez.\n");
        }

        // Contra-ataque do monstro
        if (m->vida > 0) {
            int sorteMonstro = (rand() % 4) + 1;
            int danoRecebido = (m->ataque + sorteMonstro) - p->defesa;
            if (danoRecebido < 1) danoRecebido = 1;

            receberDanoHeroi(p, danoRecebido);
            printf(">> O %s contra-atacou e causou %d de dano em voce!\n", m->nome, danoRecebido);
        }

        turno++;
    }

    if (p->vida > 0) {
        printf("\n==========================================\n");
        printf("   VITÓRIA! Voce derrotou o %s!\n", m->nome);
        printf("==========================================\n");
        ganharXP(p, m->xpRecompensa);
        return 1;
    } else {
        printf("\n==========================================\n");
        printf("   DERROTA... Voce foi vencido pelo %s.\n", m->nome);
        printf("==========================================\n");
        return 0;
    }
}
