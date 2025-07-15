#include "tabuleiro.hpp"
#include "solucao_exata.hpp"
#include "solucao_aproximada.hpp"
#include <iostream>
#include <chrono>
using namespace std::chrono;

int main() {
    Tabuleiro tabuleiro = Tabuleiro::lerEntrada();

    auto inicioExata = high_resolution_clock::now();
    int respostaExata = resolverCaminhoOtimo(tabuleiro);
    auto fimExata = high_resolution_clock::now();
    std::cout << "Exato: " << respostaExata << std::endl;
    std::cout << "Tempo (exato): " 
              << duration_cast<milliseconds>(fimExata - inicioExata).count() 
              << " ms" << std::endl;

    auto inicioAprox = high_resolution_clock::now();
    int respostaAproximada = resolverAproximado(tabuleiro);
    auto fimAprox = high_resolution_clock::now();
    std::cout << "Aproximado: " << respostaAproximada << std::endl;
    std::cout << "Tempo (aproximado): " 
              << duration_cast<milliseconds>(fimAprox - inicioAprox).count() 
              << " ms" << std::endl;

    return 0;
}