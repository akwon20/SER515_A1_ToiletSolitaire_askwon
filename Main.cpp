#include "Game.h"
#include "GameBasic.h"
#include "GameIntermediate.h"
#include "GameHouse.h"

/**
 * @brief A program that simulates a game of One-Handed Solitaire (aka Toilet Solitaire)
 * 
 * View the README.md for compilation instructions
 * 
 * GitHub Link: 
 * Taiga Link: 
 *
 * @author Austin Kwon
 */
int main(int argc, char **argv) {
    GameBasic *basic;
    GameIntermediate *intermediate;
    GameHouse *house;
    int choice;

    std::cout << "Welcome to One-Handed Solitaire!\n" << std::endl;

    while (true) {
        try {
            std::cout << "Select Game Mode:" << std::endl;
            std::cout << "\t1) Basic" << std::endl;
            std::cout << "\t2) Intermediate" << std::endl;
            std::cout << "\t3) House Rules" << std::endl;
            std::cout << "\t4) Exit" << std::endl;
            std::cin >> choice;
            std::cout << "\n";

            switch(choice)
            {
                case(1):
                    if (DEBUG) {std::cout << "Now playing: Basic Game" << std::endl;}                    
                    basic = new GameBasic;
                    basic->init();
                    basic->play();
                    basic->final();
                    delete basic;
                    break;

                case(2):
                    if (DEBUG) {std::cout << "Now playing: Intermediate Game" << std::endl;}                    
                    intermediate = new GameIntermediate;
                    intermediate->init();
                    intermediate->play();
                    intermediate->final();
                    delete intermediate;
                    break;

                case(3):
                    if (DEBUG) {std::cout << "Now playing: House Rules Game" << std::endl;}
                    house = new GameHouse;
                    house->init();
                    house->play();
                    house->final();
                    delete house;
                    break;
                case(4):
                    std::cout << "Goodbye! Thank you for playing! :D" << std::endl;
                    return 0;

                default:
                    throw(choice);
            }

            while (true) {
                try {
                    std::cout << "Play again? (1 for yes, 2 for no): ";
                    std::cin >> choice;

                    if ((choice == 1) || (choice == 2)) {
                        std::cout << "\n";
                        break;
                    }
                    else {
                        throw(choice);
                    }
                } catch (int input) {
                    std::cout << "!!! - Invalid choice! Try again. - !!!" << std::endl;
                }
            }

            // Exit application
            if (choice == 2) {
                std::cout << "Goodbye! Thank you for playing! :D" << std::endl;
                return 0;
            }


        } catch (int input) {
            std::cout << "Invalid choice! Try again." << std::endl;
        }
    }

    return 0;
}