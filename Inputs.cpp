#include <iostream>
#include <string>
#include <vector>
//#include <windows.h>

#include "Inputs.h"
#include "Computer.h"
#include "Helpers.h"



int inputComputer(std::vector<std::vector<int>> Board, int Player, std::string &input, std::string LastMove) {
    
    int sleep_time = 4000;
    int score;
    Coordinates best;

    // starting input
    std::cout << std::endl << std::endl;
    std::cout << "Player " << (3-Player)/2 << "> thinking...";
    


    score = bestMove(Board, Player, 1, 2, LastMove, best);

    input = moveToString(best);

    std::cout << "best: " << input << std::endl;
    std::cout << "score " << score << std::endl;
    //Sleep(sleep_time);

    

    return 0;

}    



    
int whichPlayer(std::string &Title, int (&players)[2]) {

    char player1, player2;
    
    std::cout << "Player 1: Human or Computer (h/c) ";
    std::cin >> player1;
    if (player1 == 'h') {
        Title = Title + "Human vs. ";
        players[0] = 0;
    } else if (player1 == 'c') {
        Title = Title + "Computer vs. ";
        players[0] = 1;
    } else {
        std::cout << "wrong character" << std::endl;
        return 1;
    }
    std::cout << "Player 2: Human or Computer (h/c) ";
    std::cin >> player2;
    if (player2 == 'h') {
        Title = Title + "Human";
        players[1] = 0;
    } else if (player2 == 'c') {
        Title = Title + "Computer";
        players[1] = 1;
    } else {
        std::cout << "wrong character" << std::endl;
        return 1;
    }

    return 0;

}


int inputHuman(int Player, std::string &input, std::string message) {
    // starting input
    std::cout << std::endl << std::endl;
    std::cout << message << std::endl;
    std::cout << "Player " << (3-Player)/2 << "> ";
    
    std::cin >> input;

    if (std::cin.eof()) {
        return 1;
    }

    return 0;
}
