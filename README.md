# Stranger Things: Escape from Hawkins 🎮

## Sobre o projeto

Este projeto foi desenvolvido em linguagem C para a disciplina de Programação do curso de Sistemas de Informação da UFRN.

O jogo é um RPG de tabuleiro inspirado na série *Stranger Things*, executado pelo terminal.

O objetivo é enfrentar criaturas do Mundo Invertido, coletar itens e completar três fases para salvar Hawkins.

## Personagens

O jogador pode escolher entre três personagens:

- **Eleven:** utiliza poderes telecinéticos e possui alta inteligência.
- **Dustin:** utiliza um estilingue e estratégias com rádio.
- **Hopper:** possui maior força e utiliza armas de fogo.

Cada personagem possui atributos, equipamentos e uma habilidade especial.

## Fases do jogo

**Fase 1 — O Desaparecimento em Hawkins**

O jogador precisa encontrar três baterias e derrotar o Demogorgon.

**Fase 2 — A Ameaça do Devorador de Mentes**

O objetivo é coletar três componentes do portal e enfrentar o Devorador de Mentes.

**Fase 3 — O Confronto Final**

O jogador deve reunir três fragmentos de proteção e derrotar Vecna para salvar Hawkins.

Cada fase possui três monstros diferentes e dificuldade crescente.

## Como jogar

O jogo funciona inteiramente pelo terminal.

- Escolha um personagem e digite seu nome.
- Pressione Enter para lançar o dado e avançar pelo tabuleiro.
- Durante o percurso, você poderá encontrar monstros, armadilhas, itens e locais de cura.
- Nos combates, escolha entre atacar, defender, usar uma habilidade especial ou tentar fugir.
- Ao derrotar monstros, você recebe experiência (XP) e bônus para melhorar seus atributos.
- Para avançar de fase, é necessário completar a missão e derrotar o chefe.

O jogo termina quando o personagem perde toda a vida ou quando consegue concluir as três fases.

## Como executar

É necessário ter um compilador C, como GCC ou Clang.

No terminal, dentro da pasta do projeto, compile utilizando:

```bash
gcc -std=c99 -Wall -Wextra -Iinclude src/*.c -o jogo
```

Depois execute:

```bash
./jogo
```

## Organização do projeto

- `src/` — Contém os arquivos com o código do jogo.
- `include/` — Contém as estruturas e declarações das funções.
- `README.md` — Documentação do projeto.
- `Makefile` — Facilita a compilação do jogo.

O código utiliza `struct`, `enum`, ponteiros, vetores e funções para organizar as funcionalidades.

## Vídeo de demonstração

[Assistir ao gameplay] https://drive.google.com/drive/folders/14WhJu75_RsOJ5edh6tpRqkQyVT1d2Afu?usp=drive_link

## Desenvolvedor

**Nome:** José Emanuel da Câmara Silva

**Matrícula:** 20260014730

**Curso:** Bacharelado em Sistemas de Informação — UFRN

**Disciplina:** Programação — 2026.2
