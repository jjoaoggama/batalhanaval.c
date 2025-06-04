#include <stdio.h>
#include <stdlib.h>  // Para abs()

#define TAB_SIZE 10
#define SHIP_SIZE 3
#define HABILITY_SIZE 5

void inicializa_tabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    for (int i = 0; i < TAB_SIZE; i++)
        for (int j = 0; j < TAB_SIZE; j++)
            tabuleiro[i][j] = 0;
}

void posiciona_navios(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    // Navio horizontal tamanho 3
    tabuleiro[1][1] = 3;
    tabuleiro[1][2] = 3;
    tabuleiro[1][3] = 3;

    // Navio vertical tamanho 3
    tabuleiro[4][6] = 3;
    tabuleiro[5][6] = 3;
    tabuleiro[6][6] = 3;
}

void gera_cone(int cone[HABILITY_SIZE][HABILITY_SIZE]) {
    for (int i = 0; i < HABILITY_SIZE; i++)
        for (int j = 0; j < HABILITY_SIZE; j++)
            cone[i][j] = 0;

    cone[0][2] = 1;
    cone[1][1] = 1; cone[1][2] = 1; cone[1][3] = 1;
    for (int j = 0; j < HABILITY_SIZE; j++)
        cone[2][j] = 1;
}

void gera_cruz(int cruz[HABILITY_SIZE][HABILITY_SIZE]) {
    for (int i = 0; i < HABILITY_SIZE; i++)
        for (int j = 0; j < HABILITY_SIZE; j++)
            cruz[i][j] = (i == 2 || j == 2) ? 1 : 0;
}

void gera_octaedro(int octaedro[HABILITY_SIZE][HABILITY_SIZE]) {
    for (int i = 0; i < HABILITY_SIZE; i++) {
        for (int j = 0; j < HABILITY_SIZE; j++) {
            int dist = abs(i - 2) + abs(j - 2);
            octaedro[i][j] = (dist <= 2) ? 1 : 0;
        }
    }
}

void aplica_habilidade(int tabuleiro[TAB_SIZE][TAB_SIZE],
                       int habilidade[HABILITY_SIZE][HABILITY_SIZE],
                       int origem_linha, int origem_coluna) {
    int offset = HABILITY_SIZE / 2;
    for (int i = 0; i < HABILITY_SIZE; i++) {
        for (int j = 0; j < HABILITY_SIZE; j++) {
            if (habilidade[i][j] == 1) {
                int linha = origem_linha - offset + i;
                int coluna = origem_coluna - offset + j;
                if (linha >= 0 && linha < TAB_SIZE && coluna >= 0 && coluna < TAB_SIZE) {
                    if (tabuleiro[linha][coluna] == 0)
                        tabuleiro[linha][coluna] = 5;
                }
            }
        }
    }
}

void imprime_tabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro ( . = agua, N = navio, * = habilidade ):\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            char c;
            switch (tabuleiro[i][j]) {
                case 0: c = '.'; break;
                case 3: c = 'N'; break;
                case 5: c = '*'; break;
                default: c = '?'; break;
            }
            printf("%c ", c);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE];

    inicializa_tabuleiro(tabuleiro);
    posiciona_navios(tabuleiro);

    int cone[HABILITY_SIZE][HABILITY_SIZE];
    int cruz[HABILITY_SIZE][HABILITY_SIZE];
    int octaedro[HABILITY_SIZE][HABILITY_SIZE];

    gera_cone(cone);
    gera_cruz(cruz);
    gera_octaedro(octaedro);

    // Posicionamento das habilidades
    aplica_habilidade(tabuleiro, cone, 2, 2);
    aplica_habilidade(tabuleiro, cruz, 7, 7);
    aplica_habilidade(tabuleiro, octaedro, 5, 4);

    imprime_tabuleiro(tabuleiro);

    return 0;
}

