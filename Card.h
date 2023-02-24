#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef CARD_H
#define CARD_H

enum Suits {Clubs = 0, Diamonds, Hearts, Spades};

static const char* SuitsToString[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
static const char* SuitsToStringShort[] = {"C", "D", "H", "S"};

class Card {
protected:
    int Value;
    Suits Suit;

public:
    Card(int Value, Suits Suit);

    void setValue(int Value);
    void setSuit(Suits Suit);
    int getValue();
    Suits getSuit();
    std::string getName();
    std::string getNameShort();

    ~Card();
};

#endif