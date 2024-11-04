#ifndef DUNGEON_H
#define DUNGEON_H

#include "player.h"
#include "enemy.h"

#define LINHAS 10
#define COLUNAS 10
#define MAX_INIMIGOS 5

typedef struct {
    char mapa[LINHAS][COLUNAS];
    Player jogador;
    Enemy inimigos[MAX_INIMIGOS];
    int num_inimigos;
} Dungeon;

void initializeDungeon(Dungeon *dungeon);
void moverJogador(Dungeon *dungeon, char direcao);
int verificarEncontro(Dungeon *dungeon);

#endif
