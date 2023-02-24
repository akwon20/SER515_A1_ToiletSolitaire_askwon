#ifndef DECK_H
#define DECK_H

#include "Card.h"


class Deck {
public:
    std::vector<Card*> Cards;
    void fillDeck();
    void shuffleDeck();
    void printDeck();
    int getDeckSize();
    Card* deal();

    ~Deck();
};

#endif