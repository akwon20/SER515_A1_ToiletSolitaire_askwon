#include "Game.h"


Game::Game() {
    if (DEBUG) {std::cout << "Game Constructor called!" << std::endl;}
    this->score = 0;
    this->choice = 0;
    this->shuffleCount = 0;
    this->quitTrue = 0;
}

Game::Game(Deck deck) {
    if (DEBUG) {std::cout << "Game(Deck) Constructor called!" << std::endl;}
    this->score = 0;
    this->deck = deck;
    this->choice = 0;
    this->shuffleCount = 0;
    this->quitTrue = 0;
}

void Game::init() {
    std::cout << "Initializing game..." << std::endl;
    shuffleCount = 0;
    clearHand();
    clearDeck();
    deck.fillDeck();
    if (DEBUG) {deck.printDeck();}
    deck.shuffleDeck();
    if (DEBUG) {deck.printDeck();}

    while (choice != 2) {
        if (DEBUG) {std::cout << "Shuffle Count: " << shuffleCount << std::endl;}
        std::cout << "Want to shuffle again? (1 for yes, 2 for no): ";  // Note: first shuffle prior doesn't count
        std::cin >> choice;
        if (DEBUG) {std::cout << "Choice: " << choice << std::endl;}
        switch(choice)
        {
            case(1):
                deck.shuffleDeck();
                if (DEBUG) {deck.printDeck();}
                shuffleCount++;
                break;
            case(2):
                break;
            default:
                std::cout << "!!! - Invalid choice! Try again. - !!!" << std::endl;
        }

        if (shuffleCount >= 7) {
            std::cout << "!!! - Maximum shuffle count reached! - !!!" << std::endl;
            break;
        }
    }

    while (hand.size() < 4) {
        if (DEBUG) {std::cout << "Drawing hand..." << std::endl;}
        hand.push_back(deck.deal());
    }

    score = hand.size();
    if (DEBUG) {std::cout << "Score: " << score << std::endl;}
}

void Game::play() {}

void Game::final() {
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "Final score: " << score << std::endl;
    std::cout << "Resulting hand:" << std::endl;
    displayShortHand();
    displayHand();

    if ((score >= 5) || (quitTrue == 1)) {
        std::cout << "Too bad! Better luck next time!" << std::endl;
    }
    else if ((score > 0) && (score < 5)) {
        std::cout << "You win! Great job!" << std::endl;
    }
    else {
        std::cout << "You cleared out your entire hand! Amazing!!! :D" << std::endl;
    }
    std::cout << "\n";
}

Deck Game::getDeck() {
    return this->deck;
}

int Game::MatchingSuits() {
    if (hand[BUFFER_LIMIT]->getSuit() == hand[hand.size()-1]->getSuit()) {
        return 1;
    }
    return 0;
}

int Game::MatchingValues() {
    if (hand[BUFFER_LIMIT]->getValue() == hand[hand.size()-1]->getValue()) {
        return 1;
    }
    return 0;
}


void Game::clearDeck() {
    if (deck.Cards.size() > 0) {
        if (DEBUG) {std::cout << "Clearing deck..." << std::endl;}
        for (int i = 0; i < deck.Cards.size(); i++) {
            delete deck.Cards[i];
        }
        deck.Cards.clear();
    }
}

void Game::displayHand() {
    if (DEBUG) {std::cout << "Displaying hand..." << std::endl;}
    for (int i = BUFFER_LIMIT; i < hand.size(); i++) {
        std::cout << hand[i]->getName() << "\t";
    }
    std::cout << "\n";
}

void Game::displayShortHand() {
    if (DEBUG) {std::cout << "Displaying short version of hand..." << std::endl;}
    for (int i = BUFFER_LIMIT; i < hand.size(); i++) {
        std::cout << "\t" << hand[i]->getNameShort() << "\t";
    }
    std::cout << "\n";
}

void Game::clearHand() {
    if (hand.size() > 0) {
        if (DEBUG) {std::cout << "Clearing hand..." << std::endl;}
        for (int i = 0; i < hand.size(); i++) {
            delete hand[i];
        }
        hand.clear();
    }
}


Game::~Game() {
    if (DEBUG) {std::cout << "Game Destructor called!" << std::endl;}
    clearHand();
}