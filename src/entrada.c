#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"

int lerLinha(char *destino, int tamanho) {
    int c;
    size_t n;
    if (tamanho < 2 || fgets(destino, tamanho, stdin) == NULL) return 0;
    n = strlen(destino);
    if (n > 0 && destino[n - 1] == '\n') {
        destino[n - 1] = '\0';
    } else if (!feof(stdin)) {
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
    return 1;
}

int lerOpcao(int minimo, int maximo, int *opcao) {
    char linha[80], *fim;
    long valor;
    while (1) {
        printf("Opcao: ");
        if (!lerLinha(linha, (int)sizeof(linha))) return 0;
        valor = strtol(linha, &fim, 10);
        while (*fim == ' ' || *fim == '\t') fim++;
        if (fim != linha && *fim == '\0' && valor >= minimo && valor <= maximo) {
            *opcao = (int)valor;
            return 1;
        }
        printf(">> Opcao invalida! Digite um numero entre %d e %d.\n", minimo, maximo);
    }
}

int esperarEnter(const char *mensagem) {
    char linha[80];
    while (1) {
        printf("%s", mensagem);
        fflush(stdout);
        if (!lerLinha(linha, (int)sizeof(linha))) return 0;
        if (linha[0] == '\0') return 1;
        puts("\n>> Entrada invalida! Pressione apenas ENTER.");
    }
}

void limparTela(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}
