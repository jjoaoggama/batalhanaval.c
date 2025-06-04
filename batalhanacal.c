#include <stdio.h>

#define TAB_SIZE 10
#define SHIP_SIZE 3

// Função para verificar se o navio cabe dentro do tabuleiro, dado o ponto inicial, tamanho e orientação
// Orientações possíveis: 'H' (horizontal), 'V' (vertical), 'D' (diagonal principal), 'A' (diagonal anti)
// Para diagonal principal, linha e coluna aumentam simultaneamente
// Para diagonal anti, linha aumenta e coluna diminui simultaneamente
int valida_posicao(int linha, int coluna, int tamanho, char orientacao) {
    switch (orientacao) {
        case 'H':
            return (coluna + tamanho - 1 < TAB_SIZE);
        case 'V':
            return (linha + tamanho - 1 < TAB_SIZE);
        case 'D': // diagonal principal (↘)
            return (linha + tamanho - 1 < TAB_SIZE && coluna + tamanho - 1 < TAB_SIZE);
        case 'A': // diagonal anti (↙)
            return (linha + tamanho - 1 < TAB_SIZE && coluna - (tamanho - 1) >= 0);
        default:
            return 0;
    }
}

// Função para verificar sobreposição, incluindo diagonais
int verifica_sobreposicao(int tabuleiro[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, char orientacao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha;
        int c = coluna;
        switch (orientacao) {
            case 'H': c += i; break;
            case 'V': l += i; break;
            case 'D': l += i; c += i; break;
            case 'A': l += i; c -= i; break;
        }
        if (tabuleiro[l][c] == 3) {
            return 1; // sobreposição detectada
        }
    }
    return 0; // sem sobreposição
}

// Função para posicionar o navio no tabuleiro, incluindo diagonais
void posiciona_navio(int tabuleiro[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, char orientacao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha;
        int c = coluna;
        switch (orientacao) {
            case 'H': c += i; break;
            case 'V': l += i; break;
            case 'D': l += i; c += i; break;
            case 'A': l += i; c -= i; break;
        }
        tabuleiro[l][c] = 3;
    }
}

// Função para imprimir o tabuleiro
void imprime_tabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro Batalha Naval (0 = água, 3 = navio):\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE] = {0};

    // Definição dos navios - tamanho fixo 3
    // Dois navios horizontais ou verticais:
    int h1_l = 1, h1_c = 1;  char h1_o = 'H';
    int v1_l = 4, v1_c = 6;  char v1_o = 'V';

    // Dois navios diagonais:
    // diagonal principal (↘)
    int d1_l = 6, d1_c = 1;  char d1_o = 'D';
    // diagonal anti (↙)
    int a1_l = 0, a1_c = 9;  char a1_o = 'A';

    // Posicionar navio horizontal 1
    if (!valida_posicao(h1_l, h1_c, SHIP_SIZE, h1_o) || 
        verifica_sobreposicao(tabuleiro, h1_l, h1_c, SHIP_SIZE, h1_o)) {
        printf("Erro ao posicionar navio horizontal 1.\n");
        return 1;
    }
    posiciona_navio(tabuleiro, h1_l, h1_c, SHIP_SIZE, h1_o);

    // Posicionar navio vertical 1
    if (!valida_posicao(v1_l, v1_c, SHIP_SIZE, v1_o) || 
        verifica_sobreposicao(tabuleiro, v1_l, v1_c, SHIP_SIZE, v1_o)) {
        printf("Erro ao posicionar navio vertical 1.\n");
        return 1;
    }
    posiciona_navio(tabuleiro, v1_l, v1_c, SHIP_SIZE, v1_o);

    // Posicionar navio diagonal principal
    if (!valida_posicao(d1_l, d1_c, SHIP_SIZE, d1_o) || 
        verifica_sobreposicao(tabuleiro, d1_l, d1_c, SHIP_SIZE, d1_o)) {
        printf("Erro ao posicionar navio diagonal principal.\n");
        return 1;
    }
    posiciona_navio(tabuleiro, d1_l, d1_c, SHIP_SIZE, d1_o);

    // Posicionar navio diagonal anti
    if (!valida_posicao(a1_l, a1_c, SHIP_SIZE, a1_o) || 
        verifica_sobreposicao(tabuleiro, a1_l, a1_c, SHIP_SIZE, a1_o)) {
        printf("Erro ao posicionar navio diagonal anti.\n");
        return 1;
    }
    posiciona_navio(tabuleiro, a1_l, a1_c, SHIP_SIZE, a1_o);

    // Exibir o tabuleiro final
    imprime_tabuleiro(tabuleiro);

    return 0;
}
