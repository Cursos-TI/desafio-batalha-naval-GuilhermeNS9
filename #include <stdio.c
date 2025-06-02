#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define OCUPADO 3
#define HABILIDADE 5
#define TAMANHO_HABILIDADE 5

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para criar matriz de habilidade em cone
void criarCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Inicializa com 0
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }

    // Cria formato de cone
    int meio = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = meio - i; j <= meio + i; j++) {
            if (j >= 0 && j < TAMANHO_HABILIDADE) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Função para criar matriz de habilidade em cruz
void criarCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em octaedro (losango)
void criarOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int meio = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(meio - i) + abs(meio - j) <= meio) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para sobrepor matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                       int origem_linha, int origem_coluna) {
    int meio = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha = origem_linha + i - meio;
            int coluna = origem_coluna + j - meio;

            // Validação para não ultrapassar limites do tabuleiro
            if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] != OCUPADO) {
                    tabuleiro[linha][coluna] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // ==== POSICIONA UM NAVIO HORIZONTAL COMO EXEMPLO ====
    int linha_hor = 2, coluna_hor = 3;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_hor][coluna_hor + i] = OCUPADO;
    }

    // ==== MATRIZES DE HABILIDADE ====
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // ==== DEFINIÇÃO DE PONTOS DE ORIGEM ====
    int origem_cone_linha = 1, origem_cone_coluna = 1;
    int origem_cruz_linha = 5, origem_cruz_coluna = 5;
    int origem_octaedro_linha = 7, origem_octaedro_coluna = 2;

    // ==== APLICAÇÃO DAS HABILIDADES ====
    aplicarHabilidade(tabuleiro, cone, origem_cone_linha, origem_cone_coluna);
    aplicarHabilidade(tabuleiro, cruz, origem_cruz_linha, origem_cruz_coluna);
    aplicarHabilidade(tabuleiro, octaedro, origem_octaedro_linha, origem_octaedro_coluna);

    // ==== EXIBIÇÃO DO TABULEIRO FINAL ====
    imprimirTabuleiro(tabuleiro);

    return 0;
}
