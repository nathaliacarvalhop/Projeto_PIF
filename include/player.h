#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int health;
    int attack;
    int x;
    int y;
} Player;

void initializePlayer(Player *player);
void takeDamage(Player *player, int damage);

#endif
