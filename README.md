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

Dungeon Explorer é um jogo de exploração em modo texto onde o jogador se aventura em uma masmorra cheia de inimigos. O objetivo é sobreviver enquanto procura a saída. O jogador possui um valor de vida e pode sofrer dano ao lutar com inimigos. O jogador possui a decisão de escapar ou enfrentar ao encontrar um inimigo e cada decisão pode afetar sua sobrevivência.

### Elementos Principais da Mecânica:

- **Exploração**: O jogador explora a masmorra e encontra inimigos aleatoriamente.
- **Combate**: Ao encontrar um inimigo, o jogador pode lutar ou tentar fugir. Se optar por lutar, o jogador e o inimigo trocarão ataques, e o jogador pode sofrer danos conforme o ataque do inimigo.
- **Movimentação**: O jogador se move pela masmorra usando os seguintes botões:
  - **w**: Mover para cima.
  - **s**: Mover para baixo.
  - **a**: Mover para a esquerda.
  - **d**: Mover para a direita.

- **Fim de Jogo**: O jogo termina quando o jogador encontra a saída ou quando sua vida chega a zero.

## Executando o jogo

- Direcione a pasta:
```bash
cd ../Projeto_PIF/build
```

- Execute o jogo:
```bash
./DungeonExplorer


