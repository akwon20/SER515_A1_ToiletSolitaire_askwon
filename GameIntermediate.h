#ifndef GAMEINTERMEDIATE_H
#define GAMEINTERMEDIATE_H

#include "GameBasic.h"

class GameIntermediate : public GameBasic {
public:
    GameIntermediate();
    void play();
    int MatchingValuesAny(Card *card1, Card *card2);
    int MatchingValuesHand();
    ~GameIntermediate();
};

#endif