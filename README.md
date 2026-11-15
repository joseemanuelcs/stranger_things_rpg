# Stranger Things: Escape from Hawkins

Jogo de tabuleiro RPG em **linguagem C (C99)**, executado no terminal. Projeto acadêmico da disciplina **DCT1106 - Programação (UFRN, 2026.2)**.

**Aluno:** PREENCHER NOME COMPLETO  
**Matrícula:** PREENCHER MATRÍCULA  
**Vídeo de gameplay:** PREENCHER LINK

> Esta é uma versão proposta para o projeto, baseada no protótipo desenvolvido durante a disciplina. Revise, compreenda, teste e personalize o código antes de entregar. A história é uma adaptação de fã, não oficial.

## História e objetivo

Hawkins sofre com criaturas do Mundo Invertido. Escolha Eleven, Dustin ou Hopper e atravesse três regiões perigosas. Em cada fase, você deve reunir **três itens** e **derrotar o chefe**. A derrota ocorre se a vida chegar a zero; a vitória final exige completar as três fases.

## Personagens

| Personagem | Vida | Força | Defesa | Agilidade | Inteligência | Arma | Armadura | Habilidade especial |
|---|---:|---:|---:|---:|---:|---|---|---|
| Eleven | 85 | 5 | 6 | 12 | 15 | Poderes Telecinéticos | Roupa Reforçada | Telecinese: dano baseado em inteligência |
| Dustin | 100 | 8 | 12 | 10 | 14 | Estilingue | Colete de Proteção | Estratégia com rádio: cura e dano baseado em agilidade |
| Hopper | 130 | 15 | 9 | 7 | 9 | Revólver | Colete Policial | Espingarda: ataque poderoso baseado em força |

As habilidades especiais têm **2 usos por combate**.

## Fases, monstros e missões

| Fase | Cenário | Missão | Monstros comuns | Chefe |
|---|---|---|---|---|
| 1 | O Desaparecimento em Hawkins | Reunir três baterias de walkie-talkie e derrotar o Demogorgon | Democão, Rastejante do Mundo Invertido | Demogorgon |
| 2 | A Ameaça do Devorador de Mentes | Reunir três componentes do portal e derrotar o Devorador de Mentes | Democão Alfa, Hospedeiro | Devorador de Mentes |
| 3 | O Confronto Final | Reunir três fragmentos de proteção e derrotar Vecna | Morcego do Mundo Invertido, Guardião de Vecna | Vecna |

Todos os 9 monstros têm nomes, descrições, vida, ataque, defesa, nível e recompensa de XP diferentes. Cada fase aumenta a força dos oponentes. Alguns nomes são criações inspiradas no universo da série.

## Dinâmica

- O mapa é um vetor de 20 casas. Cada rodada, pressione **somente Enter** para lançar um dado de seis faces (d6) e andar de 1 a 6 casas.
- O avanço é limitado à última casa; não é possível ultrapassar o limite do vetor.
- Casas: vazia, cura (waffles, até +20 HP), armadilha (dano crescente por fase), monstro, objetivo e chefe.
- Itens aparecem nas posições internas 5, 12 e 17 (casas visíveis 6, 13 e 18). Eles são coletados **ao passar ou parar** nelas, uma única vez por fase.
- As casas 10 e 15 têm dois monstros comuns específicos da fase; passar por cima delas pode evitar encontros. Monstros derrotados não ressurgem na mesma fase.
- A casa 20 contém o chefe. O combate com o chefe só acontece depois de reunir os três itens.
- Fugir de um monstro não concede XP. Fugir do chefe exige voltar a enfrentá-lo. Caso não complete a missão, você recua três casas e tenta novamente.
- O jogador mantém nível, XP, equipamentos e atributos entre fases; ao terminar uma fase, recupera até 30 de vida.

### Combate por turnos

Em cada turno, escolha:

1. **Atacar:** rola d20; dano = máximo(1, d20 + força - defesa do inimigo).
2. **Defender:** reduz aproximadamente pela metade o dano do próximo ataque do monstro (mínimo 1).
3. **Habilidade especial:** habilidade própria de cada classe, duas vezes por combate.
4. **Fugir:** chance de fuga de inimigos comuns é `35 + agilidade` por cento; contra chefes, 30%. Falha consome turno.

