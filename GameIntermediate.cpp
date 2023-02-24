#include "GameIntermediate.h"

GameIntermediate::GameIntermediate() {
    if (DEBUG) {std::cout << "GameIntermediate Constructor called!" << std::endl;}
}

void GameIntermediate::play() {
    std::cout << "Game Start!" << std::endl;

    while ((deck.Cards.size() > 0) || 
            ((MatchingSuits() == 1) || (MatchingValues() == 1) || (MatchingValuesHand() == 1))) {
        std::cout << "------------------------------------------------------------------------------" << std::endl;
        std::cout << "Cards in deck: " << deck.getDeckSize() << std::endl;
        std::cout << "Running score: " << score << std::endl;
        std::cout << "Current hand:" << std::endl;
        displayShortHand();
        displayHand();
        
        std::cout << "\n" << "Pick your choice: " << std::endl;
        std::cout
            << "1 Draw\t\t" << "2) Remove Middle 2\t" << "3) Remove Pair 2\t"
            << "4) Remove 4\t" << "5) Quit\t" <<
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
            case(3):    // Discard first pair of matching values
                int index1;    
                int index2;
                
                // -1 to keep indices from being used
                index1 = -1;
                index2 = -2;

                for (int i = 0; i < 3; i++) {
                    for (int j = i+1; j < 4; j++) {
                        if (MatchingValuesAny(hand[BUFFER_LIMIT+i], hand[BUFFER_LIMIT+j])) {
                            index1 = i;
                            index2 = j;
                            break;
                        }
                    }
                    if ((index1 > -1) && (index2 > -1)) {
                        break;
                    }
                }

                if ((index1 > -1) && (index2 > -1)) {
                    hand.erase(hand.end() - (4 - index1));
                    hand.erase(hand.end() - (4 - index2));
                    std::cout << "Pair discarded!" << std::endl;

                    // Automatically deal cards
                    if (deck.Cards.size() > 0) {
                        int min = std::min(2, (int)deck.Cards.size());
                        for (int i = 0; i < min; i++) {
                            hand.push_back(deck.deal());
                        }
                    }
                }
                else {
                    std::cout << "!!! - No pairs found! - !!!" << std::endl;
                }
                
                break;
            case(4):    // Discard entire hand (1st and 4th values match)
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
                    int min = std::min(4, (int)deck.Cards.size());
                    if (deck.Cards.size() > 0) {
                        int min = std::min(4, (int)deck.Cards.size());
                        for (int i = 0; i < min; i++) {
                            hand.push_back(deck.deal());
                        }
                    }
                }
                break;
            case(5):
                if (DEBUG) {std::cout << "Exiting game..." << std::endl;}
                break;
            default:
                std::cout << "!!! - Invalid choice! Try again. - !!!" << std::endl;
        }

        if (choice == 5) {
            quitTrue = 1;
            break;
        }
        
        score = hand.size();

        if ((deck.Cards.size() < 1) && 
            ((MatchingSuits() == 0) || (MatchingValues() == 0) || (MatchingValuesHand() == 0))) {
            break;
        }
    }
}

int GameIntermediate::MatchingValuesAny(Card *card1, Card *card2) {
    if (card1->getValue() == card2->getValue()) {
        return 1;
    }
    return 0;
}

int GameIntermediate::MatchingValuesHand() {
    for (int i = 0; i < 3; i++) {
        for (int j = i+1; j < 4; j++) {
            if (hand[BUFFER_LIMIT + i]->getValue() == hand[hand.size()-j]->getValue()) {
                return 1;
            }
        }
    }
    return 0;
}

GameIntermediate::~GameIntermediate() {
    if (DEBUG) {std::cout << "GameIntermediate Destructor called!" << std::endl;}
}