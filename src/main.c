#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"
#include "screen.h"
#include "keyboard.h"
#include "config.h"

#define LINHAS 10
#define COLUNAS 10
#define VIDA_INICIAL 100
#define ATAQUE_JOGADOR 10
#define ATAQUE_MONSTRO 10

typedef struct {
    int x, y;
} Posicao;

typedef struct {
    int vida;
    Posicao posicao;
} Jogador;

typedef struct {
    int vida;
    Posicao posicao;
} Inimigo;

void inicializar_mapa(char mapa[LINHAS][COLUNAS], Jogador *jogador, Inimigo *monstro) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            mapa[i][j] = '.';

    jogador->posicao.x = rand() % LINHAS;
    jogador->posicao.y = rand() % COLUNAS;
    mapa[jogador->posicao.x][jogador->posicao.y] = 'J';

    monstro->posicao.x = rand() % LINHAS;
    monstro->posicao.y = rand() % COLUNAS;
    while (monstro->posicao.x == jogador->posicao.x && monstro->posicao.y == jogador->posicao.y) {
        monstro->posicao.x = rand() % LINHAS;
        monstro->posicao.y = rand() % COLUNAS;
    }
    monstro->vida = 30;  // Exemplo de vida do monstro
    mapa[monstro->posicao.x][monstro->posicao.y] = 'M';
}

void exibir_mapa(char mapa[LINHAS][COLUNAS], Jogador *jogador) {
    screenClear();
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++)
            printf("%c ", mapa[i][j]);
        printf("\n");
    }
    printf("Vida do Jogador: %d\n", jogador->vida);
    screenUpdate();
}

void mover_jogador(char mapa[LINHAS][COLUNAS], Jogador *jogador, char direcao) {
    mapa[jogador->posicao.x][jogador->posicao.y] = '.';
    if (direcao == 'w' && jogador->posicao.x > 0) jogador->posicao.x--;
    else if (direcao == 's' && jogador->posicao.x < LINHAS - 1) jogador->posicao.x++;
    else if (direcao == 'a' && jogador->posicao.y > 0) jogador->posicao.y--;
    else if (direcao == 'd' && jogador->posicao.y < COLUNAS - 1) jogador->posicao.y++;

    mapa[jogador->posicao.x][jogador->posicao.y] = 'J';
}

void combate(Jogador *jogador, Inimigo *monstro) {
    while (jogador->vida > 0 && monstro->vida > 0) {
        printf("Você encontrou um monstro! (Vida do monstro: %d)\n", monstro->vida);
        printf("Escolha: (f) Lutar, (e) Escapar: ");
        char escolha;
        scanf(" %c", &escolha);

        if (escolha == 'f') {
            monstro->vida -= ATAQUE_JOGADOR;
            printf("Você atacou o monstro! (Vida do monstro: %d)\n", monstro->vida);
            if (monstro->vida > 0) {
                jogador->vida -= ATAQUE_MONSTRO;
                printf("O monstro atacou você! (Vida do jogador: %d)\n", jogador->vida);
            }
        } else if (escolha == 'e') {
            printf("Você tentou escapar!\n");
            break; // Sai do combate
        }

        if (jogador->vida <= 0) {
            printf("Você foi derrotado!\n");
            exit(0);
        }
    }
}

int main(int argc, char *argv[]) {
    char mapa[LINHAS][COLUNAS];
    Jogador jogador = {VIDA_INICIAL};
    Inimigo monstro;
    srand(time(NULL));

    keyboardInit();
    screenInit(1);
    timerInit(100);

    inicializar_mapa(mapa, &jogador, &monstro);
    char direcao;

    while (1) {
        exibir_mapa(mapa, &jogador);
        printf("Mover (w/a/s/d): ");

        while (!keyhit()) {}
        direcao = readch();
        
        mover_jogador(mapa, &jogador, direcao);

        if (jogador.posicao.x == monstro.posicao.x && jogador.posicao.y == monstro.posicao.y) {
            combate(&jogador, &monstro);
            inicializar_mapa(mapa, &jogador, &monstro);
        }

        if (jogador.vida <= 0) {
            printf("Você morreu. Fim do jogo!\n");
            break;
        }
    }

    timerDestroy();
    keyboardDestroy();
    screenDestroy();

    return 0;
}
