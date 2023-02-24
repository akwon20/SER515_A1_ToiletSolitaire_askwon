#include "Deck.h"

void Deck::fillDeck() {
    if (DEBUG) {std::cout << "Deck fillDeck() called!" << std::endl;}
    for (int i = 0; i < 52; i++) {
        Suits suit = (static_cast<Suits>(floor(i / 13)));
        int val = (i % 13) + 2;
        Cards.push_back(new Card(val, suit));
    }
}

void Deck::shuffleDeck() {
    std::cout << "Shuffling deck..." << std::endl;  
    int r;
    Card *temp;

    srand(time(0));

    for (int i = 0; i < Cards.size(); i++) {
        r = i + (rand() % (52 - i));
        temp = Cards[i];
        Cards[i] = Cards[r];
        Cards[r] = temp;
    }
}

Card* Deck::deal() {
    Card *dealt;

    dealt = Cards.back();
    Cards.pop_back();
    if (DEBUG) {std::cout << "Card dealt: " << dealt->getName() << std::endl;}

    return dealt;
}

void Deck::printDeck() {
    if (DEBUG) {std::cout << "Printing deck..." << std::endl;}
    for (int i = 0; i < Cards.size(); i++) {
        std::cout << Cards[i]->getNameShort() << 
            "\t" << Cards[i]->getName() << std::endl;
    }
}

int Deck::getDeckSize() {
    return Cards.size();
}


Deck::~Deck() {
    if (DEBUG) {std::cout << "Deck Destructor called!" << std::endl;}
    if (Cards.size() > 0) {
        for (int i = 0; i < Cards.size(); i++) {
            delete Cards[i];
        }
    }
}