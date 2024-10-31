#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 10
#define COLUNAS 10

typedef struct {
    int x, y;
} Posicao;

void inicializar_mapa(char mapa[LINHAS][COLUNAS], Posicao *jogador, Posicao *monstro) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            mapa[i][j] = '.';

    jogador->x = rand() % LINHAS;
    jogador->y = rand() % COLUNAS;
    mapa[jogador->x][jogador->y] = 'J';

    monstro->x = rand() % LINHAS;
    monstro->y = rand() % COLUNAS;
    while (monstro->x == jogador->x && monstro->y == jogador->y) {
        monstro->x = rand() % LINHAS;
        monstro->y = rand() % COLUNAS;
    }
    mapa[monstro->x][monstro->y] = 'M';
}

void exibir_mapa(char mapa[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++)
            printf("%c ", mapa[i][j]);
        printf("\n");
    }
}

void mover_jogador(char mapa[LINHAS][COLUNAS], Posicao *jogador, char direcao) {
    mapa[jogador->x][jogador->y] = '.';
    if (direcao == 'w' && jogador->x > 0) jogador->x--;
    else if (direcao == 's' && jogador->x < LINHAS - 1) jogador->x++;
    else if (direcao == 'a' && jogador->y > 0) jogador->y--;
    else if (direcao == 'd' && jogador->y < COLUNAS - 1) jogador->y++;
    
    mapa[jogador->x][jogador->y] = 'J';
}

int main() {
    char mapa[LINHAS][COLUNAS];
    Posicao jogador, monstro;
    srand(time(NULL));

    inicializar_mapa(mapa, &jogador, &monstro);
    char direcao;

    while (1) {
        exibir_mapa(mapa);
        printf("Mover (w/a/s/d): ");
        scanf(" %c", &direcao);
        
        mover_jogador(mapa, &jogador, direcao);
        
        if (jogador.x == monstro.x && jogador.y == monstro.y) {
            printf("Você encontrou o monstro!\n");
            inicializar_mapa(mapa, &jogador, &monstro);  // Reposiciona o monstro
        }
    }

    return 0;
}