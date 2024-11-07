#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"
#include "screen.h"
#include "keyboard.h"
#include "config.h"
#include "dungeon.h"
#include "enemy.h"

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
    int pontos;
} Jogador;

typedef struct {
    int vida;
    Posicao posicao;
} Inimigo;

void mover_jogador(char mapa[LINHAS][COLUNAS], Jogador *jogador, char direcao) {
    mapa[jogador->posicao.x][jogador->posicao.y] = '.';
    if (direcao == 'w' && jogador->posicao.x > 0) jogador->posicao.x--;
    else if (direcao == 's' && jogador->posicao.x < LINHAS - 1) jogador->posicao.x++;
    else if (direcao == 'a' && jogador->posicao.y > 0) jogador->posicao.y--;
    else if (direcao == 'd' && jogador->posicao.y < COLUNAS - 1) jogador->posicao.y++;

    mapa[jogador->posicao.x][jogador->posicao.y] = 'J';
}

void encontrar_saida(Jogador *jogador, Posicao *saida) {
    if (jogador->posicao.x == saida->x && jogador->posicao.y == saida->y) {
        printf("Você encontrou a saída da masmorra!\n");
        printf("Deseja sair agora? (s para sim, n para não): ");
        char escolha;
        scanf(" %c", &escolha);
        if (escolha == 's') {
            printf("Você saiu da masmorra com %d pontos! Parabéns!\n", jogador->pontos);
            exit(0);
        } else {
            printf("Você decidiu continuar na masmorra...\n");
        }
    }
}

void inicializar_mapa(char mapa[LINHAS][COLUNAS], Jogador *jogador, Inimigo *monstro, Posicao *saida) {
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
    monstro->vida = 30;

    saida->x = rand() % LINHAS;
    saida->y = rand() % COLUNAS;
    while ((saida->x == jogador->posicao.x && saida->y == jogador->posicao.y) || 
           (saida->x == monstro->posicao.x && saida->y == monstro->posicao.y)) {
        saida->x = rand() % LINHAS;
        saida->y = rand() % COLUNAS;
    }
}

void exibir_mapa(char mapa[LINHAS][COLUNAS], Jogador *jogador) {
    screenClear();
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++)
            printf("%c ", mapa[i][j]);
        printf("\n");
    }
    printf("Vida do Jogador: %d\n", jogador->vida);
    printf("Pontos: %d\n", jogador->pontos);
    screenUpdate();
}

int main(int argc, char *argv[]) {
    char mapa[LINHAS][COLUNAS];
    Jogador jogador = {VIDA_INICIAL, 0};
    Inimigo monstro;
    Posicao saida;
    srand(time(NULL));

    keyboardInit();
    screenInit(1);
    timerInit(100);

    inicializar_mapa(mapa, &jogador, &monstro, &saida);
    char direcao;

    while (1) {
        exibir_mapa(mapa, &jogador);
        printf("Mover (w/a/s/d): ");

        while (!keyhit()) {}
        direcao = readch();

        mover_jogador(mapa, &jogador, direcao);

        if (jogador.posicao.x == monstro.posicao.x && jogador.posicao.y == monstro.posicao.y) {
            combate(&jogador, &monstro);
            inicializar_mapa(mapa, &jogador, &monstro, &saida);
        }

        encontrar_saida(&jogador, &saida);

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
