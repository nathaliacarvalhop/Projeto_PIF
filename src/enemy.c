#include "enemy.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

void spawnEnemy(Enemy *enemy) {
    enemy->health = 50;
    enemy->attack = 5;
    
    enemy->x = rand() % LINHAS;
    enemy->y = rand() % COLUNAS;

    printf("Inimigo apareceu em (%d, %d) com %d de saúde e %d de ataque.\n", enemy->x, enemy->y, enemy->health, enemy->attack);
}
