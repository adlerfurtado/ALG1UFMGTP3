#include "tabuleiro.hpp"
#include <iostream>

// Lê o tabuleiro da entrada padrão
Tabuleiro Tabuleiro::lerEntrada() {
    Tabuleiro t;
    std::cin >> t.N >> t.M >> t.K;

    int encontrados = 0;
    for (int i = 0; i < t.N; i++) {
        std::cin >> t.matriz[i];
        for (int j = 0; j < t.M; j++) {
            if (t.matriz[i][j] == 'R') {
                t.rainha = {i, j};
            } else if (t.matriz[i][j] == 'P') {
                t.peoes[encontrados++] = {i, j};
            }
        }
    }

    t.K = encontrados; // Garante que K está correto mesmo que input seja inconsistente
    return t;
}

// Verifica se posição está dentro dos limites do tabuleiro
bool Tabuleiro::dentroDosLimites(int x, int y) const {
    return x >= 0 && x < N && y >= 0 && y < M;
}

// Verifica se a célula pode ser acessada (não é bloqueada)
bool Tabuleiro::celulaLivre(int x, int y) const {
    return dentroDosLimites(x, y) && matriz[x][y] != '-';
}
