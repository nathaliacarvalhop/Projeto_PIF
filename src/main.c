#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"
#include "screen.h"
#include "keyboard.h"

#define LINHAS 15
#define COLUNAS 15
#define VIDA_INICIAL 100
#define ATAQUE_JOGADOR 10
#define ATAQUE_MONSTRO 10
#define PONTOS_POR_MONSTRO 50

typedef struct {
    int x, y;
} Posicao;

typedef struct {
    int vida;
    int pontos;
    Posicao posicao;
} Jogador;

typedef struct {
    int vida;
    Posicao posicao;
} Inimigo;

typedef struct {
    Posicao posicao;
    int visivel;
} Saida;

void inicializar_mapa(char mapa[LINHAS][COLUNAS], Jogador *jogador, Inimigo *monstro, Saida *saida) {
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
    mapa[monstro->posicao.x][monstro->posicao.y] = 'M';

    saida->posicao.x = rand() % LINHAS;
    saida->posicao.y = rand() % COLUNAS;
    saida->visivel = 0;
}

void exibir_mapa(char mapa[LINHAS][COLUNAS], Jogador *jogador, Saida *saida) {
    screenClear();

    screenSetColor(CYAN, BLACK);
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == 'J') {
                screenSetColor(GREEN, BLACK);
                printf(" J ");
            } else if (mapa[i][j] == 'M') {
                screenSetColor(RED, BLACK);
                printf(" M ");
            } else if (mapa[i][j] == 'S') {
                screenSetColor(MAGENTA, BLACK);
                printf(" S ");
            } else {
                screenSetColor(WHITE, BLACK);
                printf(" . ");
            }
        }
        printf("\n");
    }

    screenSetColor(CYAN, BLACK);
    printf("\nVida do Jogador: %d \nPontos: %d\n", jogador->vida, jogador->pontos);

    if (saida->visivel) {
        printf("Você encontrou uma saída! (Posição: %d,%d)\n", saida->posicao.x, saida->posicao.y);
    }

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
            printf("Você atacou o monstro (Vida do monstro: %d)\n", monstro->vida);
            if (monstro->vida > 0) {
                jogador->vida -= ATAQUE_MONSTRO;
                printf("O monstro lhe atacou de volta! (Vida do jogador: %d)\n", jogador->vida);
            }
        } else if (escolha == 'e') {
            printf("Você escapou, por pouco...\n");
            break; 
        }

        if (monstro->vida <= 0) {
            printf("Você derrotou o monstro! Ganhou %d pontos!\n", PONTOS_POR_MONSTRO);
            jogador->pontos += PONTOS_POR_MONSTRO;
        }

        if (jogador->vida <= 0) {
            printf("Você foi derrotado!\nGAME OVER\nPontuação final: %d pontos.\n", jogador->pontos);
            exit(0);
        }
    }
}

void verificar_saida(Jogador *jogador, Saida *saida) {
    if (jogador->posicao.x == saida->posicao.x && jogador->posicao.y == saida->posicao.y) {
        saida->visivel = 1;
        printf("Você encontrou uma saída!\n");

        char escolha;
        do {
            printf("Escolha: (f) Fugir, (c) Continuar explorando: ");
            scanf(" %c", &escolha);

            if (escolha == 'f') {
                printf("Você fugiu da dungeon!\n");
                printf("GAME OVER\nPontuação final: %d pontos.\n", jogador->pontos);
                exit(0);
            } else if (escolha == 'c') {
                printf("Você decidiu continuar explorando. A saída se fechou em sua frente...\n");
                saida->visivel = 0;
            } else {
                printf("Escolha incorreta.\n");
            }
        } while (escolha != 'f' && escolha != 'c');
    }
}

int main(int argc, char *argv[]) {
    char mapa[LINHAS][COLUNAS];
    Jogador jogador = {VIDA_INICIAL, 0};
    Inimigo monstro;
    Saida saida;
    srand(time(NULL));

    keyboardInit();
    screenInit(1);
    timerInit(100);

    inicializar_mapa(mapa, &jogador, &monstro, &saida);
    char direcao;

    while (1) {
        exibir_mapa(mapa, &jogador, &saida);
        
        while (!keyhit()) {}
        direcao = readch();

        mover_jogador(mapa, &jogador, direcao);

        if (jogador.posicao.x == monstro.posicao.x && jogador.posicao.y == monstro.posicao.y) {
            combate(&jogador, &monstro);
            inicializar_mapa(mapa, &jogador, &monstro, &saida);
        }

        verificar_saida(&jogador, &saida);

        if (jogador.vida <= 0) {
            printf("Você morreu. \nGAME OVER \nPontuação final: %d pontos.\n", jogador.pontos);
            break;
        }
    }

    return 0;
}
