#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int health;
    int attack;
} Player;

void initializePlayer(Player *player);
void takeDamage(Player *player, int damage);

#endif