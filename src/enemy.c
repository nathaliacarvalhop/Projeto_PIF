#include "enemy.h"
#include <stdio.h>

void spawnEnemy(Enemy *enemy) {
    enemy->health = 50;
    enemy->attack = 5;
    printf("Inimigo apareceu com %d de saúde e %d de ataque.\n", enemy->health, enemy->attack);
}