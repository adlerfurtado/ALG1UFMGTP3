#include "tabuleiro.hpp"
#include "solucao_aproximada.hpp"
#include "solucao_exata.hpp"
#include <queue>
#include <vector>
#include <iostream>
#include <string>

const int INF = 1000000000;
const int dx[8] = {-1,-1,-1, 0, 1, 1, 1, 0};
const int dy[8] = {-1, 0, 1, 1, 1, 0,-1,-1};

// Calcula BFS a partir da origem, considerando movimentos de rainha
void bfs(const Tabuleiro& t, Ponto origem, int out[MAX_N][MAX_N]) {
    for (int i = 0; i < MAX_N; ++i)
        for (int j = 0; j < MAX_N; ++j)
            out[i][j] = -1;

    std::queue<Ponto> fila;
    fila.push(origem);
    out[origem.x][origem.y] = 0;

    while (!fila.empty()) {
        Ponto atual = fila.front(); fila.pop();
        for (int dir = 0; dir < 8; ++dir) {
            int nx = atual.x + dx[dir];
            int ny = atual.y + dy[dir];
            while (t.celulaLivre(nx, ny)) {
                if (out[nx][ny] == -1) {
                    out[nx][ny] = out[atual.x][atual.y] + 1;
                    fila.push({nx, ny});
                    if (t.matriz[nx][ny] == 'P') break; // para de atravessar peões
                }
                nx += dx[dir];
                ny += dy[dir];
            }
        }
    }
}

// Algoritmo aproximado: captura peões escolhendo o mais próximo a cada passo
int resolverAproximado(const Tabuleiro& tabuleiro) {
    std::vector<bool> capturado(tabuleiro.K, false);
    Ponto posicaoAtual = tabuleiro.rainha;
    int movimentosTotais = 0;

    for (int capturados = 0; capturados < tabuleiro.K; ++capturados) {
        int distancias[MAX_N][MAX_N];
        bfs(tabuleiro, posicaoAtual, distancias);

        int maisProximo = -1;
        int menorCusto = INF;

        for (int i = 0; i < tabuleiro.K; ++i) {
            if (!capturado[i]) {
                Ponto alvo = tabuleiro.peoes[i];
                int d = distancias[alvo.x][alvo.y];
                if (d != -1 && d < menorCusto) {
                    menorCusto = d;
                    maisProximo = i;
                }
            }
        }

        if (maisProximo == -1) return -1; // algum peão é inacessível

        capturado[maisProximo] = true;
        movimentosTotais += menorCusto;
        posicaoAtual = tabuleiro.peoes[maisProximo];
    }

    return movimentosTotais;
}