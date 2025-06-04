#include <stdio.h>

#define TAB_SIZE 10
#define SHIP_SIZE 3

// Função para verificar se o navio cabe dentro do tabuleiro, dado o ponto inicial, tamanho e orientação
int valida_posicao(int linha, int coluna, int tamanho, char orientacao) {
    if (orientacao == 'H') {
        // Verifica se o navio horizontal cabe na linha
        if (coluna + tamanho - 1 < TAB_SIZE)
            return 1; // válido
    } else if (orientacao == 'V') {
        // Verifica se o navio vertical cabe na coluna
        if (linha + tamanho - 1 < TAB_SIZE)
            return 1; // válido
    }
    return 0; // inválido
}

// Função para verificar se há sobreposição com navios já posicionados
int verifica_sobreposicao(int tabuleiro[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, char orientacao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha;
        int c = coluna;
        if (orientacao == 'H') {
            c += i;
        } else { // 'V'
            l += i;
        }
        if (tabuleiro[l][c] == 3) { // Já existe navio nessa posição
            return 1; // há sobreposição
        }
    }
    return 0; // sem sobreposição
}

// Função para posicionar o navio no tabuleiro
void posiciona_navio(int tabuleiro[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, char orientacao) {
    for (int i = 0; i < tamanho; i++) {
        if (orientacao == 'H') {
            tabuleiro[linha][coluna + i] = 3;
        } else { // 'V'
            tabuleiro[linha + i][coluna] = 3;
        }
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
    // Inicializa o tabuleiro com zeros (água)
    int tabuleiro[TAB_SIZE][TAB_SIZE] = {0};

    // Define as coordenadas iniciais e orientação dos navios
    // Navio horizontal
    int nav_h_linha = 2;
    int nav_h_coluna = 3;
    char nav_h_orientacao = 'H';

    // Navio vertical
    int nav_v_linha = 5;
    int nav_v_coluna = 7;
    char nav_v_orientacao = 'V';

    // Valida e posiciona o navio horizontal
    if (!valida_posicao(nav_h_linha, nav_h_coluna, SHIP_SIZE, nav_h_orientacao)) {
        printf("Posição inválida para navio horizontal!\n");
        return 1;
    }
    if (verifica_sobreposicao(tabuleiro, nav_h_linha, nav_h_coluna, SHIP_SIZE, nav_h_orientacao)) {
        printf("Navio horizontal sobrepõe outro navio!\n");
        return 1;
    }
    posiciona_navio(tabuleiro, nav_h_linha, nav_h_coluna, SHIP_SIZE, nav_h_orientacao);

    // Valida e posiciona o navio vertical
    if (!valida_posicao(nav_v_linha, nav_v_coluna, SHIP_SIZE, nav_v_orientacao)) {
        printf("Posição inválida para navio vertical!\n");
        return 1;
    }
    if (verifica_sobreposicao(tabuleiro, nav_v_linha, nav_v_coluna, SHIP_SIZE, nav_v_orientacao)) {
        printf("Navio vertical sobrepõe outro navio!\n");
        return 1;
    }
    posiciona_navio(tabuleiro, nav_v_linha, nav_v_coluna, SHIP_SIZE, nav_v_orientacao);

    // Imprime o tabuleiro final
    imprime_tabuleiro(tabuleiro);

    return 0;
}
