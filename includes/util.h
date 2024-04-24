#pragma once
#include <vector>

/**
  @brief Gera um vetor de números inteiros aleatórios dentro de
 *       um determinado intervalo.
 * 
 * Esta função gera um vetor de números inteiros aleatórios dentro do intervalo [A, B].
 * O tamanho do vetor é determinado pelo parâmetro N.
 * 
 * @param A O limite inferior do intervalo.
 * @param B O limite superior do intervalo.
 * @param N O número de números inteiros aleatórios a serem gerados.
 * @return std::vector<int> O vetor de números inteiros aleatórios.
 *
 * @warning Esta função é insegura e não deve ser usada em aplicações de produção
 *          devido ao risco de previsibilidade dos números gerados e possíveis
 *          implicações de segurança.
 */
std::vector<int> generateRandomNumbers(int A, int B, int N);

/**
  @brief Gera um vetor de números inteiros (não repetidos) aleatórios dentro de
 *       um determinado intervalo.
 * 
 * Esta função gera um vetor de números inteiros aleatórios dentro do intervalo [A, B].
 * O tamanho do vetor é determinado pelo parâmetro N.
 * 
 * @param A O limite inferior do intervalo.
 * @param B O limite superior do intervalo.
 * @param N O número de números inteiros aleatórios a serem gerados.
 * @return std::vector<int> O vetor de números inteiros aleatórios.
 *
 * @warning Esta função é insegura e não deve ser usada em aplicações de produção
 *          devido ao risco de previsibilidade dos números gerados e possíveis
 *          implicações de segurança.
 */
std::vector<int> generateUniqueRandomNumbers(int A, int B, int N);

/**
 * @enum WinnerType
 * @brief Enumera os tipos de vencedores no jogo.
 *
 * Enumera vários estados de vitória dentro do jogo, onde cada tipo representa uma rodada específica ou estado.
 */
enum class WinnerType {
    INVALID = -1, ///< Tipo de vencedor inválido, geralmente usado para tratamento de erros.
    NONE,         ///< Sem vencedor ou estado não inicializado.
    FIRST,        ///< Representa o vencedor da primeira rodada.
    SECOND,       ///< Representa o vencedor da segunda rodada.
    THIRD         ///< Representa o vencedor da terceira rodada.
};

/**
 * @brief Converte um enum WinnerType para o correspondente número inteiro da rodada.
 * @param round A rodada como WinnerType.
 * @return int O número inteiro da rodada correspondente ao WinnerType.
 */
int getIntRound(WinnerType round);

/**
 * @brief Converte um valor inteiro para um correspondente WinnerType.
 * @param value O valor inteiro a ser convertido.
 * @return WinnerType O WinnerType correspondente ao valor inteiro.
 */
WinnerType getWinnerType(int value);

/**
 * @class Card
 * @brief Representa um cartela no jogo de bingo.
 *
 * Esta classe armazena o estado de um cartela de bingo, incluindo seu ID, sequência de números, máscara de números marcados e utilidades para manipular e consultar seu estado.
 */
class Card {
public:
    /**
     * @brief Constrói um cartela com um ID e uma sequência de números dados.
     * @param cardId O identificador único do cartela.
     * @param cardSequence A sequência de números no cartela de bingo.
     */
    Card(unsigned int cardId, const std::vector<int>& cardSequence);

    /**
     * @brief Recupera a sequência de números no cartela.
     * @return std::vector<int> A sequência de números.
     */
    std::vector<int> getSequence() const;

    /**
     * @brief Recupera a máscara de números marcados.
     * @return std::vector<bool> A máscara indicando quais números foram marcados.
     */
    std::vector<bool> getMask() const;

    /**
     * @brief Obtém os números restantes com base na rodada atual.
     * @param round A rodada para a qual obter os números restantes.
     * @return std::vector<int> A lista de números restantes.
     */
    std::vector<int> getRemainingBasedOnRound(WinnerType round) const;

    /**
     * @brief Obtém o identificador único do cartela.
     * @return unsigned int O ID do cartela.
     */
    unsigned int getId() const;

    /**
     * @brief Obtém o tamanho da sequência no cartela.
     * @return size_t O tamanho da sequência de números.
     */
    size_t size() const;

