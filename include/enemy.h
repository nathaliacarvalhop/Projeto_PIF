#ifndef ENEMY_H
#define ENEMY_H

typedef struct {
    int health;
    int attack;
    int x;
    int y;
} Enemy;

void spawnEnemy(Enemy *enemy);

#endif
