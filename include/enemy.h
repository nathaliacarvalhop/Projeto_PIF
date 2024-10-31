#ifndef ENEMY_H
#define ENEMY_H

typedef struct {
    int health;
    int attack;
} Enemy;

void spawnEnemy(Enemy *enemy);

#endif