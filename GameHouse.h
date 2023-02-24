#ifndef GAMEHOUSE_H
#define GAMEHOUSE_H

#include "GameIntermediate.h"

class GameHouse : public GameIntermediate {
protected:
    int superCount;

public:
    GameHouse();
    void play();
    void final();
    int findPair();
    ~GameHouse();
};

#endif