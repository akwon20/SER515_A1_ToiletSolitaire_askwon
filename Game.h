#ifndef GAME_H
#define GAME_H

#include "Deck.h"

#define BEGIN_BUFFER hand.size() - 4
#define BUFFER_LIMIT std::max(0, (int)BEGIN_BUFFER)


class Game {
protected:
    int score;
    int choice;
    int shuffleCount;
    int quitTrue;
    Deck deck;
    std::vector<Card*> hand;

public:
    Game();
    Game(Deck deck);

    void init();
    void play();
    void final();
    void clearHand();
    void clearDeck();
    Deck getDeck();

    int MatchingSuits();
    int MatchingValues();
    void displayHand();
    void displayShortHand();

    ~Game();
};


#endif
