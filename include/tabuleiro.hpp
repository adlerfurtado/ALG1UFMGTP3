#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP

#include <string>

// Representa um ponto no tabuleiro
struct Ponto {
    int x, y;

    bool operator==(const Ponto& outro) const {
        return x == outro.x && y == outro.y;
    }
};

const int MAX_N = 100;
const int MAX_PEOES = 18;
const int MAX_MASK = 1 << MAX_PEOES;

// Representa o tabuleiro e suas entidades
struct Tabuleiro {
    int N, M, K; // Dimensões e número de peões
    std::string matriz[MAX_N];
    Ponto rainha;
    Ponto peoes[MAX_PEOES];

    static Tabuleiro lerEntrada();
    bool dentroDosLimites(int x, int y) const;
    bool celulaLivre(int x, int y) const;
};

#endif
