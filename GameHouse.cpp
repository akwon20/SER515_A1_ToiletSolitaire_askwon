#include "GameHouse.h"

GameHouse::GameHouse() {
    if (DEBUG) {std::cout << "GameHouse Constructor called!" << std::endl;}
    this->superCount = 0;
}

void GameHouse::play() {
    std::cout << "Game Start!" << std::endl;
    superCount = 0;

    while ((deck.Cards.size() > 0) ||
            ((MatchingSuits() == 1) 
            || (MatchingValues() == 1)
            || (MatchingValuesHand() == 1) || ((MatchingSuits() == 1)
            && (MatchingValuesAny(hand[BUFFER_LIMIT], hand[BUFFER_LIMIT+1]))))) {
        std::cout << "------------------------------------------------------------------------------" << std::endl;
        std::cout << "Cards in deck: " << deck.getDeckSize() << std::endl;
        std::cout << "Running score: " << score << std::endl;
        std::cout << "Super discards: " << superCount << std::endl;
        std::cout << "Current hand:" << std::endl;
        displayShortHand();
        displayHand();

        std::cout << "\n" << "Pick your choice: " << std::endl;
        std::cout << "1) Draw\t\t" << "2) Remove Middle 2\t\t" << "3) Remove Pair 2\t" << std::endl;
        std::cout  << "4) Remove 4\t" << "5) Remove 3 (Super discard)\t" << "6) Quit\t" << std::endl;
        
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
                    if (DEBUG) {std::cout << "Middle two cards discarded!" << std::endl;}
                    
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
                        if (MatchingValuesAny(hand[BUFFER_LIMIT+i], hand[BUFFER_LIMIT+j]) == 1) {
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
            case(5):    // Discard first three cards (1st and 4th have same suit; 1st and 2nd have same value)
                if ((MatchingSuits() == 0)
                    || (MatchingValuesAny(hand[BUFFER_LIMIT], hand[BUFFER_LIMIT+1]) == 0)) {
                    std::cout <<
                     "!!! - Neither the first and fourth suits nor the first and second values match! - !!!"
                    << std::endl;
                }
                else {
                    if (DEBUG) {std::cout << "Discarding first three cards..." << std::endl;}
                    hand.erase(hand.end()-4);
                    hand.erase(hand.end()-3);
                    hand.erase(hand.end()-2);
                    superCount++;
                    std::cout << "First three cards discarded!" << std::endl;
                }
                break;
            case(6):
                if (DEBUG) {std::cout << "Exiting game..." << std::endl;}
                break;
            default:
                std::cout << "!!! - Invalid choice! Try again. - !!!" << std::endl;
        }

        if (choice == 6) {
            quitTrue = 1;
            break;
        }
        
        score = hand.size();

        if ((deck.Cards.size() < 1) && 
            ((MatchingSuits() == 0) || (MatchingValues() == 0)
             || (MatchingValuesHand() == 0)
             || (MatchingValuesAny(hand[BUFFER_LIMIT], hand[BUFFER_LIMIT+1]) == 0))) {
            break;
        }

    }
}

void GameHouse::final() {
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "Final score: " << score << std::endl;
    std::cout << "Super discards: " << superCount << std::endl;
    std::cout << "Resulting hand:" << std::endl;
    displayShortHand();
    displayHand();

    if ((score >= 5) || (quitTrue == 1)) {
        std::cout << "Too bad! Better luck next time!" << std::endl;
    }
    else if ((score > 0) && (score < 5)) {
        std::cout << "You win! Great job!" << std::endl;
    }
    else if ((score == 0) && (superCount < 2)){
        std::cout << "Perfect win!!! SUGOI!!!!!!!!!! (>W<)/U" << std::endl;
    }
    else {
        std::cout << "You cleared out your entire hand! Amazing!!! :D" << std::endl;
        std::cout << "You just need to get at least 2 super discards for a perfect win." << std::endl;
    }
    std::cout << "\n";

}

int GameHouse::findPair() {
    for (int i = 0; i < 3; i++) {
        for (int j = i+1; j < 4; j++) {
            if (hand[i]->getValue() == hand[j]->getValue()) {
                return 1;
            }
        }
    }
    return 0;
}

GameHouse::~GameHouse() {
    if (DEBUG) {std::cout << "GameHouse Destructor called!" << std::endl;}
}