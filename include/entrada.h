#ifndef ENTRADA_H
#define ENTRADA_H

/* Retorna 1 em caso de sucesso, 0 em EOF ou erro de leitura. */
int lerLinha(char *destino, int tamanho);
int lerOpcao(int minimo, int maximo, int *opcao);
int esperarEnter(const char *mensagem);
void limparTela(void);

#endif
