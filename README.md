# Dungeon Explorers
Projeto para a disciplina de Programação Imperativa e Funcional.

Membros do Grupo:
- Nathália Carvalho - @nathaliacarvalhop
- Lilian Beckman    - @lilibeckman
- Carlos Cavalcante - @c4rlos13

Disciplina: Programação Imperativa e Funcional - 2024.2.
Instituição de ensino: CESAR School.

## Estrutura do Projeto

- **src/**: Código-fonte do jogo.
- **include/**: Arquivos de cabeçalho.
- **build/**: Arquivos gerados pela compilação.

## Mecânica do Jogo

Dungeon Explorer é um jogo de exploração em modo texto onde o jogador se aventura em uma masmorra cheia de inimigos. O objetivo é sobreviver enquanto explora e tenta encontrar a saída. O jogador tem um valor de vida e ataque e pode sofrer danos ao encontrar inimigos. A cada encontro, o jogador pode decidir enfrentar ou tentar escapar. Cada decisão afeta o progresso e a sobrevivência do jogador.

### Elementos Principais da Mecânica:

- **Exploração**: O jogador explora a masmorra e encontra inimigos aleatoriamente.
- **Combate**: Ao encontrar um inimigo, o jogador pode lutar ou tentar fugir. Se optar por lutar, o jogador e o inimigo trocarão ataques, e o jogador pode sofrer danos conforme o ataque do inimigo.
- **Movimentação**: O jogador se move pela masmorra usando os seguintes botões:
  - **w**: Mover para cima.
  - **s**: Mover para baixo.
  - **a**: Mover para a esquerda.
  - **d**: Mover para a direita.

- **Fim de Jogo**: O jogo termina quando o jogador encontra a saída ou quando sua vida chega a zero.

## Compilação e Execução

Compile o projeto com o comando:

```bash
gcc src/*.c -o DungeonExplorer

