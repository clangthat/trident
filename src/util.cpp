#include <vector>
#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>
#include <tuple>
#include <time.h>
#include "util.h"


std::vector<int> 
generateRandomNumbers(int A, int B, int N)
{
    std::vector<int> numbers;
    srand(time(0));

    for (int i = 0; i < N; i++) {
        int randomNumber = A + rand() % (B - A + 1);
        numbers.push_back(randomNumber);
    }

    return numbers;
}

std::vector<int>
generateUniqueRandomNumbers(int A, int B, int N)
{
    std::vector<int> numbers;
    srand(time(0));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(A, B);

    for (int i = 0; i < N; i++) {
        int randomNumber = dis(gen);

        bool isUnique = true;
        for (int num : numbers) {
            if (num == randomNumber) {
                isUnique = false;
                break;
            }
        }

        if (isUnique) {
            numbers.push_back(randomNumber);
        } else {
            i--;
        }
    }

    return numbers;
}

int
getIntRound(WinnerType round) {
    switch (round) {
        case WinnerType::FIRST:
            return 1;
        case WinnerType::SECOND:
            return 2;
        case WinnerType::THIRD:
            return 3;
        case WinnerType::NONE:
            return 0;
        default:
            return -1;
    }
}

WinnerType
getWinnerType(int value)
{
    switch (value) {
        case 0:
            return WinnerType::NONE;
        case 1:
            return WinnerType::FIRST;
        case 2:
            return WinnerType::SECOND;
        case 3:
            return WinnerType::THIRD;
        default:
            return WinnerType::INVALID;
    }
}

///////////////////////
// Card Object Impl.
///////////////////////

Card::Card(unsigned int cardId, const std::vector<int>& cardSequence)
    : m_Id(cardId), m_Sequence(cardSequence) {
        m_Mask.resize(cardSequence.size(), false);
}

std::vector<int> Card::getSequence() const {
    return m_Sequence;
}

std::vector<bool> Card::getMask() const {
    return m_Mask;
}

std::vector<int> Card::getRemainingBasedOnRound(WinnerType round) const {
    std::vector<int> a, b, c;
    std::vector<int> remaining;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (!m_Mask[i * 5 + j]) {
                switch (i) {
                    case 0: a.push_back(m_Sequence[i * 5 + j]); break;
                    case 1: b.push_back(m_Sequence[i * 5 + j]); break;
                    case 2: c.push_back(m_Sequence[i * 5 + j]); break;
                }
                remaining.push_back(m_Sequence[i * 5 + j]);
            }
        }
    }
    
    if (round == WinnerType::FIRST) {
            return (a.size() < b.size() && a.size() < c.size()) ? a : (b.size() < c.size()) ? b : c;
        } else if (round == WinnerType::SECOND) {
    
        std::vector<int> combined;
        int size_a = a.size();
        int size_b = b.size();   
        int size_c = c.size();

        int smallest = std::min({size_a, size_b, size_c});
        int secondSmallest = 2147483647;

        // Find the second smallest size
        for (int size : {a.size(), b.size(), c.size()}) {
            if (size > smallest && size < secondSmallest) {
                secondSmallest = size;
            }
        }

        int appendedItem = 0;

        if (smallest == size_a) {
            appendedItem = 1;
            for (int value : a) {
                combined.push_back(value);
            }
        } else if (smallest == size_b) {
            appendedItem = 2;
            for (int value : b) {
                combined.push_back(value);
            }
        } else {
            appendedItem = 3;
            for (int value : c) {
                combined.push_back(value);
            }
        }

        if (secondSmallest == size_a && appendedItem != 1) {
            for (int value : a) {
                combined.push_back(value);
            }
        } else if (smallest == size_b && appendedItem != 2) {
            for (int value : b) {
                combined.push_back(value);
            }
        } else {
            for (int value : c) {
                combined.push_back(value);
            }
        }
        return combined;
    }
    return remaining;
}

unsigned int Card::getId() const {
    return m_Id;
}

size_t Card::size() const {
    return m_Sequence.size();
}

bool Card::isMarked(int number) const {
    for (size_t i = 0; i < m_Sequence.size(); i++) {
        if (m_Sequence[i] == number) {
            return m_Mask[i];
        }
    }
    return false;
}

