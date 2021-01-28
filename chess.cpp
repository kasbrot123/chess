#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Computer.h"
#include "Plotting.h"
#include "Helpers.h"
#include "Gamelogic.h"
#include "Inputs.h"




int main(void) {

    // variable setup
    std::string title = "";
    int players[2] = {0, 0};
    std::vector<std::vector<int>> board;
    board = init_board();

    std::vector<Coordinates> turns;
    std::vector<std::string> turns_str;
    std::string input = "";
    std::string message = "";
    int player = 1;
    int enPassant;
    std::string prevMove = "X0-X0";
    Coordinates move;
    int PlayerType;



    // set up players
    if (whichPlayer(title, players))
        return 1;


    while (true) {

        // clear screen
        //system ("CLS");

        // print board
        plot_board(board, title);
        
        if (Check(board, player))
            std::cout << "Check" << std::endl;

        // print move
        print_moves(turns_str);


        // input or computer
        PlayerType = players[(3-player)/2-1];
        if (!PlayerType) {
            //std::cout << "Human player" << std::endl;
            inputHuman(player, input, message);
        } else {
            //inputHuman(player, input, message);
            inputComputer(board, player, input, prevMove);
        }


        // quit game
        if (input == "quit") {
            break;
            //running = false;
        }
        
        // help page
        if (input == "help") {
            std::string dummy;
            system("CLS");
            print_help();
            std::cin.ignore();
            std::cin.get();
            continue;
        }


        // action
        enPassant = false;
        if (turns.size() > 0) {
            prevMove = turns_str.back();
        }


        // validate turn
        if (false_move(input, board, message, player, prevMove, enPassant)) {
            //message = "invalid turn, repeat input";
            continue;
        }

        // everything is correct
        move = coordsMove(input);
        turns.push_back(move);
        turns_str.push_back(input);
        player = -player;

        board = move_figure(board, move, enPassant);

    }

    return 0;
}