    /**
     * @brief Verifica se um número específico está marcado.
     * @param number O número a verificar.
     * @return bool Verdadeiro se o número estiver marcado, falso caso contrário.
     */
    bool isMarked(int number) const;

    /**
     * @brief Marca um número no cartela.
     * @param number O número a marcar.
     * @return WinnerType O resultado da marcação do número (pode indicar uma vitória).
     */
    WinnerType markNumber(int number);

    /**
     * @brief Imprime o estado do cartela na saída padrão.
     */
    void print() const;

private:
    unsigned int m_Id; ///< O ID único do cartela.
    std::vector<int> m_Sequence; ///< A sequência de números no cartela.
    std::vector<bool> m_Mask; ///< Indica quais números foram marcados.
    /**
     * @brief Verifica se o cartela atende a qualquer condição de vitória.
     * @return WinnerType O tipo de vitória, se houver.
     */
    WinnerType checkWinningCondition() const;
};

/**
 * @class BingoGame
 * @brief Gerencia o jogo geral e o estado de um jogo de bingo.
 *
 * Esta classe controla o fluxo de um jogo de bingo, gerencia os cartões em jogo,
 * rastreia vencedores e lida com o sorteio de números.
 */
class BingoGame {
public:
    /**
     * @brief Constrói um BingoGame com um conjunto de cartões e um número de bola jackpot.
     * @param cards A coleção de cartões de bingo a serem jogados.
     * @param jackpotBall O número especial da bola jackpot.
     */
    BingoGame(std::vector<Card>& cards, unsigned int jackpotBall);

    /**
     * @brief Inicia e executa o ciclo do jogo.
     * @param balls A lista de bolas sorteadas.
     */
    void play(std::vector<int> balls);

    /**
     * @brief Recupera o número total de cartões no jogo.
     * @return size_t O número de cartões.
     */
    size_t getNumberOfCards() const;

    /**
     * @brief Recupera o número de vencedores no jogo.
     * @return size_t O número de vencedores.
     */
    size_t getNumberOfWinners() const;

    /**
     * @brief Obtém uma lista de cartões que venceram na primeira rodada.
     * @return std::vector<Card> A lista de vencedores da primeira rodada.
     */
    std::vector<Card> getFirstWinners() const;

    /**
     * @brief Obtém uma lista de cartões que venceram na segunda rodada.
     * @return std::vector<Card> A lista de vencedores da segunda rodada.
     */
    std::vector<Card> getSecondWinners() const;

    /**
     * @brief Obtém uma lista de cartões que venceram na terceira rodada.
     * @return std::vector<Card> A lista de vencedores da terceira rodada.
     */
    std::vector<Card> getThirdWinners() const;

    /**
     * @brief Imprime o estado de um cartela específico na saída padrão.
     * @param card O cartela a ser impresso.
     */
    void printCard(const Card& card) const;

    /**
     * @brief Imprime o estado de todos os cartões no jogo na saída padrão.
     */
    void printCards() const;

    /**
     * @brief Imprime a lista de vencedores na saída padrão.
     */
    void printWinners() const;

    /**
     * @brief Recupera o número total de etapas (sorteios) realizados no jogo.
     * @return size_t O número total de etapas do jogo.
     */
    size_t getTotalSteps() const;

private:
    std::vector<Card> m_Cards; ///< A coleção de cartões de bingo participantes do jogo.
    std::vector<Card> m_FirstWinners; ///< Cartões que venceram na primeira rodada.
    std::vector<Card> m_SecondWinners; ///< Cartões que venceram na segunda rodada.
    std::vector<Card> m_ThirdWinners; ///< Cartões que venceram na terceira rodada.
    unsigned int m_JackpotBall; ///< O número da bola jackpot, adicionando regras especiais ao jogo.
    unsigned int m_StepCounter; ///< A contagem de números sorteados no jogo.

    /**
     * @brief Verifica se há vencedores do jackpot entre os jogadores.
     * @return bool Verdadeiro se houver pelo menos um vencedor do jackpot, falso caso contrário.
     */
    bool hasJackpotWinners();
};
