#include "dungeon.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

void initializeDungeon(Dungeon *dungeon) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            dungeon->mapa[i][j] = '.';

    dungeon->jogador.health = 100;
    dungeon->jogador.attack = 10;

    dungeon->num_inimigos = rand() % MAX_INIMIGOS;
    for (int i = 0; i < dungeon->num_inimigos; i++) {
        spawnEnemy(&dungeon->inimigos[i]);
    }
}

void moverJogador(Dungeon *dungeon, char direcao) {
    int novoX = dungeon->jogador.x;
    int novoY = dungeon->jogador.y;

    if (direcao == 'w' && novoX > 0) novoX--;
    else if (direcao == 's' && novoX < LINHAS - 1) novoX++;
    else if (direcao == 'a' && novoY > 0) novoY--;
    else if (direcao == 'd' && novoY < COLUNAS - 1) novoY++;

    dungeon->jogador.x = novoX;
    dungeon->jogador.y = novoY;
}

int verificarEncontro(Dungeon *dungeon) {
    for (int i = 0; i < dungeon->num_inimigos; i++) {
        if (dungeon->jogador.x == dungeon->inimigos[i].x &&
            dungeon->jogador.y == dungeon->inimigos[i].y) {
            return 1;
        }
    }
    return 0;
}