void Card::print() const {
    std::cout << "Card " << m_Id << std::endl;
    for (size_t i = 0; i < m_Sequence.size(); i++) {
        std::cout << m_Sequence[i] << " ";
        if (i % 5 == 4) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

WinnerType Card::markNumber(int number) {
    for (size_t i = 0; i < m_Sequence.size(); i++) {
        if (m_Sequence[i] == number) {
            m_Mask[i] = true;
            return checkWinningCondition();
        }
    }
    return WinnerType::NONE;
}

WinnerType Card::checkWinningCondition() const {

    /* Here we are using the 3x5 card with 3 round game and winning
     *  pattern being the following:
     *       1st: 5 numbers in a row
     *       2nd: 10 numbers in a row
     *       3rd: complete card
     */
    if (m_Mask.size() < 15) {
        return WinnerType::INVALID;
    }

    int firstRow = 0;
    int secondRow = 0;
    int thirdRow = 0;
    int total = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (m_Mask[i * 5 + j]) {
                if (i == 0) { firstRow++;}
                else if (i == 1) { secondRow++; }
                else { thirdRow++; }
            }
        }
    }

    if (firstRow == 5) {
        total++;
    }

    if (secondRow == 5) {
        total++;
    }

    if (thirdRow == 5) {
        total++;
    }

    return getWinnerType(total);
}

///////////////////////////
// Bingo Game Object Impl.
///////////////////////////

BingoGame::BingoGame(std::vector<Card>& cards, unsigned int jackpotBall)
    : m_Cards(cards), m_JackpotBall(jackpotBall) {};

void BingoGame::play(std::vector<int> balls) {

    if (balls.size() != 90) {
        return;
    }

    WinnerType currentRound = WinnerType::FIRST;
    m_StepCounter = 0;

    for (int ball : balls) {
        bool roundHasWinner = false;
        m_StepCounter++;

#ifdef DEBUG
            std::cout << "\n Step: " << m_StepCounter << " Round: " << getIntRound(currentRound) << " Bola: " << ball << std::endl;
#endif

        for (Card& card : m_Cards) {
            WinnerType winner = card.markNumber(ball);
            
#ifdef DEBUG
    if(winner != WinnerType::INVALID) {
        if (getIntRound(winner) == -1) {
            std::cout << "  ... Card " << card.getId() << " has an invalid winning pattern" << std::endl;
        } else {
            std::cout << "  ... Card " << card.getId() << " has " << getIntRound(winner) << " winning patterns  ";
        }

        for (size_t i = 0; i < card.getMask().size(); i++) {
            if (card.getMask()[i] == true) {
                std::cout << "\033[32m" << card.getMask()[i] << "\033[0m ";
            } else {
                std::cout << card.getMask()[i] << " ";
            }
            if (i % 5 == 4) {
                std::cout << " ";
            }
        }
        std::cout << " Remaining: ";
        std::vector<int> remaining = card.getRemainingBasedOnRound(currentRound);

        for (int num : remaining) {
            std::cout << num << " ";
        }

        if (remaining.size() == 0) { std::cout << "\033[33mWINNER!\033[0m"; }
        std::cout << std::endl;
    }
#endif // DEBUG
    
            if (winner == WinnerType::FIRST && currentRound == WinnerType::FIRST) {
                m_FirstWinners.push_back(card);
                roundHasWinner = true;
            } else if (winner == WinnerType::SECOND && currentRound == WinnerType::SECOND) {
                m_SecondWinners.push_back(card);
                roundHasWinner = true;
            } else if (winner == WinnerType::THIRD && currentRound == WinnerType::THIRD) {
                m_ThirdWinners.push_back(card);
                roundHasWinner = true;
            }
        }

        if (roundHasWinner) {
            if (currentRound == WinnerType::THIRD) {
                break;
            }
            currentRound = static_cast<WinnerType>(static_cast<int>(currentRound) + 1);
        }
    }
}

size_t
BingoGame::getTotalSteps() const {
    return m_StepCounter;
}

size_t
BingoGame::getNumberOfCards() const {
    return m_Cards.size();
}

size_t
BingoGame::getNumberOfWinners() const {
    return m_FirstWinners.size() + m_SecondWinners.size() + m_ThirdWinners.size();
}

bool
BingoGame::hasJackpotWinners() {
    return m_StepCounter <= m_JackpotBall;
}

std::vector<Card>
BingoGame::getFirstWinners() const {
    return m_FirstWinners;
}

std::vector<Card>
BingoGame::getSecondWinners() const {
    return m_SecondWinners;
}

std::vector<Card>
BingoGame::getThirdWinners() const {
    return m_ThirdWinners;
}
