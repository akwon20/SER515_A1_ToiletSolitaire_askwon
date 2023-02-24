#include "GameBasic.h"

GameBasic::GameBasic() {
    if (DEBUG) {std::cout << "GameBasic Constructor called!" << std::endl;}
}

void GameBasic::play() {
    std::cout << "Game Start!" << std::endl;

    while ((deck.Cards.size() > 0) || ((MatchingSuits() == 1) || (MatchingValues() == 1))) {
        std::cout << "------------------------------------------------------------------------------" << std::endl;
        std::cout << "Cards in deck: " << deck.getDeckSize() << std::endl;
        std::cout << "Running score: " << score << std::endl;
        std::cout << "Current hand:" << std::endl;
        displayShortHand();
        displayHand();

        std::cout << "\n" << "Pick your choice: " << std::endl;
        std::cout
            << "1) Draw\t\t" << "2) Remove Middle 2\t"
            << "3) Remove 4\t" << "4) Quit\t" <<
        std::endl;
        
        std::cin >> choice;

        switch(choice)
        {
            case(1):    // Deal a new card
                if (DEBUG) {std::cout << "Drawing a new card..." << std::endl;}
                if (deck.Cards.size() < 1) {
                    std::cout << "!!! - There are no more cards to draw! - !!!" << std::endl;
                }
                else if (hand.size() < 4) {
                    if (DEBUG) {std::cout << "Less than 4 cards in hand! Filling hand..." << std::endl;}
                    while (hand.size() < 4) {
                        hand.push_back(deck.deal());
                    }
                }
                else {
                    hand.push_back(deck.deal());
                }
                break;
            case(2):    // Discard middle two cards (1st and 4th suits match)
                if (DEBUG) {std::cout << "Discarding middle two cards..." << std::endl;}
                if (MatchingSuits() == 0) {
                    std::cout << "!!! - First and fourth suits do not match! - !!!" << std::endl;
                }
                else {
                    hand.erase(hand.end() - 3);
                    hand.erase(hand.end() - 2);
                    std::cout << "Middle two cards discarded!" << std::endl;

                    // Automatically deal cards
                    if (deck.Cards.size() > 0) {
                        int min = std::min(2, (int)deck.Cards.size());
                        for (int i = 0; i < min; i++) {
                            hand.push_back(deck.deal());
                        }
                    }

                }
                break;
            case(3):    // Discard entire hand (1st and 4th values match)
                if (DEBUG) {std::cout << "Discarding whole hand..." << std::endl;}
                if (MatchingValues() == 0) {
                    std::cout << "!!! - First and fourth values do not match! - !!!" << std::endl;
                }
                else {
                    for (int i = 1; i <= 4; i++) {
                        hand.erase(hand.end() - i);
                    }
                    std::cout << "Hand discarded!" << std::endl;

                    // Automatically deal 4 cards
                    if (deck.Cards.size() > 0) {
                        int min = std::min(4, (int)deck.Cards.size());
                        for (int i = 0; i < min; i++) {
                            hand.push_back(deck.deal());
                        }
                    }
                }
                break;
            case(4):
                if (DEBUG) {std::cout << "Exiting game..." << std::endl;}
                break;
            default:
                std::cout << "!!! - Invalid choice! Try again. - !!!" << std::endl;
        }

        if (choice == 4) {
            quitTrue = 1;
            break;
        }
        
        score = hand.size();
        if ((deck.Cards.size() < 1) && ((MatchingSuits() == 0) || (MatchingValues() == 0))) {
            break;
        }
    }
}

GameBasic::~GameBasic() {
    if (DEBUG) {std::cout << "GameBasic Destructor called!" << std::endl;}
}