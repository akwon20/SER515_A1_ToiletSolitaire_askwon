#include "Card.h"

Card::Card(int Value, Suits Suit) {
    if (DEBUG) {std::cout << "Card Constructor called!" << std::endl;}
    this->Value = Value;
    this->Suit = Suit;
}

void Card::setValue(int Value) {
    this->Value = Value;
}

void Card::setSuit(Suits Suit) {
    this->Suit = Suit;
}

int Card::getValue() {
    return this->Value;
}

Suits Card::getSuit() {
    return this->Suit;
}

std::string Card::getName() {
    std::string cardName;
    std::string valName;
    std::string suitName;

    switch (getValue())
    {
        case(11):
            valName = "Jack";
            break;
        case(12):
            valName = "Queen";
            break;
        case(13):
            valName = "King";
            break;
        case(14):
            valName = "Ace";
            break;
        default:
            valName = std::to_string(getValue());
            break;
    }

    suitName = SuitsToString[getSuit()];
    cardName = valName + " of " + suitName;
    
    return cardName;
}

std::string Card::getNameShort() {
    std::string cardNameShort;
    std::string valName;
    std::string suitName;

    switch (getValue())
    {
        case(11):
            valName = "J";
            break;
        case(12):
            valName = "Q";
            break;
        case(13):
            valName = "K";
            break;
        case(14):
            valName = "A";
            break;
        default:
            valName = std::to_string(getValue());
            break;
    }

    suitName = SuitsToStringShort[getSuit()];
    cardNameShort = valName + suitName;

    return cardNameShort;
}

Card::~Card() {
    if (DEBUG) {std::cout << "Card Destructor called!" << std::endl;}
}