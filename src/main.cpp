#include "tabuleiro.hpp"
#include "solucao_exata.hpp"
#include "solucao_aproximada.hpp"
#include <iostream>

int main() {
    Tabuleiro tabuleiro = Tabuleiro::lerEntrada();

    int respostaExata = resolverCaminhoOtimo(tabuleiro);
    //std::cout << "Exato: ";
    std::cout << respostaExata << std::endl;

    //int respostaAproximada = resolverAproximado(tabuleiro);
    //std::cout << "Aproximado: ";
    //std::cout << respostaAproximada << std::endl;

    return 0;
}
