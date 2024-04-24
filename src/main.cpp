#include <iostream>
#include <vector>
#include "util.h"


/// @brief Descobre a combinação de 90 números que farão as cartelas ganharem.
/// @param cartelas Vetor de cartelas de bingo.
/// @param cartelaA Cartela Alvo A.
/// @param cartelaB Cartela Alvo B.
/// @param cartelaC Cartela Alvo C.
/// @return std::vector<int> A combinação de 90 números que farão as cartelas ganharem.
std::vector<int>
algoritmoFodaAqui([[maybe_unused]]std::vector<Card> &cartelas,
                  [[maybe_unused]]int cartelaA,
                  [[maybe_unused]]int cartelaB,
                  [[maybe_unused]]int cartelaC)
{
    // TODO: Implementar algoritmo foda aqui.

    return generateUniqueRandomNumbers(1, 90, 90); // delete-me!
}


int main(void) {

    // 10 cartelas de bingo com 15 números aleatórios únicos.
    std::vector<Card> cards;
    for (int i = 0; i < 10; i++) {
        cards.push_back(Card(i+100, generateUniqueRandomNumbers(1, 90, 15)));
    }

    // Cartelas alvo.
    cards.push_back(Card(333, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15}));
    cards.push_back(Card(666, {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}));
    cards.push_back(Card(999, {31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45}));

    // 90 números de bingo.
    std::vector<int> bolas = algoritmoFodaAqui(cards, 333, 666, 999);

    // Realiza o sorteio do bingo.
    BingoGame game(cards, 45);
    game.play(bolas);

    std::cout << "\nVencedores do primeiro round: " << "\n";
    for (const auto& card : game.getFirstWinners()) {
        card.print();  // deveria ser cartela 333
    }

    std::cout << "Vencedores do segundo round: " << "\n";
    for (const auto& card : game.getSecondWinners()) {
        card.print();  // deveria ser cartela 666
    }

    std::cout << "Vencedores do terceiro round: " << "\n";
    for (const auto& card : game.getThirdWinners()) {
        card.print(); // deveria ser cartela 999
    }

    return 0;
}