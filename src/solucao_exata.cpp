#include "tabuleiro.hpp"
#include <queue>
#include <vector>
#include <iostream>
#include <string>

const int INF = 1000000000;

// Direções de movimento da rainha (8 direções)
const int dx[8] = {-1,-1,-1, 0, 1, 1, 1, 0};
const int dy[8] = {-1, 0, 1, 1, 1, 0,-1,-1};

int matrizDistancias[MAX_N][MAX_N];

// Converte uma máscara em string binária (para debug)
std::string paraBinario(int mascara, int bits = 10) {
    std::string resultado(bits, '0');
    for (int i = bits - 1; i >= 0; --i)
        if (mascara & (1 << i))
            resultado[bits - 1 - i] = '1';
    return resultado;
}

// Executa uma BFS a partir de uma posição, simulando movimento de rainha
void calcularDistanciasBFS(const Tabuleiro& t, Ponto origem, int out[MAX_N][MAX_N]) {
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
                    if (t.matriz[nx][ny] == 'P') break; // para de avançar se achar um peão
                }
                nx += dx[dir];
                ny += dy[dir];
            }
        }
    }
}

int resolverCaminhoOtimo(const Tabuleiro& t) {
    int totalPeoes = t.K;

    // Junta a posição da rainha e dos peões em um único vetor
    std::vector<Ponto> posicoes;
    posicoes.push_back(t.rainha);
    for (int i = 0; i < totalPeoes; i++)
        posicoes.push_back(t.peoes[i]);

    // dist[i][j] = menor distância de i para j, considerando movimentos de rainha
    std::vector<std::vector<int>> dist(totalPeoes + 1, std::vector<int>(totalPeoes + 1, INF));
    for (int i = 0; i <= totalPeoes; ++i) {
        calcularDistanciasBFS(t, posicoes[i], matrizDistancias);
        for (int j = 0; j <= totalPeoes; ++j) {
            int d = matrizDistancias[posicoes[j].x][posicoes[j].y];
            dist[i][j] = (d == -1) ? INF : d;
        }
    }

    // dp[mask][i] = custo mínimo para capturar os peões do mask, terminando na posição i
    std::vector<std::vector<int>> dp(1 << totalPeoes, std::vector<int>(totalPeoes + 1, INF));
    dp[0][0] = 0; // Começamos na posição da rainha sem nenhum peão capturado

    for (int mask = 0; mask < (1 << totalPeoes); ++mask) {
        for (int posAtual = 0; posAtual <= totalPeoes; ++posAtual) {
            if (dp[mask][posAtual] >= INF) continue;
            for (int proxPeao = 1; proxPeao <= totalPeoes; ++proxPeao) {
                if (mask & (1 << (proxPeao - 1))) continue; // já capturado
                int novoMask = mask | (1 << (proxPeao - 1));
                int novoCusto = dp[mask][posAtual] + dist[posAtual][proxPeao];
                if (novoCusto < dp[novoMask][proxPeao]) {
                    dp[novoMask][proxPeao] = novoCusto;
                }
            }
        }
    }

    // Pega o menor custo final entre todas as possibilidades
    int respostaFinal = INF;
    for (int i = 1; i <= totalPeoes; ++i)
        if (dp[(1 << totalPeoes) - 1][i] < respostaFinal)
            respostaFinal = dp[(1 << totalPeoes) - 1][i];

    return (respostaFinal >= INF) ? -1 : respostaFinal;
}
