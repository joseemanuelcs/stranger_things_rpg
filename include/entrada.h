#ifndef ENTRADA_H
#define ENTRADA_H

int lerLinha(char *destino, int tamanho);
int lerOpcao(int minimo, int maximo, int *opcao);
int esperarEnter(const char *mensagem);
void limparTela(void);

#endif