Se o monstro sobreviver, ele contra-ataca: dano = máximo(1, d20 + ataque do monstro - defesa do jogador). A função `receberDanoHeroi` aplica o dano via ponteiro e impede vida negativa. O combate termina com vitória, derrota ou fuga.

### Evolução e recompensas

- Vitória concede o XP definido para o monstro e **um bônus aleatório** (+1 força, defesa, agilidade, inteligência ou +5 vida máxima).
- XP é **acumulativo**. A cada limiar `nível * 50`, o nível aumenta. Um ganho grande de XP pode subir vários níveis.
- Ao subir nível: +15 de vida máxima, +2 de força, +1 de defesa e cura para vida máxima.
- O jogo usa `rand()` inicializado uma única vez por `srand(time(NULL))` no começo da execução.

## Compilação e execução

Pré-requisito: compilador C compatível com C99 (GCC ou Clang). Não são usadas bibliotecas externas nem arquivos de persistência.

**macOS e Linux:**

```bash
cd stranger_things_rpg_completo
gcc -std=c99 -Wall -Wextra -pedantic -Iinclude src/*.c -o jogo_mac
./jogo_mac
```

Ou, usando Makefile:

```bash
make
./jogo_mac
```

**Windows (MinGW-w64, terminal PowerShell):**

```powershell
gcc -std=c99 -Wall -Wextra -pedantic -Iinclude src/*.c -o jogo.exe
.\jogo.exe
```

Se o terminal não interpretar sequências ANSI, a limpeza da tela pode aparecer como códigos de controle. Isso não afeta as regras do jogo.

## Organização do código

```text
include/
  personagem.h  # classe, atributos e funções do herói
  monstro.h     # dados dos inimigos
  combate.h     # ações e resultados do combate
  fase.h        # mapa, eventos, missão e progressão
  entrada.h     # leitura segura de entradas
src/
  main.c        # fluxo geral, laço das três fases
  personagem.c  # criação, status, dano, XP e bônus
  monstro.c     # nove inimigos, dano
  combate.c     # turnos, habilidades, defesa e fuga
  fase.c        # cenário, eventos, objetivos, chefe
  entrada.c     # validação de números, Enter e tela
Makefile        # compilação opcional
.gitignore      # ignora executáveis locais
tests/          # testes de lógica
video/          # instruções para adicionar o vídeo
```

`struct` representa personagens, monstros e o tabuleiro. `enum` representa classes, tipos de casas, ações e resultados do combate. Funções recebem ponteiros para alterar dados (`Personagem *`, `Monstro *`, `Tabuleiro *`). A `main` coordena as fases, sem implementar as regras internas de cada subsistema.

## Testes recomendados

1. Digitar nome com espaços (ex.: `Jose Emanuel`).
2. Digitar letra, texto misto e número fora da faixa ao escolher personagem ou ação de combate.
3. Digitar caracteres em vez de apenas Enter para lançar o dado.
4. Verificar coleta de três itens, inclusive ao saltar suas casas; conferir que não são contados duas vezes.
5. Derrotar e fugir de monstros; conferir XP/bônus apenas ao vencer.
6. Usar defesa e cada habilidade especial; verificar limite de dois usos.
7. Derrotar o chefe, liberar fase seguinte, preservar XP/nível e concluir três missões.
8. Testar game over e fim da entrada (Ctrl+D no macOS/Linux).

## Imagens e vídeo

Imagens são opcionais. Se criar imagens com IA, inclua-as na pasta `images/`, identifique a ferramenta e os prompts neste README.

O **vídeo é obrigatório**, deve ter duração máxima de **10 minutos**, gravação de tela e narração do próprio aluno. Mostre: apresentação, compilação no terminal, seleção do personagem, movimentação, combate, bônus, progressão de fases e conclusão. Hospede o vídeo com acesso liberado e preencha o link acima.

## Observação para entrega

Antes da publicação, substitua os campos de nome, matrícula e vídeo. Revise o código e execute o jogo completo para garantir que você compreende e consegue explicar cada função ao professor.
